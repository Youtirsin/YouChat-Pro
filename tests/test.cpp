#include <bits/stdc++.h>
#include "sw/redis++/redis++.h"
using namespace std;


int main() {
    auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");
    
    redis.hincrby("test", "id", 123);

    auto res = redis.hget("test", "id");

    cout << res.value() << endl;

    return 0;
}

