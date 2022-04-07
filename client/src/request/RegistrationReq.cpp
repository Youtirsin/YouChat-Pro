#include "RegistrationReq.h"

bool RegistrationReq::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    if (root["type"].isNull()) { return false; }
    if (root["type"].asString() != "register") { return false; }

    if (root["name"].isNull()) { return false; }

    type = root["type"].asString();
    name = root["name"].asString();

    return true;
}

std::string RegistrationReq::dump() {
    Json::Value root;

    root["type"] = type;
    root["name"] = name;

    return root.toStyledString();
}
