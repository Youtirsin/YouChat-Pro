#include "request/privatereq.h"


bool PrivateReq::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try{
        if (root["type"].isNull()) { return false; }
        if (root["to_id"].isNull()) { return false; }
        if (root["msg"].isNull()) { return false; }

        type = root["type"].asString();
        to_id = root["to_id"].asInt();
        msg = root["msg"].asString();

    }catch(...){
        return false;
    }
    
    return true;
}


std::string PrivateReq::dump() {
    Json::Value root;

    root["type"] = type;
    root["to_id"] = to_id;
    root["msg"] = msg;

    return root.toStyledString();
}