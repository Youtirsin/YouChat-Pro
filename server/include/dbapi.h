#pragma once

#include <sstream>
#include <memory>
#include <iostream>

#include "mydb.h"
#include "response/response.h"
#include "entity.h"

using std::shared_ptr;

using std::stringstream;
using std::string;
using std::cout;
using std::endl;


class DBApi {
public:
    // DBApi(const SqlConnPool::Config& config_, const string& redis_conn);
    DBApi(const SqlConnPool::Config& config_);
    
    bool saveUser(const string& username, const string& password);

    shared_ptr<User> getUserWithId(int id);

    shared_ptr<User> getUserWithName(const string& username);

    // string getPsd(const string& username);

    // int getUserId(const string& username);

    // string getUsername(int id);

    bool savePrivateMsg(int from_id, int to_id, const string& msg);

    bool saveBroadcastMsg(int from_id, const string& msg);

    string loadPrivateMsg(int user_id, int friend_id, int page, int size);

    string loadBroadcastMsg( int page, int size);

private:
    SqlConnPool::Config config;

    // std::unique_ptr<sw::redis::Redis> redis_cli;
};