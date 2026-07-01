# rag_23

 Version: 0.9.1

 date    : 2026/07/01
 
 update :

***

C++ CLI , RAG Search + SQLite DB

* embedding : Gemini-embedding-001
* gcc version 14.2.0 
* opencode use

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
* table add
```
sqlite3 ./example.db < table.sql
```
***
### env value
```
export GEMINI_API_KEY=your-key
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

https://zenn.dev/knaka0209/scraps/563c35e6ab6fe0
