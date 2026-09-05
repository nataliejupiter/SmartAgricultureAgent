# SmartAgricultureAgent  
### 相关模型下载  
由于github上传限制，无法传大于100mb文件，所涉及模型需自己下载  
在`\RAG\model`下，要下载两个模型，`bge-small-zh-v1___5`和`qwen2.5-7b-instruct-q4_k_m.gguf`  
前者用于RAG检索，后者是大语言模型  
请自行到`modelscope`或`huggingface`下载，相关代码示例如下：  
```python
from modelscope import snapshot_download
model_dir = snapshot_download( model_id='Qwen/Qwen2.5-3B-Instruct-GGUF qwen2.5-3b-instruct-q5_k_m.gguf',
                               cache_dir='\RAG\model' )
print("done:", model_dir)
# modelscope download --model=qwen/Qwen2.5-3B-Instruct-GGUF --include "qwen2.5-3b-instruct-q4_k_m*.gguf" --local_dir .
```
`bge-small-zh-v1___5`下载同理  
### APP（RAG）使用说明  
#### 安装与启动方式
本软件由前端应用和 Python 后端服务两部分组成，使用前需保证前后端运行环境已准备完成。
- （1）下载`llama-server`服务，可在github官网搜索并下载`llama-b9114-bin-win-cpu-x64`服务。并且需要自行构建一农业知识的知识库文档（word或markdown形式均可）。

- （2）后端服务启动：在确保已配置好 Python 运行环境、llama-server服务和相关模型的前提下，首先需要打开llama-server服务，先进到llama-b9114-bin-win-cpu-x64目录下（使用命令`cd llama-b9114-bin-win-cpu-x64`），在命令提示符中输入如下命令：
`llama-server.exe -m D:\RAG\model\qwen_gguf\qwen2.5-7b-instruct-q4_k_m.gguf  -c 4096 --port  8080 --api`

此处指定后端访问的是8080端口上运行的llama-server模型服务。

- （3）启动 `rag_gguf.py` 所对应的 FastAPI 服务。在存放`rag_gguf.py`代码的目录下输入命令：`python rag_gguf.py --mode server --port 4567`。当前项目默认通过 `127.0.0.1:4567` 对外提供问答及RAG接口，此处可在代码里进行修改.

值得说明的是，此处可通过`--mode cli`指定为客户端模式进行测试，其会打印出相关token数量，预测下一个token所需时间（predicted_token_ms）等相关信息.
 
- （4）启动前端。前端运行方式有两种：1.在PC桌面使用自带的浏览器运行前端页面，通过浏览器直接访问部署后的页面地址。 2.在HbuilderX中编译代码，并将开发环境选择运行到浏览器，如图6所示。
- (5)后端环境：建议使用 Python 3.10 运行 FastAPI 服务，并安装 `requests`、`numpy`、`torch`、`sentence-transformers`、`faiss-cpu`、`uvicorn` 等依赖
