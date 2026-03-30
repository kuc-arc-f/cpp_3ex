# rag_8pg

 Version: 0.9.1

 date    : 2026/03/27

 update :

***

C++ CLI , RAG Search  PGVector DB

* modl: Qwen3.5-2B-Q4_K_S.gguf
* Embedding-model : Qwen3-Embedding-0.6B-Q8_0.gguf
* llama.cpp , llama-server 
* gcc version 14.2.0 

***

### setup


* llama-server start
* port 8080: Qwen3-Embedding-0.6B
* port 8090: Qwen3.5-2B

```
#Qwen3-Embedding-0.6B
/home/user123/llama-server -m /var/lm_data/Qwen3-Embedding-0.6B-Q8_0.gguf --embedding  -c 1024 --port 8080

#Qwen3.5-2B
/home/user123/llama-server -m /var/lm_data/unsloth/Qwen3.5-2B-GGUF/Qwen3.5-2B-Q4_K_S.gguf \
 --chat-template-kwargs '{"enable_thinking": false}' --port 8090 

```

***
### related

https://huggingface.co/unsloth/Qwen3.5-2B-GGUF

https://huggingface.co/Qwen/Qwen3-Embedding-0.6B-GGUF

***
* LIB

```
sudo apt install libpq-dev libpqxx-dev
sudo apt install nlohmann-json3-dev
sudo apt install libcurl4-openssl-dev
```

***
* build
```
g++ -std=c++17 -I./include -o embed embed.cpp -lcurl -lpqxx -lpq
g++ -std=c++17 -I./include -o search search.cpp -lcurl -lpqxx -lpq
```
***
* table pgvector: ./table.sql

***
* vector data add
```
./embed ./data
```

***
* search
```
./search  hello
```

***
### Blog

