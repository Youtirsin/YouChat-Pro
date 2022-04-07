#pragma once

#include <iostream>
#include <cassert>
#include <cstring>
#include <mutex>

#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#include "request/request.h"

class Client {
public:
    Client(char *ip_= "127.0.0.1", int port_=10086):
        ip(ip_), port(port_) {}

    void start();


private:
    static const int BUFF_SIZE = 1024;

    char *ip;

    int port;

    int sock;

    bool socket_init();

    void prompt();

    void listen();

    void registerName();

    void fetchUserList();

    void privateMsg();

    void broadcast();

    void showMessages();

    void write_(const std::string& response);

    char read_buffer[BUFF_SIZE];

    std::mutex mtx;

    std::vector<std::string> messages;
};