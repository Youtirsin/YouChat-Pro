#pragma once

#include <iostream>
#include <vector>
#include <jsoncpp/json/json.h>

#include "responsebase.h"
#include "privateres.h"

// private response
// { 
//     "type": "privateload", 
//     "to_id": 12,
//     "msgs": [
//         "from_id" : 1,
//         "to_id" : 2,
//         "msg" : "test",
//         "stamp" : "timestamp"
//     ]
// }
struct PrivateLoadRes: public ResponseBase {

    int to_id;

    std::vector<PrivateRes> msgs;

    PrivateLoadRes():
        ResponseBase("privateload") {}

    PrivateLoadRes(int to_):
        to_id(to_),
        ResponseBase("privateload") {}

    void addMsg(const PrivateRes& msg) { msgs.push_back(msg); }

    std::string dump();

    bool load(const std::string& s);
};
