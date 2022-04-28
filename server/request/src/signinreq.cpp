#include "request/signInreq.h"


bool SignInReq::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try{
        if (root["type"].isNull()) { return false; }
        if (root["username"].isNull()) { return false; }
        if (root["password"].isNull()) { return false; }

        type = root["type"].asString();
        username = root["username"].asString();
        password = root["password"].asString();

    }catch(...){
        return false;
    }
    
    return true;
}


std::string SignInReq::dump() {
    Json::Value root;

    root["type"] = type;
    root["username"] = username;
    root["password"] = password;

    return root.toStyledString();
}
