#pragma once

#include <iostream>
#include <vector>
#include <jsoncpp/json/json.h>

#include "responsebase.h"
#include "broadcastres.h"

// private request
// { 
//     "type": "broadcastload",
//     "msgs": [
//         "from_id" : 1,
//         "msg" : "test",
//         "stamp" : "timestamp"
//     ]
// }
struct BroadcastLoadRes: public ResponseBase {

    std::vector<BroadcastRes> msgs;

    BroadcastLoadRes():
        ResponseBase("broadcastload") {}

    void addMsg(const BroadcastRes& msg) { msgs.push_back(msg); }

    std::string dump();

    bool load(const std::string& s);
};
