#include <bits/stdc++.h>
#include "sw/redis++/redis++.h"
using namespace std;


int main() {
    auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");

    unordered_map<string, string> m = {
        {"key1", "val1"},
        {"key2", "val2"}
    };

    redis.hmset("key1", m.begin(), m.end());
    redis.hmset("key2", m.begin(), m.end());

    
    redis.expire("key1", std::chrono::seconds(600));
    redis.expire("key2", std::chrono::seconds(600));
    
    return 0;
}

