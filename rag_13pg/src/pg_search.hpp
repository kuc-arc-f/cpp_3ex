#include <iostream>
#include <vector>
#include <pqxx/pqxx> // libpqxx が必要
#include <sstream>
#include <string>

#include "http_client.hpp"

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
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ChatQuery, role, content)
struct ChatRequest {
    std::string model;
    std::vector<ChatQuery> messages;
    double temperature;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ChatRequest, model, messages, temperature)

struct SearchResponse {
    std::string ret;
    std::string text;
};   
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SearchResponse, ret, text)


class PgSearch {
private:
    std::string name = "";

public:
    explicit PgSearch(std::string str){}

    std::string pg_search(std::vector<float> embedding) {
      std::string ret = "";
      try {
          pqxx::connection conn("host=localhost user=root dbname=mydb password=admin");
          if (conn.is_open()) {
              cout << "Connected to database successfully." << endl;
          }

          pqxx::work txn(conn);

          vector<float> query_vector = embedding;

          stringstream ss;
          ss << "[";
          for (size_t i = 0; i < query_vector.size(); ++i) {
              if (i > 0) ss << ",";
              ss << query_vector[i];
          }
          ss << "]";
          string query_vec_str = ss.str();

          // 3. SQL実行 (<=> はコサイン距離)
          // 距離を "distance" として取得し、近い順(ASC)にソート
          //string sql = "SELECT id, embedding , content FROM documents ORDER BY embedding <-> '" + query_vec_str + "' LIMIT 1;";
          std::string sql = "SELECT id, content, embedding <=> '" + query_vec_str + "'"
                            + " AS distance FROM documents ORDER BY distance LIMIT 1";
                            
          //cout << "sql=" << sql << "\n";
          pqxx::result result = txn.exec(sql);

          cout << "Top similar vectors:\n";
          std::string matches = "";
          for (const auto& row : result) {
              int id = row["id"].as<int>();
              //string emb = row["embedding"].c_str();
              auto distance = row["distance"].as<float>();
              std::string content = row["content"].c_str();
              if (distance < 0.5) {
                  matches = content;
              }
              cout << "ID: " << id << ", distance: " << distance << endl;
          }
          txn.commit();

          ret = matches;
          return ret;
      } catch (const exception &e) {
          cerr << e.what() << endl;
          return ret;
      }
      return ret;
    }

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
    
    /**
    *
    * @param
    *
    * @return
    */
    void search_handler(const httplib::Request& req, httplib::Response& res) {
        std::string ret = "";
        if (req.get_header_value("Content-Type") != "application/json") {
            res.status = 400;
            res.set_content("Expected application/json", "text/plain");
            return;
        }        
        try{
            HttpClient client(30 /*timeout*/, true /*verify_ssl*/);
            json j = json::parse(req.body);

            std::string query = j.at("query").get<std::string>();
            std::cout << "query=" << query << "\n";

            QueryReq req_data;
            req_data.input = query;
            json j_req = req_data;            
            std::string json_str = j_req.dump();
            std::cout << "json_str : " << json_str << "\n";
            auto resp = client.post_json("http://localhost:8080/embedding", json_str);
            if (!resp.error.empty()) {
                std::cerr << "[ERROR] " << resp.error << "\n";
                return;
            }
            std::cout << "Status : " << resp.status_code << "\n";
            if (resp.is_ok()) {
                std::string str = resp.body;
                json j = json::parse(str);
                auto embedding = j[0]["embedding"];
                auto vec = embedding[0];
                int vlength = sizeof(vec) / sizeof(vec[0]);
                std::cout << "vlen=" << vec.size() << std::endl;

                double v1 = vec[0];
                double v2 = vec[1];        
                std::cout << v1 << ", " << v2 << std::endl;
                
                std::string resp_str = pg_search(vec);
                std::cout << "resp_str=" << resp_str << std::endl;
                std::string out_str = "日本語で、回答して欲しい。 \n要約して欲しい。\n\n";
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

                ChatQuery req2;
                req2.role = "user";
                req2.content = out_str;
                json j2 = req2;
                std::string json_str2 = j2.dump();
                //std::cout << "json_str2:" << json_str2 << std::endl;
                std::vector<ChatQuery> chat_messages;
                chat_messages.push_back(req2);

                std::string target_msg = "[";
                target_msg.append(json_str2);
                target_msg.append("]");
                ChatRequest req3;
                req3.model = "local-model";
                req3.messages = chat_messages;
                req3.temperature = 0.7;
                json j3 = req3; // 構造体を代入するだけ！
                std::string json_str3 = j3.dump();
                //std::cout << "json_str3:" << json_str3 << std::endl;
                std::string requestBody = json_str3;
                //std::cout << "requestBody:" << requestBody  << std::endl;
                auto resp2 = client.post_json(API_URL_CHAT, requestBody);
                if (!resp2.error.empty()) {
                    std::cerr << "[ERROR] " << resp2.error << "\n";
                    return;
                }
                std::string reply = extractContent(resp2.body);
                std::cout << "Assistant: " << reply << "\n\n"; 

                SearchResponse resp3;
                resp3.ret = "OK";
                resp3.text = reply;
                json j4 = resp3;
                std::string json_str4 = j4.dump();
                res.status = 201;
                res.set_content(json_str4, "application/json");
                return;
            }
            res.status = 201;
            res.set_content("OK", "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("Internal Server Error", "text/plain");
        }        
    } 

};
