#include "request/broadcastreq.h"


bool BroadcastReq::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try{
        if (root["type"].isNull()) { return false; }
        if (root["msg"].isNull()) { return false; }

        type = root["type"].asString();
        msg = root["msg"].asString();
    }catch(...){
        return false;
    }
    
    return true;
}


std::string BroadcastReq::dump() {
    Json::Value root;

    root["type"] = type;
    root["msg"] = msg;

    return root.toStyledString();
}
