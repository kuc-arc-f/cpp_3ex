
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp> // JSONライブラリ
#include <random>

#include "qdrant_client.hpp"
#include "http_client.hpp"
#include "include/GeminiEmbeddingClient.hpp"
#include "include/openrouter_client.hpp"

const std::string COLLECTION = "document-1";
const size_t      VECTOR_DIM = 3072;  // ベクトル次元

using namespace std;

using json = nlohmann::json;

const std::string API_URL_CHAT = "http://localhost:8090/v1/chat/completions";

struct QueryReq {
    std::string input;
};   
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(QueryReq, input)
struct ChatQuery {
    std::string role;
    std::string content;
};
// これ一行で、QueryReq <=> json の変換が魔法のように可能になります
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ChatQuery, role, content)
struct ChatRequest {
    std::string model;
    std::vector<ChatQuery> messages;
    double temperature;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ChatRequest, model, messages, temperature)

std::string extractContent(const std::string& jsonStr)
{
    try {
        auto j = nlohmann::json::parse(jsonStr);
        return j["choices"][0]["message"]["content"].get<std::string>();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] JSON parse: " << e.what() << "\n";
        return "";
    }
}
// ─────────────────────────────────────────────
// main : 動作確認サンプル
// ─────────────────────────────────────────────
int main(int argc, char* argv[])
{
    const char* api_key = std::getenv("OPENROUTER_API_KEY");
    if (api_key != nullptr) {
        std::cout << "OPENROUTER.api_key:" << api_key << std::endl;
    }else{
        std::cerr << "Error: OPENROUTER_API_KEY environment variable not set" << std::endl;
        std::cerr << "Please set it with: export OPENROUTER_API_KEY=your_api_key_here" << std::endl;
        return -1;
    }    
    const char* model_name = std::getenv("OPENROUTER_MODEL");
    if (model_name != nullptr) {
        std::cout << "model_name:" << model_name << std::endl;
    }else{
        std::cerr << "Error: OPENROUTER_MODEL environment variable not set" << std::endl;
        return -1;
    }      

    if(argc < 2) {
        std::cerr << "[ERROR] argment none" << "\n";
        return 0;
    }
    int arg_count = argc;
    std::string query = argv[1];
    std::cout << "query=" << query << "\n";

    HttpClient client(30 /*timeout*/, true /*verify_ssl*/);
    std::string api_url = "";
    QdrantClient qdrant_client("localhost", 6333);
    std::cout << "=== Qdrant C++ クライアント===\n\n";

    try{
        auto embeddings = EmbeddingStart(query);
        std::cout << "vlen=" << embeddings.size() << std::endl;

        // =========================================================
        // 4. ベクトル検索 (類似検索)
        // =========================================================
        std::cout << "--- ベクトル類似検索 (Top N rec) ---\n";
        std::cout << "クエリベクトル: ";
        std::cout << "\n\n";        
        auto results = qdrant_client.search(COLLECTION, embeddings, 1);
        std::string matches = "";
        for (const auto& r : results) {
            std::cout << "  score: " << std::fixed << std::setprecision(4) << r.score
                      << "\n";
            std::cout << "r.score=" << r.score << "\n";
            std::string content = r.payload["content"].get<std::string>();
            if(r.score > 0.6) {
                matches = content;
            }
        }
        std::cout << "\n";

        std::string out_str = "要約して欲しい。\n";
        std::string resp_str = matches;
        if(resp_str.empty()){
            out_str.append("user query: ");
            out_str.append(query);
            out_str.append(" \n");
        }else{
            out_str.append("context:");
            out_str.append(resp_str);
            out_str.append("\n user query: ");
            out_str.append(query);
            out_str.append(" \n");
        }
        std::cout << out_str  << std::endl;

        OpenRouterClient client(api_key);
        auto response = client.sendChatCompletion(
            model_name,
            out_str,
            1.0,
            2000
        );
        if (response.has_value()) {
            std::cout << "Response: " << response.value() << std::endl;
            //auto outStr = response.value();
            //ret = outStr;
            return -1;
        } else {
            std::cerr << "Failed to get response from API" << std::endl;
            return -1;
        }
        return 1;
    } catch (const std::exception& e) {
        std::cout << "Error , main" << std::endl;
        return 0;
    }        
    return 0;
}


