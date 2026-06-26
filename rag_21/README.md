# rag_21

 Version: 0.9.1

 date    : 2026/06/26

 update :

***

C++ CLI , RAG Search OpenRouter + Qdrant

* OpenRouter: openai/gpt-oss-20b:free
* embedding : Gemini-embedding-001
* gcc version 14.2.0 
* Linux

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

export OPENROUTER_API_KEY=your-key
export OPENROUTER_MODEL=openai/gpt-oss-20b:free
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

