#include "response/broadcastloadres.h"


bool BroadcastLoadRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try {
        if (root["type"].isNull()) { return false; }
        if (root["msgs"].isNull()) { return false; }
        if (!root["msgs"].isArray()) { return false; }

        type = root["type"].asString();

        for (int i = 0; i < root["msgs"].size(); i++) {
            Json::Value t = root["msgs"][i];

            if (!t) continue;

            BroadcastRes res(t["from_id"].asInt(),
                t["msg"].asString(),
                t["stamp"].asString());

            msgs.push_back(res);
        }
        
    } catch(...) {
        return false;
    }
    
    return true;
}

std::string BroadcastLoadRes::dump() {
    Json::Value root;

    root["type"] = type;

    for (auto &&msg : msgs) {
        Json::Value t;
        t["from_id"] = msg.from_id;
        t["msg"] = msg.msg;
        t["stamp"] = msg.stamp;
        
        root["msgs"].append(t);
    }

    return root.toStyledString();
}
