#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "RequestBase.h"

// fetch list requst
// { "type": "fetchlist" }
struct FetchListReq: public RequestBase {

    FetchListReq():
        RequestBase("fetchlist") {}

    std::string dump();

    bool load(const std::string& s);
};
