'''
import torch
from transformers import AutoTokenizer, AutoModelForCausalLM

# 你的本地模型路径
LOCAL_LLM_DIR = r"D:\About_Competitions_and_Projects\模型量化\deployInRK3588\DeepSeek-R1-Distill-Qwen-1.5B"

def load_model(model_dir: str):
    tokenizer = AutoTokenizer.from_pretrained(
        model_dir,
        trust_remote_code=True
    )

    model = AutoModelForCausalLM.from_pretrained(
        model_dir,
        trust_remote_code=True,
        torch_dtype=torch.float16 if torch.cuda.is_available() else torch.float32,
        device_map="auto" if torch.cuda.is_available() else None
    )

    model.eval()
    return tokenizer, model

def generate_answer(tokenizer, model, query: str, max_new_tokens: int = 2048):
    # 使用 chat template，适配聊天模型
    messages = [
        {"role": "user", "content": query}
    ]

    if hasattr(tokenizer, "apply_chat_template"):
        input_text = tokenizer.apply_chat_template(
            messages,
            tokenize=False,
            add_generation_prompt=True
        )
    else:
        input_text = query

    inputs = tokenizer(
        input_text,
        return_tensors="pt"
    )

    # 放到模型所在设备
    if torch.cuda.is_available():
        inputs = {k: v.to(model.device) for k, v in inputs.items()}
    else:
        inputs = {k: v.to("cpu") for k, v in inputs.items()}

    with torch.no_grad():
        output_ids = model.generate(
            **inputs,
            max_new_tokens=max_new_tokens,
            do_sample=True,
            temperature=0.7,
            top_p=0.9,
            repetition_penalty=1.05
        )

    # 只截取新生成的部分
    new_tokens = output_ids[0][inputs["input_ids"].shape[-1]:]
    answer = tokenizer.decode(new_tokens, skip_special_tokens=True)
    return answer.strip()

def main():
    tokenizer, model = load_model(LOCAL_LLM_DIR)
    print("模型加载完成，可以开始对话。输入 exit 退出。")

    while True:
        query = input("\n用户：").strip()
        if query.lower() in ["exit", "quit", "q"]:
            break

        answer = generate_answer(tokenizer, model, query)
        print(f"模型：{answer}")

if __name__ == "__main__":
    main()
'''

import requests

url = "http://127.0.0.1:8080/v1/chat/completions"

headers = {
    "Content-Type": "application/json"
}

while True:
    user_input = input("你：")

    data = {
        "model": "qwen2.5-7b-instruct-q4_k_m",
        "messages": [
            {"role": "user", "content": user_input}
        ],
        "temperature": 0.7,
        "max_tokens": 1024
    }

    response = requests.post(url, headers=headers, json=data)
    result = response.json()

    reply = result["choices"][0]["message"]["content"]
    print("模型：", reply)