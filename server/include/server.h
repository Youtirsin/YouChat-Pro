#pragma once


#include <iostream>
#include <unordered_map>
#include <memory>

#include <cassert>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>


#include "epoll.h"
#include "threadpool.h"
#include "clientconn.h"
#include "request/request.h"
#include "response/response.h"
#include "dbapi.h"
#include "redisapi.h"
#include "myutil.h"

using std::string;

class Server {
public:
    Server(const SqlConnPool::Config& sqlconfig, const string& redisconn);

    void start();

private:
    static const int FD_NUM = 1024;

    static const int LISTEN_NUM = 20;

    static const int PORT = 10086;

    // // ------------ redis -------
    // const string REDIS_CONN = "tcp://127.0.0.1:6379";

    // // MySQL Configuration
    // const SqlConnPool::Config SQLConfig = {
    //     "127.0.0.1",
    //     "root",
    //     "123456",
    //     "youchatpro",
    //     10
    // };

    static int setFdNonBlock(int fd);
    
    bool socket_init();

    void doConnect();

    void closeConn(int fd);

    void processRead(int fd);

    void read(int fd);

    void write(ClientConn *client, string response);
    
    void handleRequest(const string& request, ClientConn *client);

    // *********** request handles *****************

    void denied(const string& request, ClientConn *client);

    void signUp(const string& request, ClientConn *client);
    void signIn(const string& request, ClientConn *client);
    void broadcast(const string& request, ClientConn *client);
    void fetchlist(const string& request, ClientConn *client);
    void privateMsg(const string& request, ClientConn *client);

    void loadPrivate(const string& request, ClientConn *client);
    void loadBroadcast(const string& request, ClientConn *client);

    bool closed;

    int listenfd;

    sockaddr_in serv_addr;
    
    // fd -> Conn
    std::unordered_map<int, ClientConn*> conns;
    // fd -> user_id
    std::unordered_map<int, int> fd_to_userId;
    // user_id -> fd
    std::unordered_map<int, int> userId_to_fd;

    std::unique_ptr<Epoll> epoll;
    std::unique_ptr<ThreadPool> threadpool;

    DBApi dbapi;

    RedisApi redisapi;
    // std::unique_ptr<SqlConnPool> sqlConnPool;
    // std::unique_ptr<sw::redis::Redis> redis;
};