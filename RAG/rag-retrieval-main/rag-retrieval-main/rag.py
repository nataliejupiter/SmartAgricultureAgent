#!/usr/bin/env python3
# rag.py
"""
Minimal RAG: load existing FAISS index + meta -> retrieve -> build prompt -> generate with local LLM.
Usage:
  # CLI query:
  python rag.py --mode cli --query "现在土壤含水量 28%, 温度 29°C, 是否需要浇水？" --snapshot '{"node_id":"n1","ts":"2026-01-30T08:00:00Z","temp_C":29,"soil_vwc_percent":28,"rh_percent":82}'

  # Start API:
  python rag.py --mode server

"""

import json, argparse, threading, os
from pathlib import Path
from typing import List, Dict, Any
import numpy as np
import faiss
from sentence_transformers import SentenceTransformer
from transformers import AutoTokenizer, AutoModelForCausalLM
import torch

# FastAPI parts (optional)
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel

# ----------------------------
# Config (tune these)
# ----------------------------
INDEX_PREFIX = "LLM_word"                         # defaults to LLM_word.index & LLM_word_meta.jsonl
EMBED_MODEL = "sentence-transformers/all-MiniLM-L6-v2"  # change if you used a different embed model
LOCAL_LLM_DIR = "D:\About_Competitions_and_Projects\模型量化\deployInRK3588\DeepSeek-R1-Distill-Qwen-1.5B"
DEVICE = "cuda" if torch.cuda.is_available() else "cpu"

# ----------------------------
# Load index & metadata
# ----------------------------
def load_index_and_meta(prefix: str = INDEX_PREFIX):
    idx_file = f"{prefix}.index"
    meta_file = f"{prefix}_meta.jsonl" if Path(f"{prefix}_meta.jsonl").exists() else f"{prefix}_meta.jsonl"
    # if user used different naming, try both patterns
    if not Path(idx_file).exists():
        raise FileNotFoundError(f"FAISS index file {idx_file} not found in cwd.")
    if not Path(meta_file).exists():
        # also try prefix + "_meta.jsonl"
        raise FileNotFoundError(f"Meta file {meta_file} not found in cwd.")
    index = faiss.read_index(idx_file)
    metas = []
    with open(meta_file, "r", encoding="utf8") as f:
        for line in f:
            metas.append(json.loads(line.strip()))
    return index, metas

# ----------------------------
# Retriever
# ----------------------------
class Retriever:
    def __init__(self, index, metas, embed_model_name=EMBED_MODEL):
        self.index = index
        self.metas = metas
        self.embedder = SentenceTransformer(embed_model_name)

    def retrieve(self, query: str, top_k: int = 5):
        q_emb = self.embedder.encode([query], convert_to_numpy=True).astype("float32")
        faiss.normalize_L2(q_emb)
        D, I = self.index.search(q_emb, top_k)
        results = []
        for score, idx in zip(D[0], I[0]):
            if idx < 0:
                continue
            m = self.metas[idx].copy()
            m["score"] = float(score)
            results.append(m)
        return results

# ----------------------------
# Local LLM wrapper
# ----------------------------
class LocalLLM:
    def __init__(self, model_dir: str, device: str = DEVICE):
        if not Path(model_dir).exists():
            raise FileNotFoundError(f"Local model directory {model_dir} not found.")
        print("Loading tokenizer and model from", model_dir, "-> device:", device)
        self.tokenizer = AutoTokenizer.from_pretrained(model_dir, trust_remote_code=False)
        # Use float16 on CUDA if available for memory savings; on CPU fallback to float32
        dtype = torch.float16 if (device.startswith("cuda")) else torch.float32
        self.model = AutoModelForCausalLM.from_pretrained(model_dir, torch_dtype=dtype, low_cpu_mem_usage=True)
        self.model.to(device)
        self.device = device
        self.lock = threading.Lock()

    def generate(self, prompt: str, max_new_tokens: int = 2048, temperature: float = 0.2, top_k: int = 50, top_p: float = 0.95):
        with self.lock:
            inputs = self.tokenizer(prompt, return_tensors="pt", truncation=True, max_length=2048).to(self.model.device)
            out = self.model.generate(**inputs, max_new_tokens=max_new_tokens, do_sample=True, temperature=temperature, top_k=top_k, top_p=top_p)
            gen = self.tokenizer.decode(out[0][inputs["input_ids"].shape[-1]:], skip_special_tokens=True)
            return gen

