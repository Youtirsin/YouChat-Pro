#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "ResponseBase.h"

// private response
// { "type": "private", "from": "han", "msg": "hello" }
struct PrivateRes: public ResponseBase {

    std::string from;

    std::string msg;

    PrivateRes(const std::string& from_, const std::string& msg_):
        from(from_), 
        msg(msg_), 
        ResponseBase("private") {}

    std::string dump();

    bool load(const std::string& s);
};
