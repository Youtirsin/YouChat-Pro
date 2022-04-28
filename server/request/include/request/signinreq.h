#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "requestbase.h"

// sign in request
// {
//     "type" : "signin",
//     "username" : "Han",
//     "password" : "password"
// }
struct SignInReq: public RequestBase {

    std::string username;
    std::string password;

    SignInReq() {}

    SignInReq(const std::string& username_, const std::string& password_):
        username(username_), password(password_),
        RequestBase("signin") {}

    std::string dump();

    bool load(const std::string& s);
};
