#pragma once
#include <nlohmann/json.hpp> // JSONライブラリ
using json = nlohmann::json;

// ─────────────────────────────────────────
// データ構造
// ─────────────────────────────────────────
struct Todo_2 {
    int         id;
    std::string title;
    std::string content;
    int         public_val;
    int         food_orange;
    int         food_apple;
    int         food_banana;
    std::string pub_date;
    int         qty1;
    int         qty2;
    int         qty3;
    std::string created_at;
};
// ─────────────────────────────────────────
//  todo helper
// ─────────────────────────────────────────
class MyTodo_2 {
public:
    explicit MyTodo_2(const std::string& path) {
        if (sqlite3_open(path.c_str(), &db_) != SQLITE_OK)
            die("open");
        exec("PRAGMA journal_mode=WAL;");
        exec(R"(
            CREATE TABLE IF NOT EXISTS todo_2 (
                id         INTEGER PRIMARY KEY AUTOINCREMENT,
                title      TEXT    NOT NULL,
                done       INTEGER NOT NULL DEFAULT 0,
                created_at TEXT    NOT NULL
            );
        )");
    }
    ~MyTodo_2() { sqlite3_close(db_); }

    // ── Write ──────────────────────────────
    long long add(const std::string& title, const std::string& content, int pub, int orange, int apple, int banana, const std::string& pub_date, int q1, int q2, int q3) {
        std::string now = timestamp();
        sqlite3_stmt* s;
        prepare("INSERT INTO todo_2 (title, content, public, food_orange, food_apple, food_banana, pub_date, qty1, qty2, qty3, created_at) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", &s);
        sqlite3_bind_text(s, 1, title.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 2, content.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(s, 3, pub);
        sqlite3_bind_int(s, 4, orange);
        sqlite3_bind_int(s, 5, apple);
        sqlite3_bind_int(s, 6, banana);
        sqlite3_bind_text(s, 7, pub_date.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(s, 8, q1);
        sqlite3_bind_int(s, 9, q2);
        sqlite3_bind_int(s, 10, q3);
        sqlite3_bind_text(s, 11, now.c_str(),   -1, SQLITE_TRANSIENT);
        step_and_finalize(s);
        long long id = sqlite3_last_insert_rowid(db_);
        std::cout << "✓ 追加しました: [" << id << "] " << title << "\n";
        return id;
    }

    void update_details(int id, const std::string& title, const std::string& content, int pub, int orange, int apple, int banana, const std::string& pub_date, int q1, int q2, int q3) {
        sqlite3_stmt* s;
        prepare("UPDATE todo_2 SET title=?, content=?, public=?, food_orange=?, food_apple=?, food_banana=?, pub_date=?, qty1=?, qty2=?, qty3=? WHERE id=?;", &s);
        sqlite3_bind_text(s, 1, title.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(s, 2, content.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(s, 3, pub);
        sqlite3_bind_int(s, 4, orange);
        sqlite3_bind_int(s, 5, apple);
        sqlite3_bind_int(s, 6, banana);
        sqlite3_bind_text(s, 7, pub_date.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(s, 8, q1);
        sqlite3_bind_int(s, 9, q2);
        sqlite3_bind_int(s, 10, q3);
        sqlite3_bind_int(s, 11, id);
        step_and_finalize(s);
        if (sqlite3_changes(db_) == 0)
            std::cout << "ID " << id << " が見つかりません。\n";
        else
            std::cout << "✓ 更新しました: ID " << id << "\n";
    }

    void update(int id) {
        sqlite3_stmt* s;
        prepare("UPDATE todo_2 SET done = 1 WHERE id = ?;", &s);
        sqlite3_bind_int(s, 1, id);
        step_and_finalize(s);
        if (sqlite3_changes(db_) == 0)
            std::cout << "ID " << id << " が見つかりません。\n";
        else
            std::cout << "✓ 完了しました: ID " << id << "\n";
    }
    
    void reset_complete(int id) {
        sqlite3_stmt* s;
        prepare("UPDATE todo_2 SET done = 0 WHERE id = ?;", &s);
        sqlite3_bind_int(s, 1, id);
        step_and_finalize(s);
        if (sqlite3_changes(db_) == 0)
            std::cout << "ID " << id << " が見つかりません。\n";
        else
            std::cout << "✓ 未完了に戻しました: ID " << id << "\n";
    }

    void remove(int id) {
        sqlite3_stmt* s;
        prepare("DELETE FROM todo_2 WHERE id = ?;", &s);
        sqlite3_bind_int(s, 1, id);
        step_and_finalize(s);
        if (sqlite3_changes(db_) == 0)
            std::cout << "ID " << id << " が見つかりません。\n";
        else
            std::cout << "✓ 削除しました: ID " << id << "\n";
    }

    void clear_done() {
        exec("DELETE FROM todo_2 WHERE done = 1;");
        std::cout << "✓ 完了済みタスクをすべて削除しました。\n";
    }

    // ── Read ───────────────────────────────
    std::vector<Todo_2> list(const std::string& filter = "all") {
        std::string sql = "SELECT id, title, content, public, food_orange, food_apple, food_banana, pub_date, qty1, qty2, qty3, created_at FROM todo_2";
        sql += " ORDER BY id DESC LIMIT 20;";

        sqlite3_stmt* s;
        prepare(sql, &s);
        std::vector<Todo_2> rows;
        while (sqlite3_step(s) == SQLITE_ROW) {
            rows.push_back({
                sqlite3_column_int (s, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(s, 1)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 1)) : "",
                reinterpret_cast<const char*>(sqlite3_column_text(s, 2)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 2)) : "",
                sqlite3_column_int (s, 3),
                sqlite3_column_int (s, 4),
                sqlite3_column_int (s, 5),
                sqlite3_column_int (s, 6),
                reinterpret_cast<const char*>(sqlite3_column_text(s, 7)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 7)) : "",
                sqlite3_column_int (s, 8),
                sqlite3_column_int (s, 9),
                sqlite3_column_int (s, 10),
                reinterpret_cast<const char*>(sqlite3_column_text(s, 11)) ? reinterpret_cast<const char*>(sqlite3_column_text(s, 11)) : ""
            });
        }
        sqlite3_finalize(s);
        return rows;
    }

    std::string todo_to_json(const Todo_2& t) {
        std::ostringstream oss;
        oss << "{"
            << "\"id\":"           << t.id           << ","
            << "\"title\":\""      << t.title        << "\","
            << "\"content\":\""    << t.content      << "\","
            << "\"public\":"       << t.public_val   << ","
            << "\"food_orange\":"  << t.food_orange  << ","
            << "\"food_apple\":"   << t.food_apple   << ","
            << "\"food_banana\":"  << t.food_banana  << ","
            << "\"pub_date\":\""   << t.pub_date     << "\","
            << "\"qty1\":"         << t.qty1         << ","
            << "\"qty2\":"         << t.qty2         << ","
            << "\"qty3\":"         << t.qty3         << ","
            //<< "\"done\":"         << (t.done ? "true" : "false"),
            << "\"created_at\":\"" << t.created_at   << "\""
            << "}";
        return oss.str();
    }

    std::string todos_to_json(const std::vector<Todo_2>& todos) {
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
            json j = json::parse(req.body);

            std::string title = j.value("title", "");
            std::string content = j.value("content", "");
            int pub = j.value("public", 0);
            int orange = j.value("food_orange", 0);
            int apple = j.value("food_apple", 0);
            int banana = j.value("food_banana", 0);
            std::string pub_date = j.value("pub_date", "");
            int q1 = j.value("qty1", 0);
            int q2 = j.value("qty2", 0);
            int q3 = j.value("qty3", 0);

            update_details(id, title, content, pub, orange, apple, banana, pub_date, q1, q2, q3);
            res.status = 200;            
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
