#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "sw/redis++/redis++.h"

#include "entity.h"

using std::shared_ptr;

using std::string;
using std::cout;
using std::endl;

class RedisApi {
public:
    RedisApi(const string& connection);

    bool saveUser(const User& user);

    std::unordered_set<int> getAllUserIds();

    shared_ptr<User> getUserWithId(int id);

    shared_ptr<User> getUserWithName(const string& username);

    std::vector<Unread> getAllUnreadWithId(int id);

    bool increUnreadBy(int keyid, int targetid, int num);

    bool clearUnread(int keyid, int targetid);
private:
    sw::redis::Redis redis;

    // project prefix
    const string PROJECT_NAME = "youchatpro:";

    // business prefix
    const string USER_BY_ID = "userbyid:"; // hash
    const string USER_BY_NAME = "userbyname:"; // hash
    const string UNREAD = "unread:"; // hash

    // business name
    const string ALL_USER_ID = "alluserid"; // set


    const int DEFAULT_EXPIRE_TIME = 600; // seconds
};