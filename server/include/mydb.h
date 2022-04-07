#pragma once

#include <mysql/mysql.h>
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <semaphore.h>
#include <thread>
#include <cassert>


using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::lock_guard;
using std::mutex;


class DBMysqlConn {
public:
    DBMysqlConn(const char* host,const char* user,const char* passwd,const char* db_name);

    ~DBMysqlConn();

    bool db_insert(const string& sqlstr);

    bool db_update(const string& sqlstr);

    vector<vector<string>> db_select(const string& sqlstr);
private:
    MYSQL mysql;
    
    void db_close();
};


class SqlConnPool {
public:
    struct Config {
        string host;
        string user;
        string pwd;
        string dbName;
        int connSize;
    };

    static SqlConnPool *Instance(const Config& config);

    DBMysqlConn* GetConn();

    void FreeConn(DBMysqlConn* conn);

    int GetFreeConnCount();

private:
    void init(const Config& config);

    SqlConnPool();

    // SqlConnPool(const SqlConnPool& r) = default;

    ~SqlConnPool();

    void ClosePool();

    int MAX_CONN_;
    int useCount_;
    int freeCount_;

    std::queue<DBMysqlConn*> connQue_;
    std::mutex mtx_;
    sem_t semId_;
};


class SqlConnWrapper {
public:
    SqlConnWrapper(SqlConnPool *pool_);

    ~SqlConnWrapper();

    DBMysqlConn *getConn() const { return conn; }

private:
    DBMysqlConn *conn;

    SqlConnPool *pool;
};