#pragma once

#include <string>

using std::string;

struct User {
    int id;
    string username;
    string password;
};


struct PrivateMsg {
    int id;
    int fromid;
    int toid;
    string msg;
    string stamp;
};


struct BroadcastMsg {
    int id;
    int fromid;
    string msg;
    string stamp;
};


struct Unread {
    int id;
    int num;
};
