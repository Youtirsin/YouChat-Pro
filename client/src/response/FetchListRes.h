#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "ResponseBase.h"

// fetch list requst
// { "type": "fetchlist", "names": [] }
struct FetchListRes: public ResponseBase {

    std::vector<std::string> names;

    FetchListRes():
        ResponseBase("fetchlist") {}

    void addName(const std::string& name) { names.push_back(name); }

    std::string dump();

    bool load(const std::string& s);
};
