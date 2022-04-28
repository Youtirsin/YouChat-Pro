#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>
#include <mutex>

#include <arpa/inet.h>
#include <cstring>

// Client Connection
class ClientConn {
public:
    ClientConn(int fd, const sockaddr_in& cliaddr);
    
    bool read(std::string& request);

    bool write(std::string& response);

    int getFd() const { return fd; }

    sockaddr_in getCliaddr() const { return cliaddr; }

    const char *getIP() const { return ip; }

    int getPort() const { return port; }

private:
    static const int BUFFER_SIZE = 1024;

    std::mutex mtx;

    int fd;

    std::string user_id;

    sockaddr_in cliaddr;
    char ip[24];
    int port;

    char readBuffer[BUFFER_SIZE];
    char writeBuffer[BUFFER_SIZE];
};