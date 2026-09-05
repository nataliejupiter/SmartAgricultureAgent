from __future__ import annotations
# /root/smart_agri/rag/RAG/rag-retrieval-main/rag-retrieval-main
"""
cmd:
D:\Download\llama_cpp\llama-b9114-bin-win-cpu-x64\llama-b9114-bin-win-cpu-x64>llama-server.exe ^
  -m D:\About_Competitions_and_Projects\innova_agri_agent\code\RAG\model\qwen_gguf\qwen2.5-7b-instruct-q4_k_m.gguf ^
  -c 4096
  --port 8080
  --api
  
cd /root/smart_agri/rag/RAG/rag-retrieval-main/rag-retrieval-main
conda activate argi_server_3.10
cd /root/smart_agri/rag/RAG/model/llama.cpp/build/bin
ssh root@8.152.218.172
./llama-server -m /root/smart_agri/rag/RAG/model/qwen_gguf/qwen2.5-7b-instruct-q4_k_m.gguf -c 4096

"""
#!/usr/bin/env python3
"""Minimal RAG MVP for GGUF via llama-server.

Run examples:

# 1) Start your llama-server first (same host or remote)
# Example:
# llama-server -m qwen2.5-7b-instruct-q4_k_m.gguf -c 4096 --host 0.0.0.0

# 2) Run this RAG API server
# python rag_gguf.py --mode server --llama_server_url http://127.0.0.1:8080

# 3) Interactive CLI
# python rag_gguf.py --mode cli --query "现在天气晴朗，有微风，气温15摄氏度，土壤湿度28%，我种了一批草莓，但是发现有一些蚜虫，下面我该怎么办"
# python rag_mvp_server.py --mode cli
"""

from fastapi.responses import JSONResponse
from fastapi.requests import Request
import argparse
import json
import os
import re
import threading
from functools import lru_cache
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

import faiss
import numpy as np
import requests
import torch
import uvicorn
from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel, Field
from sentence_transformers import SentenceTransformer

# ----------------------------
# Config
# ----------------------------
INDEX_PREFIX = "agri_rag_v3"  # expects xxx.index + xxx_meta.jsonl in cwd
EMBED_MODEL = "D:\\About_Competitions_and_Projects\\innova_agri_agent\\code\\RAG\\model\\bge\\BAAI\\bge-small-zh-v1___5"
DEFAULT_MODEL_NAME = "D:\\About_Competitions_and_Projects\\innova_agri_agent\\code\\RAG\\model\\qwen_gguf\\qwen2.5-7b-instruct-q4_k_m.gguf"  # only used in docs / logs
DEFAULT_LLM_SERVER_URL = "http://127.0.0.1:8080"
DEFAULT_LLM_COMPLETION_PATH = "/v1/chat/completions"
DEVICE = "cpu"  # keep embedding CPU-only for portability unless you change it explicitly

# Speed-oriented defaults
DEFAULT_TOP_K = 3
DEFAULT_MAX_NEW_TOKENS = 1024
DEFAULT_TEMPERATURE = 0.3
DEFAULT_TOP_P = 0.9
DEFAULT_TIMEOUT = (10, 300)  # connect timeout, read timeout

# Keep torch from oversubscribing threads on some machines
try:
    torch.set_num_threads(max(1, os.cpu_count() or 1))
except Exception:
    pass

# ----------------------------
# Utilities
# ----------------------------
def normalize_text(text: str) -> str:
    """Normalize a query so repeated inputs hit the cache better."""
    text = text.strip().lower()
    text = re.sub(r"\s+", " ", text)
    return text


