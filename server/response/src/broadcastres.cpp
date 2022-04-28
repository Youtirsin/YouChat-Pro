#include "response/broadcastres.h"


bool BroadcastRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try{
        if (root["type"].isNull()) { return false; }
        if (root["from_id"].isNull()) { return false; }
        if (root["msg"].isNull()) { return false; }
        if (root["stamp"].isNull()) { return false; }

        type = root["type"].asString();
        from_id = root["from_id"].asInt();
        msg = root["msg"].asString();
        stamp = root["stamp"].asString();
    } catch(...) {
        return false;
    }
    
    return true;
}

std::string BroadcastRes::dump() {
    Json::Value root;

    root["type"] = type;
    root["from_id"] = from_id;
    root["msg"] = msg;
    root["stamp"] = stamp;

    return root.toStyledString();
}


Json::Value BroadcastRes::dumpJson() {
    Json::Value root;

    root["type"] = type;
    root["from_id"] = from_id;
    root["msg"] = msg;
    root["stamp"] = stamp;

    return root;
}