#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "requestbase.h"

// private request
// { 
//     "type": "broadcastload",
//     "page": 1,
//     "size": 10
// }
struct BroadcastLoadReq: public RequestBase {
    int page;
    int size;

    BroadcastLoadReq() {}

    BroadcastLoadReq(int page_, int size_):
        page(page_),
        size(size_),
        RequestBase("broadcastload") {}

    std::string dump();

    bool load(const std::string& s);
};
