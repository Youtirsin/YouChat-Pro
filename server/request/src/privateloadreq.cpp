#include "request/privateloadreq.h"


bool PrivateLoadReq::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try{
        if (root["type"].isNull()) { return false; }
        if (root["to_id"].isNull()) { return false; }
        if (root["page"].isNull()) { return false; }
        if (root["size"].isNull()) { return false; }

        type = root["type"].asString();
        to_id = root["to_id"].asInt();
        page = root["page"].asInt();
        size = root["size"].asInt();

    }catch(...){
        return false;
    }
    
    return true;
}


std::string PrivateLoadReq::dump() {
    Json::Value root;

    root["type"] = type;
    root["to_id"] = to_id;
    root["page"] = page;
    root["size"] = size;

    return root.toStyledString();
}