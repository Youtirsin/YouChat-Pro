#include "PrivateRes.h"

bool PrivateRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    if (root["type"].isNull()) { return false; }
    if (root["type"].asString() != "private") { return false; }

    if (root["msg"].isNull()) { return false; }
    if (root["from"].isNull()) { return false; }

    type = root["type"].asString();
    from = root["from"].asString();
    msg = root["msg"].asString();

    return true;
}

std::string PrivateRes::dump() {
    Json::Value root;

    root["type"] = type;
    root["from"] = from;
    root["msg"] = msg;

    return root.toStyledString();
}
