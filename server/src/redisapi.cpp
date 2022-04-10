#include "redisapi.h"


RedisApi::RedisApi(const string& connection):
    redis(connection) {}


bool RedisApi::saveUser(const User& user) {
    string key_by_id = PROJECT_NAME + USER_BY_ID + std::to_string(user.id);
    string key_by_name = PROJECT_NAME + USER_BY_NAME + user.username;
    string key_all_id = PROJECT_NAME + ALL_USER_ID;

    std::unordered_map<string, string> map;

    map["id"] = std::to_string(user.id);
    map["username"] = user.username;
    map["password"] = user.password;

    redis.hmset(key_by_id, map.begin(), map.end()); // user by id
    redis.hmset(key_by_name, map.begin(), map.end()); // user by name
    redis.sadd(key_all_id, std::to_string(user.id)); // save to alluserid set

    redis.expire(key_by_id, std::chrono::seconds(DEFAULT_EXPIRE_TIME));
    redis.expire(key_by_name, std::chrono::seconds(DEFAULT_EXPIRE_TIME));

    return true;
}


std::unordered_set<int> RedisApi::getAllUserIds() {
    string key = PROJECT_NAME + ALL_USER_ID;

    std::unordered_set<string> searched;
    redis.smembers(key, std::inserter(searched, searched.begin()));

    std::unordered_set<int> res;
    for (auto &&e : searched) {
        res.insert(std::stoi(e));
    }
    
    return res;
}


shared_ptr<User> RedisApi::getUserWithId(int id) {
    string key = PROJECT_NAME + USER_BY_ID + std::to_string(id);

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
    string key = PROJECT_NAME + USER_BY_NAME + username;

    std::unordered_map<string, string> res;
    redis.hgetall(key, std::inserter(res, res.begin()));
    if (res.empty()) { return nullptr; }

    auto user = std::make_shared<User>();
    user->id = stoi(res["id"]);
    user->username = res["username"];
    user->password = res["password"];

    return user;
}


std::vector<Unread> RedisApi::getAllUnreadWithId(int id) {
    string key = PROJECT_NAME + UNREAD + std::to_string(id);

    std::unordered_map<string, string> searched;
    redis.hgetall(key, std::inserter(searched, searched.begin()));
    if (searched.empty()) { return {}; }

    std::vector<Unread> res;

    for (auto &&unread : searched) {
        res.push_back({ std::stoi(unread.first), std::stoi(unread.first) });
    }
    
    return res;
}


bool RedisApi::increUnreadBy(int keyid, int targetid, int num) {
    string key = PROJECT_NAME + UNREAD + std::to_string(keyid);
    string field = std::to_string(targetid);

    redis.hincrby(key, field, num);
    
    // delete if unread <= 0
    if (std::stoi(redis.hget(key, field).value()) <= 0) {
        redis.hdel(key, field);
    }

    return true;
}


bool RedisApi::clearUnread(int keyid, int targetid) {
    string key = PROJECT_NAME + UNREAD + std::to_string(keyid);
    string field = std::to_string(targetid);

    redis.hdel(key, field);
    return true;
}