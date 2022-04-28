#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "requestbase.h"

// private request
// { 
//     "type": "privateload", 
//     "to_id": 12,
//     "page": 1,
//     "size": 10
// }
struct PrivateLoadReq: public RequestBase {

    int to_id;
    int page;
    int size;

    PrivateLoadReq() {}

    PrivateLoadReq(int to_, int page_, int size_):
        to_id(to_), 
        page(page_),
        size(size_),
        RequestBase("privateload") {}

    std::string dump();

    bool load(const std::string& s);
};