def load_index_and_meta(prefix: str = INDEX_PREFIX):
    idx_file = Path(f"{prefix}.index")
    meta_file = Path(f"{prefix}_meta.jsonl")

    if not idx_file.exists():
        raise FileNotFoundError(f"FAISS index file not found: {idx_file.resolve()}")
    if not meta_file.exists():
        raise FileNotFoundError(f"Meta file not found: {meta_file.resolve()}")

    index = faiss.read_index(str(idx_file))
    metas: List[Dict[str, Any]] = []
    with meta_file.open("r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if line:
                metas.append(json.loads(line))

    return index, metas


# ----------------------------
# Retriever (FAISS unchanged, cached)
# ----------------------------
class Retriever:
    def __init__(self, index, metas, embed_model_name: str = EMBED_MODEL, device: str = DEVICE):
        self.index = index
        self.metas = metas
        self.embedder = SentenceTransformer(embed_model_name, device=device)
        self.lock = threading.Lock()

    @lru_cache(maxsize=4096)
    def _embed_query_cached(self, normalized_query: str) -> Tuple[float, ...]:
        """Cache query embeddings to avoid recomputing repeated queries."""
        with self.lock:
            emb = self.embedder.encode(
                [normalized_query],
                convert_to_numpy=True,
                show_progress_bar=False,
                batch_size=1,
            ).astype("float32")

        # Keep your FAISS usage style: normalize query vector before search.
        faiss.normalize_L2(emb)
        return tuple(float(x) for x in emb[0])

    def retrieve(self, query: str, top_k: int = DEFAULT_TOP_K) -> List[Dict[str, Any]]:
        normalized_query = normalize_text(query)
        q_vec = np.array([self._embed_query_cached(normalized_query)], dtype="float32")

        D, I = self.index.search(q_vec, top_k)
        results: List[Dict[str, Any]] = []
        for score, idx in zip(D[0], I[0]):
            if idx < 0:
                continue
            m = self.metas[idx].copy()
            m["score"] = float(score)
            results.append(m)
        return results


# ----------------------------
# Prompt builder (minimal MVP)
# ----------------------------
def build_prompt(retrieved: List[Dict[str, Any]], user_query: str) -> str:
    evidence_lines: List[str] = []
    for i, r in enumerate(retrieved, start=1):
        text = str(r.get("text", "")).replace("\n", " ").strip()
        if len(text) > 700:
            text = text[:700]
        source = r.get("source", "unknown")
        score = r.get("score", 0.0)
        evidence_lines.append(f"[{i}] source={source} score={score:.4f}\n{text}")

    evidence_block = "\n\n".join(evidence_lines) if evidence_lines else "(no retrieved evidence)"

    return (
        "### System\n"
        "你是一名农业种植与病虫害防治专家，需要根据环境数据、作物状态、天气情况和检索到的农业知识，为农户提供实用、可靠的建议。\n\n"

        "回答要求：\n"
        "1. 优先分析当前最主要的问题，再给出具体到实处的处理措施。\n"
        "2. 优先给出最关键、最紧急的措施。\n"
        "3. 如果信息不足，可以明确指出需要补充的数据。\n"
        "4. 回答要尽量精炼，不要废话。\n"
        "5. 如果检索内容与问题关联较弱，不要生硬引用。\n\n"

        "### 用户问题\n"
        f"{user_query}\n\n"

        "### 检索到的农业知识\n"
        f"{evidence_block}\n\n"

        "### 回答任务\n"
        "请结合环境情况与农业知识：\n"
        "- 给出优先处理措施\n"
        "- 给出具体到实处的操作建议\n\n"

        "### Assistant\n"

    )


# ----------------------------
# llama-server client
# ----------------------------
class LlamaServerClient:
    def __init__(self, base_url: str = DEFAULT_LLM_SERVER_URL, completion_path: str = DEFAULT_LLM_COMPLETION_PATH):
        self.base_url = base_url.rstrip("/")
        self.completion_url = f"{self.base_url}{completion_path}"
        self.session = requests.Session()
        self.lock = threading.Lock()

    def generate(
            self,
            prompt: str,
            max_new_tokens: int = DEFAULT_MAX_NEW_TOKENS,
            temperature: float = DEFAULT_TEMPERATURE,
            top_p: float = DEFAULT_TOP_P,
            cache_prompt: bool = True,
    ) -> str:

        payload = {
            "model": "qwen2.5-7b-instruct-q4_k_m.gguf",
            "messages": [
                {"role": "system", "content": "你是农业决策专家"},
                {"role": "user", "content": prompt}
            ],
            "max_tokens": int(max_new_tokens),
            "temperature": float(temperature),
            "top_p": float(top_p),
            "stream": False
        }

        try:
            # ===== 请求 =====
            with self.lock:
                resp = self.session.post(
                    self.completion_url,
                    json=payload,
                    timeout=DEFAULT_TIMEOUT
                )

            print("\n===== llama-server 响应 =====")
            print("status:", resp.status_code)
            print("text:", resp.text)

            # ===== HTTP错误 =====
            resp.raise_for_status()

            # ===== JSON解析 =====
            try:
                data = resp.json()
            except Exception:
                raise ValueError(f"返回不是JSON: {resp.text}")

            # ===== 解析逻辑（你这个其实是OK的）=====
            if isinstance(data, dict):

                # OpenAI格式
                if "choices" in data and data["choices"]:
                    choice = data["choices"][0]

                    if isinstance(choice, dict):

                        # 标准chat
                        if "message" in choice and isinstance(choice["message"], dict):
                            content = choice["message"].get("content", "")
                            if content:
                                return str(content).strip()

                        # 兼容text
                        if "text" in choice:
                            return str(choice["text"]).strip()

                # fallback（llama.cpp某些版本）
                if "content" in data:
                    return str(data["content"]).strip()

            # ===== 兜底 =====
            raise ValueError(f"无法解析模型返回: {data}")

        except Exception as e:
            import traceback
            print("\n===== generate() 出错 =====")
            traceback.print_exc()
            raise RuntimeError(f"LLM调用失败: {str(e)}")

# ----------------------------
# Global state for server mode
# ----------------------------
GLOBAL: Dict[str, Any] = {
    "retriever": None,
    "llm": None,
    "args": None,
}


# ----------------------------
# API models
# ----------------------------
class ChatRequest(BaseModel):
    message: str = Field(..., description="User question")
    top_k: int = Field(DEFAULT_TOP_K, ge=1, le=20)
    max_new_tokens: int = Field(DEFAULT_MAX_NEW_TOKENS, ge=1, le=2048)
    temperature: float = Field(DEFAULT_TEMPERATURE, ge=0.0, le=3.0)
    top_p: float = Field(DEFAULT_TOP_P, ge=0.0, le=1.0)


class ChatResponse(BaseModel):
    reply: str
    evidence: List[Dict[str, Any]]
    cached: bool = False


# ----------------------------
# Build FastAPI app
# ----------------------------
app = FastAPI(title="Minimal RAG MVP", version="1.0")

# Allow mobile app / H5 / debug tools to call it easily.
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.on_event("startup")
def startup_event():

    print("[startup] 初始化中...")

    #  手动写死
    index_prefix = INDEX_PREFIX
    embed_model = EMBED_MODEL
    embed_device = DEVICE
    llama_server_url = DEFAULT_LLM_SERVER_URL
    llama_completion_path = DEFAULT_LLM_COMPLETION_PATH

    print("[startup] loading FAISS index + metadata ...")
    index, metas = load_index_and_meta(index_prefix)

    GLOBAL["retriever"] = Retriever(
        index,
        metas,
        embed_model_name=embed_model,
        device=embed_device
    )

    print("[startup] connecting to llama-server...")
    GLOBAL["llm"] = LlamaServerClient(
        base_url=llama_server_url,
        completion_path=llama_completion_path,
    )

    print("[startup] 初始化完成")

# 健康检查接口，判断服务是否正常
@app.get("/health")
def health():
    return {
        "status": "ok",
        "retriever_ready": GLOBAL["retriever"] is not None,
        "llm_ready": GLOBAL["llm"] is not None,
    }


@app.post("/chat", response_model=ChatResponse)
def chat(req: ChatRequest):
    print("\n========== 新请求 ==========")
    print("用户输入:", req.message)

    retriever: Optional[Retriever] = GLOBAL["retriever"]
    llm: Optional[LlamaServerClient] = GLOBAL["llm"]

    # ===== 1️⃣ 基础组件检查 =====
    if retriever is None:
        print("❌ Retriever 未初始化")
        raise HTTPException(status_code=500, detail="Retriever not initialized")

    if llm is None:
        print("❌ LLM 未初始化")
        raise HTTPException(status_code=500, detail="LLM client not initialized")

    # ===== 2️⃣ 检索阶段 =====
    try:
        print("\n--- 开始检索 ---")
        retrieved = retriever.retrieve(req.message, top_k=req.top_k)
        print(f"✅ 检索成功，返回 {len(retrieved)} 条")

    except Exception as e:
        import traceback
        print("❌ Retriever 出错")
        traceback.print_exc()

        raise HTTPException(
            status_code=500,
            detail=f"Retriever error: {str(e)}"
        )

    # ===== 3️⃣ Prompt 构建 =====
    try:
        print("\n--- 构建 Prompt ---")
        prompt = build_prompt(retrieved, req.message)
        print("✅ Prompt 构建成功")
        print("Prompt长度:", len(prompt))

    except Exception as e:
        import traceback
        print("❌ Prompt 构建出错")
        traceback.print_exc()

        raise HTTPException(
            status_code=500,
            detail=f"Prompt build error: {str(e)}"
        )

    # ===== 4️⃣ LLM 推理 =====
    try:
        print("\n--- 调用 LLM ---")
        reply = llm.generate(
            prompt,
            max_new_tokens=req.max_new_tokens,
            temperature=req.temperature,
            top_p=req.top_p,
            cache_prompt=True,
        )
        print("✅ LLM 返回成功")
        print("回复长度:", len(reply))

    except Exception as e:
        import traceback
        print("❌ LLM 调用出错")
        traceback.print_exc()

        raise HTTPException(
            status_code=500,
            detail=f"LLM error: {str(e)}"
        )

    # ===== 5️⃣ 返回结果 =====
    try:
        print("\n--- 返回前端 ---")
        return ChatResponse(
            reply=reply,
            evidence=retrieved,
            cached=False
        )

    except Exception as e:
        import traceback
        print("❌ 返回数据构造失败")
        traceback.print_exc()

        raise HTTPException(
            status_code=500,
            detail=f"Response build error: {str(e)}"
        )


# OpenAI-style endpoint for easier app integration later if you want it.
@app.post("/v1/chat/completions")
def openai_style_chat(payload: Dict[str, Any]):

    print("\n===== 收到请求 =====")
    print(payload)

    try:
        message = ""

        if "messages" in payload and isinstance(payload["messages"], list):
            for m in reversed(payload["messages"]):
                if isinstance(m, dict) and m.get("role") == "user":
                    message = str(m.get("content", ""))
                    break
        else:
            message = str(payload.get("message", ""))

        print("解析出的 message:", message)

        if not message.strip():
            raise ValueError("message为空")

        top_k = int(payload.get("top_k", DEFAULT_TOP_K))
        max_new_tokens = int(payload.get("max_tokens", DEFAULT_MAX_NEW_TOKENS))
        temperature = float(payload.get("temperature", DEFAULT_TEMPERATURE))
        top_p = float(payload.get("top_p", DEFAULT_TOP_P))

        print("参数:", top_k, max_new_tokens, temperature, top_p)

        retriever = GLOBAL["retriever"]
        llm = GLOBAL["llm"]

        retrieved = retriever.retrieve(message, top_k=top_k)
        print("检索OK")

        prompt = build_prompt(retrieved, message)
        print("prompt OK")

        reply = llm.generate(
            prompt,
            max_new_tokens=max_new_tokens,
            temperature=temperature,
            top_p=top_p,
        )
        print("LLM OK")

        return {
            "choices": [
                {
                    "message": {
                        "content": reply
                    }
                }
            ],
            "evidence": retrieved
        }

    except Exception as e:
        import traceback
        print("\n❌ 出错了")
        traceback.print_exc()

        return {
            "error": str(e),
            "traceback": traceback.format_exc()
        }

@app.exception_handler(Exception)
async def global_exception_handler(request: Request, exc: Exception):
    import traceback
    tb = traceback.format_exc()

    print("\n===== 全局异常捕获 =====")
    print(tb)

    return JSONResponse(
        status_code=500,
        content={
            "error": str(exc),
            "traceback": tb
        },
    )

# ----------------------------
# CLI mode
# ----------------------------

def cli_once(retriever: Retriever, llm: LlamaServerClient, query: str, top_k: int, max_new_tokens: int):
    retrieved = retriever.retrieve(query, top_k=top_k)
    prompt = build_prompt(retrieved, query)
    reply = llm.generate(prompt, max_new_tokens=max_new_tokens, temperature=0.0, top_p=1.0, cache_prompt=True)
    print("\n=== Reply ===")
    print(reply)
    print("\n=== Evidence ===")
    for i, r in enumerate(retrieved, start=1):
        excerpt = str(r.get("text", "")).replace("\n", " ")
        if len(excerpt) > 180:
            excerpt = excerpt[:180] + "..."
        print(f"[{i}] score={r.get('score', 0.0):.4f} source={r.get('source', 'unknown')} :: {excerpt}")


def cli_mode(args):
    index, metas = load_index_and_meta(args.index_prefix)
    retriever = Retriever(index, metas, embed_model_name=args.embed_model, device=args.embed_device)
    llm = LlamaServerClient(base_url=args.llama_server_url, completion_path=args.llama_completion_path)

    if args.query:
        cli_once(retriever, llm, args.query, args.top_k, args.max_new_tokens)
        return

    print("Enter your question. Type 'exit' or 'quit' to stop.")
    while True:
        try:
            query = input("\n> ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\nbye")
            break

        if not query:
            continue
        if query.lower() in {"exit", "quit", "q"}:
            break

        cli_once(retriever, llm, query, args.top_k, args.max_new_tokens)


# ----------------------------
# Args / main
# ----------------------------

def parse_args():
    p = argparse.ArgumentParser()
    p.add_argument("--mode", choices=["cli", "server"], default="cli")
    p.add_argument("--query", type=str, default=None)
    p.add_argument("--index_prefix", type=str, default=INDEX_PREFIX)
    p.add_argument("--embed_model", type=str, default=EMBED_MODEL)
    p.add_argument("--embed_device", type=str, default=DEVICE)
    p.add_argument("--llama_server_url", type=str, default=DEFAULT_LLM_SERVER_URL, help="fastapi要去请求的大模型服务地址")
    p.add_argument("--llama_completion_path", type=str, default=DEFAULT_LLM_COMPLETION_PATH)
    p.add_argument("--top_k", type=int, default=DEFAULT_TOP_K)
    p.add_argument("--max_new_tokens", type=int, default=DEFAULT_MAX_NEW_TOKENS)
    p.add_argument("--host", type=str, default="0.0.0.0")
    p.add_argument("--port", type=int, default=4567, help="fastapi端口")
    p.add_argument("--reload", action="store_true")
    return p.parse_args()


if __name__ == "__main__":
    args = parse_args()
    GLOBAL["args"] = args

    if args.mode == "cli":
        cli_mode(args)
    elif args.mode == "server":
        # Startup event will load FAISS + llama client.
        uvicorn.run(
            "rag_gguf:app",
            host=args.host,
            port=args.port,
            reload=True,
            log_level="debug",
        )
