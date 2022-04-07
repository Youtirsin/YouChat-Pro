#pragma once

#include <iostream>
#include <fstream>

#include "jsoncpp/json/json.h"
#include "mydb.h"


class ConfigFileLoader {
public:
    bool load(const string& filepath);

    const string& getRedisConn() const { return redisconn; }

    const SqlConnPool::Config& getSQLConfig() const { return sqlconfig; }

private:
    string redisconn;

    SqlConnPool::Config sqlconfig;
};