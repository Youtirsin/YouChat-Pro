#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "responsebase.h"

// broadcast response
// { 
//     "type": "broadcast", 
//     "user_id": 12, 
//     "msg": "hi"
// }
struct BroadcastRes: public ResponseBase {

    std::string msg;

    int from_id;

    std::string stamp;

    BroadcastRes(int from_id_, const std::string& msg_, const std::string& stamp_):
        msg(msg_),
        from_id(from_id_),
        stamp(stamp_),
        ResponseBase("broadcast") {}

    std::string dump();

    Json::Value dumpJson();

    bool load(const std::string& s);
};




