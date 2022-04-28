#pragma once

#include <iostream>
#include <utility>
#include <jsoncpp/json/json.h>
#include "responsebase.h"

// fetch unread requst
// { 
//     "type": "fetchunread", 
//     "unread": [
//         {
//             "id" : 1,
//             "num" : 12
//         }
//     ]
// }
struct FetchUnreadRes: public ResponseBase {

    std::vector<std::pair<int, int>> unread;

    FetchUnreadRes():
        ResponseBase("fetchunread") {}

    void addUnread(int id, int num) { unread.push_back(std::make_pair(id, num)); }

    std::string dump();

    bool load(const std::string& s);
};
