#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "sw/redis++/redis++.h"

#include "entity.h"

using std::shared_ptr;

using std::string;
using std::cout;
using std::endl;

class RedisApi {
public:
    RedisApi(const string& connection);

    // bool saveUser(const string& username, const string& password);
    bool saveUser(const User& user);

    shared_ptr<User> getUserWithId(int id);

    shared_ptr<User> getUserWithName(const string& username);

    // string getUsernameWithId(int id);

    // bool setUsernameWithId(int id, const string& name);
private:
    sw::redis::Redis redis;

    const string PROJECT_NAME = "youchatpro:";

    const string USERID_TO_NAME = "usernameid:";

    const int DEFAULT_EXPIRE_TIME = 600; // seconds
};