# rag_29

 Version: 0.9.1

 date    : 2026/07/19
 
 update :

***

C++ CLI , RAG Search  PGVector DB

* OpenRouter
* embedding : Gemini-embedding-001
* gcc version 14.2.0 
* C/C++
* Linux

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

* .env
```
GEMINI_API_KEY=
OPENROUTER_API_KEY=
OPENROUTER_MODEL=deepseek/deepseek-v4-flash
```
***
* table: ./table.sql

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

