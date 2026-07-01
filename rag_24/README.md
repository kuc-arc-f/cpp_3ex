# rag_24

 Version: 0.9.1

 date    : 2026/07/02

 update :

***

C++ CLI , RAG Search + Qdrant

* OpenCode: Agent skills
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

https://zenn.dev/knaka0209/scraps/ba3eba28d73836

