from modelscope import snapshot_download
model_dir = snapshot_download( model_id='Qwen/Qwen2.5-3B-Instruct-GGUF qwen2.5-3b-instruct-q5_k_m.gguf',
                               cache_dir='D:\About_Competitions_and_Projects\innova_agri_agent\code\RAG\model\\bge' )
print("done:", model_dir)
# modelscope download --model=qwen/Qwen2.5-3B-Instruct-GGUF --include "qwen2.5-3b-instruct-q4_k_m*.gguf" --local_dir .