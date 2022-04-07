#include "RegistrationRes.h"

bool RegistrationRes::load(const std::string& s) {
    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(s, root)) { return false; }

    if (root["type"].isNull()) { return false; }
    if (root["type"].asString() != "register") { return false; }

    if (root["name"].isNull()) { return false; }

    if (root["result"].isNull()) { return false; }

    type = root["type"].asString();
    name = root["name"].asString();
    result = root["result"].asInt();

    return true;
}

std::string RegistrationRes::dump() {
    Json::Value root;

    root["type"] = type;
    root["name"] = name;
    root["result"] = result;

    return root.toStyledString();
}
