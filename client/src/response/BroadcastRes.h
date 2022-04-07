#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "ResponseBase.h"

// broadcast response
// { "type": "broadcast", "name": "han", "msg": "han"}
struct BroadcastRes: public ResponseBase {

    std::string msg;

    std::string name;

    BroadcastRes(const std::string& msg_, const std::string& name_):
        msg(msg_),
        name(name_),
        ResponseBase("broadcast") {}

    std::string dump();

    bool load(const std::string& s);
};
