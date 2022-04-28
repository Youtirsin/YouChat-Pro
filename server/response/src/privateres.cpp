#include "response/privateres.h"


bool PrivateRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try {
        if (root["type"].isNull()) { return false; }
        if (root["from_id"].isNull()) { return false; }
        if (root["to_id"].isNull()) { return false; }
        if (root["msg"].isNull()) { return false; }
        if (root["stamp"].isNull()) { return false; }

        type = root["type"].asString();
        from_id = root["from_id"].asInt();
        to_id = root["to_id"].asInt();
        msg = root["msg"].asString();
        stamp = root["stamp"].asString();
    } catch(...) {
        return false;
    }
    
    return true;
}


std::string PrivateRes::dump() {
    Json::Value root;

    root["type"] = type;
    root["from_id"] = from_id;
    root["to_id"] = to_id;
    root["msg"] = msg;
    root["stamp"] = stamp;

    return root.toStyledString();
}


Json::Value PrivateRes::dumpJson() {
    Json::Value root;

    root["type"] = type;
    root["from_id"] = from_id;
    root["to_id"] = to_id;
    root["msg"] = msg;
    root["stamp"] = stamp;

    return root;
}