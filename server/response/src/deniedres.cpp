#include "response/deniedres.h"


std::string DeniedRes::dump() {
    Json::Value root;

    root["type"] = type;
    root["msg"] = "permission denied";

    return root.toStyledString();
}