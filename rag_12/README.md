# rag_12

 Version: 0.9.1

 date    : 2026/04/07

 update :

***

C++ Server , RAG Search , React UI

* SQLite DB use
* modl: gemma-4-E2B-it-Q4_K_S.gguf
* Embedding-model : Qwen3-Embedding-0.6B-Q8_0.gguf
* llama.cpp , llama-server 
* gcc version 14.2.0 

***
### vector data add

https://github.com/kuc-arc-f/cpp_3ex/tree/main/rag_10

***

### setup

* llama-server start
* port 8080: Qwen3-Embedding-0.6B
* port 8090: gemma-4-E2B

```
#Qwen3-Embedding-0.6B
/home/user123/llama-server -m /var/lm_data/Qwen3-Embedding-0.6B-Q8_0.gguf --embedding  -c 1024 --port 8080

#gemma-4-E2B
/usr/local/llama-b8642/llama-server -m /var/lm_data/unsloth/gemma-4-E2B-it-Q4_K_S.gguf \
 --chat-template-kwargs '{"enable_thinking": false}' --port 8090 

```

***
### related

* gemma-4-E2B

https://huggingface.co/unsloth/gemma-4-E2B-it-GGUF

* Qwen3-Embedding-0.6B

https://huggingface.co/Qwen/Qwen3-Embedding-0.6B-GGUF

https://github.com/nlohmann/json

https://github.com/yhirose/cpp-httplib/blob/master/httplib.h

***
* LIB

```
sudo apt install uuid-dev
sudo apt install nlohmann-json3-dev
sudo apt install libcurl4-openssl-dev
sudo apt install libsqlite3-dev
```
***
* front build
```
npm i
npm run build
```

***
* build
```
make all
```

***
* start
* localhost:8000

```
./server
```


***
### Blog

