#include "request/broadcastloadreq.h"


bool BroadcastLoadReq::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try{
        if (root["type"].isNull()) { return false; }
        if (root["page"].isNull()) { return false; }
        if (root["size"].isNull()) { return false; }

        type = root["type"].asString();
        page = root["page"].asInt();
        size = root["size"].asInt();

    }catch(...){
        return false;
    }
    
    return true;
}


std::string BroadcastLoadReq::dump() {
    Json::Value root;

    root["type"] = type;
    root["page"] = page;
    root["size"] = size;

    return root.toStyledString();
}