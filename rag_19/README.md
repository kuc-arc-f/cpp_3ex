# rag_19

 Version: 0.9.1

 date    : 2026/06/19

 update :

***

C++ CLI , RAG Search + Qdrant DB

* embedding : Gemini-embedding-001
* model: gemma-4-E2B
* llama.cpp , llama-server 
* gcc version 14.2.0 
* Linux

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
```

***
* build
```
g++ -std=c++17 -o init init.cpp -lcurl
g++ -std=c++17 -o embed embed.cpp -lcurl -luuid
g++ -std=c++17 -o search search.cpp -lcurl -luuid
```

***
* env set , GEMINI_API_KEY

```
export GEMINI_API_KEY=your-key
```
***
* init-DB
```
./init
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

