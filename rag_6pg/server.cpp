#include "httplib.h"
#include <iostream>
#include <nlohmann/json.hpp> // JSONライブラリ
#include <vector>
#include <string>
#include <mutex>
#include <sstream>

#include "pg_search.hpp"
#include "http_client.hpp"
#include "my_rag.hpp"

using json = nlohmann::json;

// インメモリストレージ
static std::mutex        g_mutex;

// ─────────────────────────────────────────
// CORS ヘッダー（ブラウザからのアクセス用）
// ─────────────────────────────────────────
void set_cors(httplib::Response& res) {
    res.set_header("Access-Control-Allow-Origin",  "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

// ─────────────────────────────────────────
// main
// ─────────────────────────────────────────
int main() {
    httplib::Server svr;

    // ── OPTIONS（プリフライト） ──────────────
    svr.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        set_cors(res);
        res.status = 204;
    });

    /**
    *
    * @param
    *
    * @return
    */    
    svr.Post("/search", [](const httplib::Request& req, httplib::Response& res) {
        std::lock_guard<std::mutex> lk(g_mutex);
        MyRag db(""); 
        db.search_handler(req, res);        
    });

    // ── 起動 ────────────────────────────────
    int port_no = 8000;
    std::cout << "TODO Server running on http://localhost:8000\n";
    std::cout << "Endpoints:\n"
              << "  GET    /todos\n"
              << "  POST   /todos        body: {\"title\":\"...\"}\n"
              << "  PUT    /todos/:id    body: {\"title\":\"...\",\"done\":true}\n"
              << "  DELETE /todos/:id\n";

    svr.listen("0.0.0.0", port_no);
    return 0;
}
