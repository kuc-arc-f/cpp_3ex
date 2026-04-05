# rag_10

 Version: 0.9.1

 date    : 2026/04/05

 update :

***

C++ CLI , RAG Search + SQLite DB

* modl: gemma-4-E2B-it-Q4_K_S.gguf
* Embedding-model : Qwen3-Embedding-0.6B-Q8_0.gguf
* llama.cpp , llama-server 
* gcc version 14.2.0 

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

https://huggingface.co/unsloth/gemma-4-E2B-it-GGUF

https://huggingface.co/Qwen/Qwen3-Embedding-0.6B-GGUF

***
* LIB

```
sudo apt install uuid-dev
sudo apt install nlohmann-json3-dev
sudo apt install libcurl4-openssl-dev
sudo apt install libsqlite3-dev
```

***
* build
```
g++ -std=c++17 -I./include -o embed embed.cpp -lcurl -lsqlite3 -luuid
g++ -std=c++17 -I./include -o search search.cpp -lcurl -lsqlite3 -lm
```
***
* table : ./table.sql

```
CREATE TABLE IF NOT EXISTS document (
  id TEXT PRIMARY KEY,
  sessid TEXT,
  name TEXT,
  content TEXT,
  embeddings BLOB
);

PRAGMA journal_mode = WAL;
```

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

