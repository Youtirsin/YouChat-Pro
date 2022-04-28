#include "response/signupres.h"


bool SignUpRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try {
        if (root["type"].isNull()) { return false; }
        if (root["result"].isNull()) { return false; }
        
        type = root["type"].asString();
        result = root["result"].asInt();

    } catch(...) {
        return false;
    }

    return true;
}


std::string SignUpRes::dump() {
    Json::Value root;

    root["type"] = type;
    root["result"] = result;

    return root.toStyledString();
}
