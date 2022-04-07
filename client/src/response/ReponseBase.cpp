#include "ResponseBase.h"

bool ResponseBase::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    if (root["type"].isNull()) { return false; }

    type = root["type"].asString();

    return true;
}

std::string ResponseBase::dump() {
    Json::Value root;

    root["type"] = type;

    return root.toStyledString();
}
