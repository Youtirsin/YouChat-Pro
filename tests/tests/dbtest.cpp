#include "myDB/MyDB.h"
#include <bits/stdc++.h>
// using namespace std;

#define range(a) a.begin(), a.end()
#define vt vector
#define umap unordered_map
#define uset unordered_set
#define pq priority_queue


void println() { cout << endl; }
template<typename Type, typename... Types>
void println(const Type& arg, const Types&... args) { cout << arg; println(args...); }

template<typename T>
void printv(const vector<T> & v, string end=" ") { for (auto&& e : v) {cout << e << ' ';} cout << endl; }


int main() {
    SqlConnPool::Config config = {
        "127.0.0.1",
        "root",
        "123456",
        "youchatpro",
        10
    };
    
    const string REDIS_CONN = "tcp://127.0.0.1:6379";

    SqlConnWrapper conn((SqlConnPool::Instance(config)));

    auto res = conn.getConn()->db_select("select * from user");

    for (auto &&v : res) {
        for (auto &&e : v) {
            cout << e << ' ';
        }
        cout << endl;
    }

    return 0;
}

