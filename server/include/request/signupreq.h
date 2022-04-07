#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "requestbase.h"

// sign up request
// {
//     "type" : "signup",
//     "username" : "Han",
//     "password" : "password"
// }
struct SignUpReq: public RequestBase {

    std::string username;
    std::string password;

    SignUpReq() {}

    SignUpReq(const std::string& username_, const std::string& password_):
        username(username_), password(password_),
        RequestBase("signup") {}

    std::string dump();

    bool load(const std::string& s);
};
