#include "response/privateloadres.h"


bool PrivateLoadRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    try {
        if (root["type"].isNull()) { return false; }
        if (root["to_id"].isNull()) { return false; }
        if (root["msgs"].isNull()) { return false; }
        if (!root["msgs"].isArray()) { return false; }

        type = root["type"].asString();
        to_id = root["to_id"].asInt();

        for (int i = 0; i < root["msgs"].size(); i++) {
            Json::Value t = root["msgs"][i];

            if (!t) continue;

            PrivateRes res(t["from_id"].asInt()
                , t["to_id"].asInt(), t["msg"].asString(), t["stamp"].asString());

            msgs.push_back(res);
        }
        
    } catch(...) {
        return false;
    }
    
    return true;
}

std::string PrivateLoadRes::dump() {
    Json::Value root;

    root["type"] = type;
    root["to_id"] = to_id;

    for (auto &&msg : msgs) {
        Json::Value t;
        t["from_id"] = msg.from_id;
        t["to_id"] = msg.to_id;
        t["msg"] = msg.msg;
        t["stamp"] = msg.stamp;
        
        root["msgs"].append(t);
    }

    return root.toStyledString();
}
