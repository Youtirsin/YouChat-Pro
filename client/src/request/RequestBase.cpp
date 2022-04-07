#include "RequestBase.h"

bool RequestBase::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    if (root["type"].isNull()) { return false; }

    type = root["type"].asString();

    return true;
}

std::string RequestBase::dump() {
    Json::Value root;

    root["type"] = type;

    return root.toStyledString();
}
