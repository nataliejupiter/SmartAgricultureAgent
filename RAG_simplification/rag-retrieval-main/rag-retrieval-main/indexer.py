import re
import json
import faiss
from tqdm import tqdm
import numpy as np
from typing import List, Dict
from sentence_transformers import SentenceTransformer

# 读取文件

def load_md(path):
    with open(path, "r", encoding="utf-8") as f:
        return f.read()


# 主chunk切分
def split_main_chunks(content):
    chunks = content.split('---')
    return [c.strip() for c in chunks if c.strip()]


#  判断chunk类型

def classify_chunk(chunk):
    if "### 生长环境" in chunk:
        return "CROP"
    elif "阈值" in chunk or "决策规则" in chunk or "灌溉" in chunk:
        return "RULE"
    else:
        return "KNOWLEDGE"



#  作物chunk拆分（001–006）

def split_crop_chunk(chunk):
    results = []

    id_match = re.search(r'##\s*(CHUNK__\d+)\s+([^\n]+)', chunk)
    if not id_match:
        return []

    chunk_id, crop = id_match.group(1), id_match.group(2)

    sections = re.findall(r'(### [^\n]+)(.*?)(?=###|$)', chunk, re.S)

    for title, body in sections:
        results.append({
            "chunk_id": f"{chunk_id}_{title.strip()}",
            "crop": crop,
            "type": "CROP",
            "title": title.strip(),
            "text": body.strip(),
            "embedding_text": f"{crop} {title} {body.strip()}"
        })

    return results


#  规则chunk（保持整体）

def build_rule_chunk(chunk):
    id_match = re.search(r'##\s*(CHUNK__\d+)', chunk)
    chunk_id = id_match.group(1) if id_match else "UNKNOWN"

    return [{
        "chunk_id": chunk_id,
        "type": "RULE",
        "text": chunk,
        "embedding_text": chunk
    }]



# 知识chunk（按子标题拆）
def split_knowledge_chunk(chunk):
    results = []

    id_match = re.search(r'##\s*(CHUNK__\d+)\s+([^\n]+)', chunk)
    if not id_match:
        return []

    chunk_id, title_main = id_match.group(1), id_match.group(2)

    sections = re.findall(r'(### [^\n]+)(.*?)(?=###|$)', chunk, re.S)

    for title, body in sections:
        results.append({
            "chunk_id": f"{chunk_id}_{title.strip()}",
            "type": "KNOWLEDGE",
            "title": title.strip(),
            "text": body.strip(),
            "embedding_text": f"{title_main} {title} {body.strip()}"
        })

    return results

# 总构建逻辑

def build_all_chunks(content):
    main_chunks = split_main_chunks(content)

    all_chunks = []

    for chunk in main_chunks:
        ctype = classify_chunk(chunk)

        if ctype == "CROP":
            all_chunks.extend(split_crop_chunk(chunk))
        elif ctype == "RULE":
            all_chunks.extend(build_rule_chunk(chunk))
        else:
            all_chunks.extend(split_knowledge_chunk(chunk))

    return all_chunks


# embedding

def embed_chunks(chunks, model):
    texts = [c["embedding_text"] for c in chunks]

    embeddings = model.encode(
        texts,
        batch_size=8,
        show_progress_bar=True
    )

    return embeddings.astype("float32")



# FAISS

def build_and_save_faiss(embeddings, meta_list, prefix):
    faiss.normalize_L2(embeddings)

    index = faiss.IndexFlatIP(embeddings.shape[1])
    index.add(embeddings)

    faiss.write_index(index, f"{prefix}.index")

    with open(f"{prefix}_meta.jsonl", "w", encoding="utf-8") as f:
        for m in meta_list:
            f.write(json.dumps(m, ensure_ascii=False) + "\n")


#  查询

def search(query, model, index, meta, k=5):
    q_emb = model.encode([query], convert_to_numpy=True).astype("float32")
    faiss.normalize_L2(q_emb)

    D, I = index.search(q_emb, k)

    return [meta[i] for i in I[0]]

#  主程序

if __name__ == "__ain__":

    model = SentenceTransformer("D:\About_Competitions_and_Projects\innova_agri_agent\code\RAG\model\\bge\BAAI\\bge-small-zh-v1___5", device = "cpu")

    content = load_md("agriculture_rag_markdown_chunks.md")

    chunks = build_all_chunks(content)
    print(f"总chunk数: {len(chunks)}")

    embeddings = embed_chunks(chunks, model)

    build_and_save_faiss(embeddings, chunks, "agri_rag_v3")

    # 测试
    index = faiss.read_index("agri_rag_v3.index")
    meta = [json.loads(line) for line in open("agri_rag_v3_meta.jsonl", encoding="utf-8")]

    query = "蚜虫怎么防治"
    results = search(query, model, index, meta)

    for r in results:
        print("----")
        print(r["chunk_id"])
        print(r["text"][:150])
