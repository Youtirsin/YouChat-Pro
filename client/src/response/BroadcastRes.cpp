#include "BroadcastRes.h"

bool BroadcastRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    if (root["type"].isNull()) { return false; }
    if (root["type"].asString() != "broadcast") { return false; }

    if (root["msg"].isNull()) { return false; }
    if (root["name"].isNull()) { return false; }

    type = root["type"].asString();
    name = root["name"].asString();
    msg = root["msg"].asString();

    return true;
}

std::string BroadcastRes::dump() {
    Json::Value root;

    root["type"] = type;
    root["name"] = name;
    root["msg"] = msg;

    return root.toStyledString();
}
