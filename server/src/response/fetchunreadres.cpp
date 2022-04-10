#include "response/fetchunreadres.h"


bool FetchUnreadRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try {
        if (root["type"].isNull()) { return false; }
        if (root["unread"].isNull()) { return false; }
        if (!root["unread"].isArray()) { return false; }

        type = root["type"].asString();

        for (int i = 0; i < root["unread"].size(); i++) {
            Json::Value t = root["unread"][i];
            unread.push_back(std::make_pair(t["id"].asInt(), t["num"].asInt()));
        }
        
    } catch(...) {
        return false;
    }
    
    return true;
}

std::string FetchUnreadRes::dump() {
    Json::Value root;

    root["type"] = type;

    for (auto &&user : unread) {
        Json::Value t;
        t["id"] = user.first;
        t["num"] = user.second;
        root["unread"].append(t);
    }

    return root.toStyledString();
}
