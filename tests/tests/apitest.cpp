#include <bits/stdc++.h>
#include <jsoncpp/json/json.h>
#include "DBApi.h"
using namespace std;

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

    // const string REDIS_CONN = "tcp://127.0.0.1:6379";

    DBApi api(config);

    // api.savePrivateMsg("han", "test1", "hello");

    // api.saveBroadcastMsg("han", "screw it");

    auto res = api.loadBroadcastMsg(1, 1, 10);

    println(res);
    
    return 0;
}

