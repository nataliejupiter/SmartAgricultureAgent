import requests

resp = requests.post(
    "http://127.0.0.1:8080/v1/chat/completions",
    json={
        "model": "D:\About_Competitions_and_Projects\innova_agri_agent\code\RAG\model\qwen_gguf\qwen2.5-7b-instruct-q4_k_m.gguf",
        "messages": [
            {"role": "user", "content": "你好"}
        ]
    }
)

print(resp.json())