#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "responsebase.h"

// private response
// {
//    "from_id" : 1,
//    "msg" : "test",
//    "stamp" : "t",
//    "to_id" : 2,
//    "type" : "private"
// }
class PrivateRes: public ResponseBase {
public:

    int from_id;

    int to_id;

    std::string msg;

    std::string stamp;

    PrivateRes(): ResponseBase("private") {}

    PrivateRes(int from_id_, int to_id_, const std::string& msg_, const std::string& date_):
        from_id(from_id_), 
        to_id(to_id), 
        msg(msg_),
        stamp(date_),
        ResponseBase("private") {}

    std::string dump();
    
    Json::Value dumpJson();

    bool load(const std::string& s);
};
