#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "RequestBase.h"

// broadcast request
// { "type": "broadcast", "msg": "hello" }
struct BroadcastReq: public RequestBase {

    std::string msg;

    BroadcastReq() {}

    BroadcastReq(const std::string& msg_):
        msg(msg_),
        RequestBase("broadcast") {}

    std::string dump();

    bool load(const std::string& s);
};