# ----------------------------
# Prompt builder
# ----------------------------
def build_prompt(snapshot: Dict[str,Any], retrieved: List[Dict], user_query: str):
    # build environment summary
    env_lines = []
    if snapshot:
        env_lines.append(f"现场快照 (时间: {snapshot.get('ts','unknown')}, 节点: {snapshot.get('node_id','unknown')}):")
        for k in ["temp_C", "rh_percent", "soil_vwc_percent", "leaf_wet_hours"]:
            if snapshot.get(k) is not None:
                env_lines.append(f"- {k}: {snapshot.get(k)}")
        if "detections" in snapshot:
            for d in snapshot["detections"]:
                env_lines.append(f"- 检测: {d.get('type')} 数量: {d.get('count','N/A')} 置信: {d.get('conf','')}")
    else:
        env_lines.append("No snapshot provided.")

    evidence_texts = []
    for i, r in enumerate(retrieved):
        excerpt = r.get("text", "")[:800].replace("\n", " ")
        evidence_texts.append(f"[{i+1}] source={r.get('source')} score={r.get('score'):.3f}\n{excerpt}")

    prompt_parts = [
        "你是农业领域的专家助理，回答要保守、可验证，并在给出建议时标注依据与不确定性。",
        "\n".join(env_lines),
        "检索到的证据片段（按相关性）：",
        "\n".join(evidence_texts),
        "用户问题: " + user_query,
        "请基于上述现场快照与证据，给出：1) 环境概况 2) 优先级排序的具体建议（灌溉/施药/巡检）3) 若给出农药或剂量，需标注依据与安全注意事项 4) 推荐的后续观测或复核时间。"
    ]
    return "\n\n".join(prompt_parts)

# ----------------------------
# Simple CLI flow
# ----------------------------
def cli_mode(args):
    index, metas = load_index_and_meta(args.index_prefix)
    retriever = Retriever(index, metas, embed_model_name=args.embed_model)
    llm = LocalLLM(args.model_dir, device=args.device)
    # parse snapshot as json if provided
    snapshot = {}
    if args.snapshot:
        try:
            snapshot = json.loads(args.snapshot)
        except Exception:
            print("Warning: snapshot parse failed; using empty snapshot.")
            snapshot = {}
    # retrieve and generate
    retrieved = retriever.retrieve(args.query, top_k=args.top_k)
    prompt = build_prompt(snapshot, retrieved, args.query)
    print("=== Prompt (for debug) ===\n", prompt[:2000], "\n=== end prompt ===")
    out = llm.generate(prompt, max_new_tokens=args.max_new_tokens)
    print("\n=== Model Output ===\n", out)
    print("\n=== Evidence ===")
    for r in retrieved:
        print(f"- score={r['score']:.4f} source={r.get('source')} excerpt={r.get('text')[:200].replace(chr(10),' ')}...")

# ----------------------------
# FastAPI server mode (very minimal)
# ----------------------------
app = FastAPI(title="Minimal Local RAG")

class ChatRequest(BaseModel):
    user: str
    message: str
    snapshot: Dict[str, Any] = None
    top_k: int = 5

GLOBAL = {"retriever": None, "llm": None}

@app.on_event("startup")
def startup():
    # lazy load index & models at server start
    print("Server startup: loading index and models...")
    idx, metas = load_index_and_meta(INDEX_PREFIX)
    GLOBAL["retriever"] = Retriever(idx, metas, embed_model_name=EMBED_MODEL)
    try:
        GLOBAL["llm"] = LocalLLM(LOCAL_LLM_DIR, device=DEVICE)
    except Exception as e:
        print("Warning: Local LLM failed to load at startup:", e)
        GLOBAL["llm"] = None

@app.post("/chat")
def chat(req: ChatRequest):
    if GLOBAL["retriever"] is None:
        raise HTTPException(status_code=500, detail="Retriever not initialized")
    retriever = GLOBAL["retriever"]
    retrieved = retriever.retrieve(req.message, top_k=req.top_k)
    prompt = build_prompt(req.snapshot, retrieved, req.message)
    if GLOBAL["llm"] is None:
        raise HTTPException(status_code=500, detail="Local LLM not loaded; check logs")
    out = GLOBAL["llm"].generate(prompt, max_new_tokens=256)
    return {"reply": out, "evidence": retrieved, "prompt": prompt}

# ----------------------------
# Argparse & main
# ----------------------------
def parse_args():
    p = argparse.ArgumentParser()
    p.add_argument("--mode", choices=["cli","server"], default="cli")
    p.add_argument("--query", type=str, default=None)
    p.add_argument("--snapshot", type=str, default=None, help='JSON string of snapshot')
    p.add_argument("--index_prefix", type=str, default=INDEX_PREFIX)
    p.add_argument("--embed_model", type=str, default=EMBED_MODEL)
    p.add_argument("--model_dir", type=str, default=LOCAL_LLM_DIR)
    p.add_argument("--device", type=str, default=DEVICE)
    p.add_argument("--top_k", type=int, default=5)
    p.add_argument("--max_new_tokens", type=int, default=2048)
    return p.parse_args()

if __name__ == "__main__":
    args = parse_args()
    # set config from args
    INDEX_PREFIX = args.index_prefix
    EMBED_MODEL = args.embed_model
    LOCAL_LLM_DIR = args.model_dir
    DEVICE = args.device

    if args.mode == "cli":
        if not args.query:
            print("Provide --query when using cli mode.")
        else:
            cli_mode(args)
    else:
        # run server
        import uvicorn
        uvicorn.run("rag:app", host="0.0.0.0", port=8000, log_level="info")
