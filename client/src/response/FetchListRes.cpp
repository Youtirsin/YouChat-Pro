#include "FetchListRes.h"

bool FetchListRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    if (root["type"].isNull()) { return false; }
    if (root["type"].asString() != "broadcast") { return false; }

    if (root["names"].isNull()) { return false; }
    if (!root["names"].isArray()) { return false; }

    type = root["type"].asString();
    for (int i = 0; i < root["names"].size(); i++) {
        names.push_back(root["names"][i].asString());
    }
    
    return true;
}

std::string FetchListRes::dump() {
    Json::Value root;

    root["type"] = type;
    for (auto &&name : names) {
        root["names"].append(name);
    }

    return root.toStyledString();
}
