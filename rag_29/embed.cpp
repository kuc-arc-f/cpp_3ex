
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp> // JSONライブラリ

#include "pg_add.hpp"
#include "include/GeminiEmbeddingClient.hpp"

using namespace std;

using json = nlohmann::json;

struct QueryReq {
    std::string input;
};   
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(QueryReq, input)

/**
*
* @param
*
* @return
*/
int ebmed(std::string query){
    int ret = 0;
    auto embeddings = EmbeddingStart(query);
    std::cout << "vlen=" << embeddings.size() << std::endl;

    try{
        PgAdd app("");
        app.pg_add(embeddings, query);
    } catch (const std::exception& e) {
        std::cout << "Error , main" << std::endl;
        return 1;
    }        
    return 0;
}

// 1ファイル分のデータを保持する構造体
struct TextFile {
    std::string filename;
    std::vector<std::string> lines;
};

// .txt ファイルを読み込んで行を返す
TextFile loadTextFile(const std::filesystem::path& filepath) {
    TextFile tf;
    tf.filename = filepath.filename().string();

    std::ifstream ifs(filepath);
    if (!ifs.is_open()) {
        std::cerr << "[警告] ファイルを開けません: " << filepath << "\n";
        return tf;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        tf.lines.push_back(line);
    }
    return tf;
}

// 読み込んだデータを表示する
void printTextFiles(const std::vector<TextFile>& files) {
    for (const auto& tf : files) {
        std::cout << "========================================\n";
        std::cout << "ファイル名: " << tf.filename << "\n";
        std::cout << "行数      : " << tf.lines.size() << "\n";
        std::cout << "----------------------------------------\n";
        std:string target = "";
        for (size_t i = 0; i < tf.lines.size(); ++i) {
            //std::cout << "[" << i + 1 << "] " << tf.lines[i] << "\n";
            std::string tmp = tf.lines[i] + "\n";
            target.append(tmp);
        }
        std::cout <<  target << "\n";
        int resp = ebmed(target);
        std::cout << "resp=" << resp << "\n";
    }
    std::cout << "========================================\n";
}
/**
*
* @param
*
* @return
*/
int main(int argc, char* argv[])
{
    // 引数でフォルダを指定、省略時はカレントディレクトリ
    std::string dirPath = (argc >= 2) ? argv[1] : ".";
    if(argc < 2) {
        std::cerr << "[ERROR] argment none" << "\n";
        return 0;
    }    

    if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath)) {
        std::cerr << "[エラー] 有効なディレクトリではありません: " << dirPath << "\n";
        return 1;
    }

    std::cout << "対象フォルダ: " << std::filesystem::absolute(dirPath) << "\n\n";

    std::vector<TextFile> allFiles;

    // フォルダ内の .txt ファイルをすべて列挙
    for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
        //if (entry.is_regular_file() && entry.path().extension() == ".txt") {
        if (entry.is_regular_file() && 
        (entry.path().extension() == ".txt" || entry.path().extension() == ".md") ) {
            TextFile tf = loadTextFile(entry.path());
            allFiles.push_back(std::move(tf));
        }
    }

    if (allFiles.empty()) {
        std::cout << ".txt ファイルが見つかりませんでした。\n";
        return 0;
    }

    std::cout << "読み込んだファイル数: " << allFiles.size() << "\n\n";
    printTextFiles(allFiles);

    return 0;
}

