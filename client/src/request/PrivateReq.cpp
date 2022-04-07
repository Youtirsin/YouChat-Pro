#include "PrivateReq.h"

bool PrivateReq::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    if (root["type"].isNull()) { return false; }
    if (root["type"].asString() != "private") { return false; }

    if (root["to"].isNull()) { return false; }
    if (root["msg"].isNull()) { return false; }

    type = root["type"].asString();
    to = root["to"].asString();
    msg = root["msg"].asString();

    return true;
}

std::string PrivateReq::dump() {
    Json::Value root;

    root["type"] = type;
    root["to"] = to;
    root["msg"] = msg;

    return root.toStyledString();
}
