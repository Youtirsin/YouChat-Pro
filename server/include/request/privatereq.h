#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "requestbase.h"

// private request
// { 
//     "type": "private", 
//     "to_id": 12, 
//     "msg": "hello"
// }
struct PrivateReq: public RequestBase {

    int to_id;

    std::string msg;

    PrivateReq() {}

    PrivateReq(int to_, const std::string& msg_):
        to_id(to_), 
        msg(msg_), 
        RequestBase("private") {}

    std::string dump();

    bool load(const std::string& s);
};
