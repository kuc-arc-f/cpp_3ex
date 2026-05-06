#pragma once
#include <nlohmann/json.hpp> // JSONライブラリ
using json = nlohmann::json;

// ─────────────────────────────────────────
// データ構造
// ─────────────────────────────────────────
struct Todo_3 {
    int         id;
    std::string title;
    std::string content;
    int         is_public;
    int         food_orange;
    int         food_apple;
    int         food_banana;
    int         food_melon;
    int         food_grape;
    std::string pub_date1;
    std::string pub_date2;
    std::string pub_date3;
    std::string pub_date4;
    std::string pub_date5;
    std::string pub_date6;
    int         qty1;
    int         qty2;
    int         qty3;
    int         qty4;
    int         qty5;
    int         qty6;
    bool        done;
    std::string created_at;
};
// ─────────────────────────────────────────
//  todo helper
// ─────────────────────────────────────────
class MyTodo_3 {
public:
    explicit MyTodo_3(const std::string& path) {
        if (sqlite3_open(path.c_str(), &db_) != SQLITE_OK)
            die("open");
        exec("PRAGMA journal_mode=WAL;");
    }
    ~MyTodo_3() { sqlite3_close(db_); }

    // ── Write ──────────────────────────────
    void add(const std::string& title, const std::string& content, int is_public, 
                int food_orange, int food_apple, int food_banana, int food_melon, int food_grape,
                const std::string& d1, const std::string& d2, const std::string& d3, 
                const std::string& d4, const std::string& d5, const std::string& d6,
                int q1, int q2, int q3, int q4, int q5, int q6) {
        std::string now = timestamp();
        sqlite3_stmt* s;
        prepare("INSERT INTO todo_3 (title, content, is_public, food_orange, food_apple, food_banana, food_melon, food_grape, pub_date1, pub_date2, pub_date3, pub_date4, pub_date5, pub_date6, qty1, qty2, qty3, qty4, qty5, qty6, created_at) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", &s);
        sqlite3_bind_text(s, 1, title.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 2, content.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(s, 3, is_public);
        sqlite3_bind_int(s, 4, food_orange);
        sqlite3_bind_int(s, 5, food_apple);
        sqlite3_bind_int(s, 6, food_banana);
        sqlite3_bind_int(s, 7, food_melon);
        sqlite3_bind_int(s, 8, food_grape);
        sqlite3_bind_text(s, 9, d1.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 10, d2.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 11, d3.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 12, d4.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 13, d5.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 14, d6.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(s, 15, q1);
        sqlite3_bind_int(s, 16, q2);
        sqlite3_bind_int(s, 17, q3);
        sqlite3_bind_int(s, 18, q4);
        sqlite3_bind_int(s, 19, q5);
        sqlite3_bind_int(s, 20, q6);
        sqlite3_bind_text(s, 21, now.c_str(), -1, SQLITE_TRANSIENT);
        step_and_finalize(s);
        std::cout << "✓ 追加しました: [" << sqlite3_last_insert_rowid(db_) << "] " << title << "\n";
    }

    void update(int id) {
        sqlite3_stmt* s;
        prepare("UPDATE todo_3 SET done = 1 WHERE id = ?;", &s);
        sqlite3_bind_int(s, 1, id);
        step_and_finalize(s);
        if (sqlite3_changes(db_) == 0)
            std::cout << "ID " << id << " が見つかりません。\n";
        else
            std::cout << "✓ 完了しました: ID " << id << "\n";
    }
    
    void update_todo(int id, const std::string& title, const std::string& content, int is_public, 
                     int food_orange, int food_apple, int food_banana, int food_melon, int food_grape,
                     const std::string& d1, const std::string& d2, const std::string& d3, 
                     const std::string& d4, const std::string& d5, const std::string& d6,
                     int q1, int q2, int q3, int q4, int q5, int q6) {
        sqlite3_stmt* s;
        prepare("UPDATE todo_3 SET title=?, content=?, is_public=?, food_orange=?, food_apple=?, food_banana=?, food_melon=?, food_grape=?, pub_date1=?, pub_date2=?, pub_date3=?, pub_date4=?, pub_date5=?, pub_date6=?, qty1=?, qty2=?, qty3=?, qty4=?, qty5=?, qty6=? WHERE id=?;", &s);
        sqlite3_bind_text(s, 1, title.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 2, content.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(s, 3, is_public);
        sqlite3_bind_int(s, 4, food_orange);
        sqlite3_bind_int(s, 5, food_apple);
        sqlite3_bind_int(s, 6, food_banana);
        sqlite3_bind_int(s, 7, food_melon);
        sqlite3_bind_int(s, 8, food_grape);
        sqlite3_bind_text(s, 9, d1.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 10, d2.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 11, d3.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 12, d4.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 13, d5.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 14, d6.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(s, 15, q1);
        sqlite3_bind_int(s, 16, q2);
        sqlite3_bind_int(s, 17, q3);
        sqlite3_bind_int(s, 18, q4);
        sqlite3_bind_int(s, 19, q5);
        sqlite3_bind_int(s, 20, q6);
        sqlite3_bind_int(s, 21, id);
        step_and_finalize(s);
        if (sqlite3_changes(db_) == 0)
            std::cout << "ID " << id << " が見つかりません。\n";
        else
            std::cout << "✓ 更新しました: ID " << id << "\n";
    }
        
    void reset_complete(int id) {
        sqlite3_stmt* s;
        prepare("UPDATE todo_3 SET done = 0 WHERE id = ?;", &s);
        sqlite3_bind_int(s, 1, id);
        step_and_finalize(s);
        if (sqlite3_changes(db_) == 0)
            std::cout << "ID " << id << " が見つかりません。\n";
        else
            std::cout << "✓ 未完了に戻しました: ID " << id << "\n";
    }

    void remove(int id) {
        sqlite3_stmt* s;
        prepare("DELETE FROM todo_3 WHERE id = ?;", &s);
        sqlite3_bind_int(s, 1, id);
        step_and_finalize(s);
        if (sqlite3_changes(db_) == 0)
            std::cout << "ID " << id << " が見つかりません。\n";
        else
            std::cout << "✓ 削除しました: ID " << id << "\n";
    }

    void clear_done() {
        exec("DELETE FROM todo_3 WHERE done = 1;");
        std::cout << "✓ 完了済みタスクをすべて削除しました。\n";
    }

    // ── Read ───────────────────────────────
    std::vector<Todo_3> list(const std::string& filter = "all") {
        std::string sql = "SELECT id, title, content, is_public, food_orange, food_apple, food_banana, food_melon, food_grape, pub_date1, pub_date2, pub_date3, pub_date4, pub_date5, pub_date6, qty1, qty2, qty3, qty4, qty5, qty6, created_at FROM todo_3";
        //if (filter == "pending")  sql += " WHERE done = 0";
        //if (filter == "done")     sql += " WHERE done = 1";
        sql += " ORDER BY id DESC;";

        sqlite3_stmt* s;
        prepare(sql, &s);
        std::vector<Todo_3> rows;
        while (sqlite3_step(s) == SQLITE_ROW) {
            rows.push_back({
                sqlite3_column_int (s, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(s, 1)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 1)) : "",
                reinterpret_cast<const char*>(sqlite3_column_text(s, 2)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 2)) : "",
                sqlite3_column_int (s, 3),
                sqlite3_column_int (s, 4),
                sqlite3_column_int (s, 5),
                sqlite3_column_int (s, 6),
                sqlite3_column_int (s, 7),
                sqlite3_column_int (s, 8),
                reinterpret_cast<const char*>(sqlite3_column_text(s, 9)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 9)) : "",
                reinterpret_cast<const char*>(sqlite3_column_text(s, 10)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 10)) : "",
                reinterpret_cast<const char*>(sqlite3_column_text(s, 11)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 11)) : "",
                reinterpret_cast<const char*>(sqlite3_column_text(s, 12)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 12)) : "",
                reinterpret_cast<const char*>(sqlite3_column_text(s, 13)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 13)) : "",
                reinterpret_cast<const char*>(sqlite3_column_text(s, 14)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 14)) : "",
                sqlite3_column_int (s, 15),
                sqlite3_column_int (s, 16),
                sqlite3_column_int (s, 17),
                sqlite3_column_int (s, 18),
                sqlite3_column_int (s, 19),
                sqlite3_column_int (s, 20),
                false, // done (not in SELECT, keeping default)
                reinterpret_cast<const char*>(sqlite3_column_text(s, 21)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 21)) : ""
            });
        }
        sqlite3_finalize(s);
        return rows;
    }

    std::string todo_to_json(const Todo_3& t) {
        std::ostringstream oss;
        oss << "{"
            << "\"id\":"    << t.id           << ","
            << "\"title\":\"" << t.title      << "\","
            << "\"content\":\"" << t.content  << "\","
            << "\"is_public\":" << t.is_public << ","
            << "\"food_orange\":" << t.food_orange << ","
            << "\"food_apple\":" << t.food_apple << ","
            << "\"food_banana\":" << t.food_banana << ","
            << "\"food_melon\":" << t.food_melon << ","
            << "\"food_grape\":" << t.food_grape << ","
            << "\"pub_date1\":\"" << t.pub_date1 << "\","
            << "\"pub_date2\":\"" << t.pub_date2 << "\","
            << "\"pub_date3\":\"" << t.pub_date3 << "\","
            << "\"pub_date4\":\"" << t.pub_date4 << "\","
            << "\"pub_date5\":\"" << t.pub_date5 << "\","
            << "\"pub_date6\":\"" << t.pub_date6 << "\","
            << "\"qty1\":" << t.qty1 << ","
            << "\"qty2\":" << t.qty2 << ","
            << "\"qty3\":" << t.qty3 << ","
            << "\"qty4\":" << t.qty4 << ","
            << "\"qty5\":" << t.qty5 << ","
            << "\"qty6\":" << t.qty6 << ","
            << "\"done\":"  << 0
            << "}";
        return oss.str();
    }

    std::string todos_to_json(const std::vector<Todo_3>& todos) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < todos.size(); ++i) {
            if (i > 0) oss << ",";
            oss << todo_to_json(todos[i]);
        }
        oss << "]";
        return oss.str();
    }
    /**
    *
    * @param
    *
    * @return
    */
    void todos_list_handler(httplib::Response& res) {
        std::string ret = "";
        try{
            auto todos = list("all");
            auto resp = todos_to_json(todos);
            res.status = 201;
            res.set_content(resp, "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("Internal Server Error", "text/plain");
        }        
    }
    /**
    *
    * @param
    *
    * @return
    */
    void todos_add_handler(const httplib::Request& req, httplib::Response& res) {
    }
    /**
    *
    * @param
    *
    * @return
    */    
    void todos_update_handler(const httplib::Request& req, httplib::Response& res) {
        std::string ret = "";
        if (req.get_header_value("Content-Type") != "application/json") {
            res.status = 400;
            res.set_content("Expected application/json", "text/plain");
            return;
        }        
        try{
            int id = std::stoi(req.matches[1]);
            std::cout << "id=" << id << "\n";
            update(id);
            res.status = 201;
            res.set_content("OK", "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("Internal Server Error", "text/plain");
        }        
    }    
    /**
    *
    * @param
    *
    * @return
    */
    void todos_delete_handler(const httplib::Request& req, httplib::Response& res) {
        std::string ret = "";
        int id = std::stoi(req.matches[1]);
        try{
            remove(id);
            res.status = 200;
            res.set_content("OK", "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("Internal Server Error", "text/plain");
        }
    }

private:
    sqlite3* db_ = nullptr;

    void exec(const std::string& sql) {
        char* err = nullptr;
        if (sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err) != SQLITE_OK) {
            std::string msg = err ? err : "unknown";
            sqlite3_free(err);
            die(msg);
        }
    }

    void prepare(const std::string& sql, sqlite3_stmt** s) {
        if (sqlite3_prepare_v2(db_, sql.c_str(), -1, s, nullptr) != SQLITE_OK)
            die(sqlite3_errmsg(db_));
    }

    void step_and_finalize(sqlite3_stmt* s) {
        sqlite3_step(s);
        sqlite3_finalize(s);
    }

    static std::string timestamp() {
        std::time_t t = std::time(nullptr);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
        return buf;
    }

    [[noreturn]] static void die(const std::string& msg) {
        std::cerr << "DB error: " << msg << "\n";
        std::exit(1);
    }
};
