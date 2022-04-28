#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "requestbase.h"

// fetch list requst
// { 
//     "type": "fetchunread" 
// }
struct FetchUnread: public RequestBase {

    FetchUnread():
        RequestBase("fetchunread") {}

    std::string dump();

    bool load(const std::string& s);
};
