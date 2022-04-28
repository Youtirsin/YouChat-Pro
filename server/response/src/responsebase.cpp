#include "response/responsebase.h"

bool ResponseBase::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try {
        if (root["type"].isNull()) { return false; }

        type = root["type"].asString();

    } catch(...) {
        return false;
    }
    
    return true;
}


std::string ResponseBase::dump() {
    Json::Value root;

    root["type"] = type;

    return root.toStyledString();
}


Json::Value ResponseBase::dumpJson() {

    Json::Value root;

    root["type"] = type;

    return root;
}