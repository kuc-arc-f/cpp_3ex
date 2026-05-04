# http_9

 Version: 0.9.1

 date    : 2026/05/04

 update :

***

C++ React + cpp-httplib , todo server

* SQLite DB
* gcc version 14.2.0 
* node 22

***
### related

* https://github.com/nlohmann/json

* https://github.com/yhirose/cpp-httplib/blob/master/httplib.h

* dotenv-cpp
* https://github.com/laserpants/dotenv-cpp

***

### setup

* LIB

```
sudo apt-get update
sudo apt install nlohmann-json3-dev
sudo apt-get install libsqlite3-dev
```
***
* dotenv-cpp

```
git clone https://github.com/laserpants/dotenv-cpp.git
mkdir -p include
cp -rn <path-to-this-repo>/dotenv-cpp/include/ .
```

***
* httplib.h
```
cd ./include
wget https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.43.2.tar.gz
tar xvf v0.43.2.tar.gz
cp cpp-httplib-0.43.2/httplib.h  .
rm -fr cpp-httplib-0.43.2/
cd ..
```
***
* tree include
```
$ tree include/
include/
├── httplib.h
├── laserpants
│   └── dotenv
│       └── dotenv.h
├── my_page.hpp
├── my_todo.hpp
```
***
### front-build

```
npm i
npm run build
```

***
### .env
```
VALID_LOGIN=true
USER_NAME=user123@example.com
PASSWORD=123
```

***
* build
```
make all
```

***
* start
* localhost:8000 start

```
./server
```

***
### Blog

