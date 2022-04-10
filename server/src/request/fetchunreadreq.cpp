#include "request/fetchunreadreq.h"


bool FetchUnread::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try{
        if (root["type"].isNull()) { return false; }

        type = root["type"].asString();
    }catch(...){
        return false;
    }
    
    return true;
}


std::string FetchUnread::dump() {
    Json::Value root;

    root["type"] = type;

    return root.toStyledString();
}
