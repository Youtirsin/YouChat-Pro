#include "response/fetchlistres.h"


bool FetchListRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try {
        if (root["type"].isNull()) { return false; }
        if (root["users"].isNull()) { return false; }
        if (!root["users"].isArray()) { return false; }

        type = root["type"].asString();

        for (int i = 0; i < root["names"].size(); i++) {
            Json::Value t = root["names"][i];
            users.push_back(std::make_pair(t["username"].asString(), t["id"].asInt()));
        }
        
    } catch(...) {
        return false;
    }
    
    return true;
}

std::string FetchListRes::dump() {
    Json::Value root;

    root["type"] = type;

    for (auto &&user : users) {
        Json::Value t;
        t["username"] = user.first;
        t["id"] = user.second;
        root["users"].append(t);
    }

    return root.toStyledString();
}
