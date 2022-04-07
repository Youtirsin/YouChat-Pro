#include "redisapi.h"


RedisApi::RedisApi(const string& connection):
    redis(connection) {}


bool RedisApi::saveUser(const User& user) {
    string key1 = PROJECT_NAME + USERID_TO_NAME + std::to_string(user.id);
    string key2 = PROJECT_NAME + USERID_TO_NAME + user.username;

    std::unordered_map<string, string> map;

    map["id"] = std::to_string(user.id);
    map["username"] = user.username;
    map["password"] = user.password;

    redis.hmset(key1, map.begin(), map.end());
    redis.hmset(key2, map.begin(), map.end());

    redis.expire(key1, std::chrono::seconds(DEFAULT_EXPIRE_TIME));
    redis.expire(key2, std::chrono::seconds(DEFAULT_EXPIRE_TIME));

    return true;
}


shared_ptr<User> RedisApi::getUserWithId(int id) {
    string key = PROJECT_NAME + USERID_TO_NAME + std::to_string(id);

    std::unordered_map<string, string> res;

    redis.hgetall(key, std::inserter(res, res.begin()));
    if (res.empty()) { return nullptr; }

    auto user = std::make_shared<User>();
    user->id = stoi(res["id"]);
    user->username = res["username"];
    user->password = res["password"];

    return user;
}


shared_ptr<User> RedisApi::getUserWithName(const string& username) {
    string key = PROJECT_NAME + USERID_TO_NAME + username;

    std::unordered_map<string, string> res;

    redis.hgetall(key, std::inserter(res, res.begin()));
    if (res.empty()) { return nullptr; }

    auto user = std::make_shared<User>();
    user->id = stoi(res["id"]);
    user->username = res["username"];
    user->password = res["password"];

    return user;
}
