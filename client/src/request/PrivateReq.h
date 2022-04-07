#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "RequestBase.h"

// private request
// { "type": "private", "to": "to_sb", "msg": "hello" }
struct PrivateReq: public RequestBase {

    std::string to;

    std::string msg;

    PrivateReq() {}

    PrivateReq(const std::string& to_, const std::string& msg_):
        to(to_), 
        msg(msg_), 
        RequestBase("private") {}

    std::string dump();

    bool load(const std::string& s);
};
