# rag_18

 Version: 0.9.1

 date    : 2026/06/10

 update :

***

C++ CLI , RAG Search + SQLite DB

* embedding : Gemini-embedding-001
* model: gemma-4-E2B
* llama.cpp , llama-server 
* LLVM CLang

***

### setup


* llama-server start
* port 8090: gemma-4-E2B
```
#gemma-4-E2B

/usr/local/llama-b8642/llama-server -m /var/lm_data/unsloth/gemma-4-E2B-it-Q4_K_S.gguf \
 --chat-template-kwargs '{"enable_thinking": false}' --port 8090 
```

***
### related

https://huggingface.co/unsloth/gemma-4-E2B-it-GGUF

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
clang++ -std=c++17 -I./include -o embed embed.cpp -lcurl -lsqlite3 -luuid
clang++ -std=c++17 -I./include -o search search.cpp -lcurl -lsqlite3 -lm
```
***
* table : ./table.sql

```
sqlite3 ./example.db < table.sql
```

***
* env set , GEMINI_API_KEY
```
export GEMINI_API_KEY=
```

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

