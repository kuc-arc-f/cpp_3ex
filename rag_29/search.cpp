
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp> // JSONライブラリ

#include "include/dotenv.h"
#include "pg_search.hpp"
#include "include/GeminiEmbeddingClient.hpp"
#include "include/openrouter_client.hpp"

using namespace std;

using json = nlohmann::json;

// ─────────────────────────────────────────────
// main : 動作確認サンプル
// ─────────────────────────────────────────────
int main(int argc, char* argv[])
{
    int ret = -1;
    dotenv::init();
    // API_KEYを環境変数から取得（または直接設定）
    const char* api_key = std::getenv("OPENROUTER_API_KEY");
    if (api_key != nullptr) {
        //std::cout << "api_key:" << api_key << std::endl;
    }else{
        std::cerr << "Error: OPENROUTER_API_KEY environment variable not set" << std::endl;
        std::cerr << "Please set it with: export OPENROUTER_API_KEY=your_api_key_here" << std::endl;
        return ret;
    }      
    const char* model_name = std::getenv("OPENROUTER_MODEL");
    if (!model_name) {
        std::cerr << "Error: OPENROUTER_MODEL environment variable not set" << std::endl;
        return ret;
    }    
    //std::cout << "arg_count=" << argc << "\n";
    //std::cout << "argv[0]=" << argv[0] << "\n";
    if(argc < 2) {
        std::cerr << "[ERROR] argment none" << "\n";
        return 0;
    }
    int arg_count = argc;
    std::string query = argv[1];
    std::cout << "query=" << query << "\n";
    auto embeddings = EmbeddingStart(query);
    std::cout << "vlen=" << embeddings.size() << std::endl;
    //return -1;
    try{
        PgSearch app("");
        std::string out_str = "日本語で、回答して欲しい。 \n要約して欲しい。\n\n";
        std::string resp_str = app.pg_search(embeddings);
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
        //std::cout << "Assistant: " << reply << "\n\n"; 
        OpenRouterClient client(api_key);
        // チャットリクエストの送信
        auto response = client.sendChatCompletion(
            model_name,
            out_str,
            1.0,
            2000
        );

        if (response.has_value()) {
            auto outStr = response.value();
            std::cout << "Response: " << outStr << std::endl;
            //ret = outStr;
            return ret;
        } else {
            std::cerr << "Failed to get response from API" << std::endl;
            return ret;
        }

        return ret;
    } catch (const std::exception& e) {
        std::cout << "Error , main" << std::endl;
        return 0;
    }        
    return 0;
}

