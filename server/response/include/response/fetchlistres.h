#pragma once

#include <iostream>
#include <utility>
#include <jsoncpp/json/json.h>
#include "responsebase.h"

// fetch list requst
// { 
//     "type": "fetchlist", 
//     "users": [
//         "username": "han",
//         "id": 1
//     ]
// }
struct FetchListRes: public ResponseBase {

    std::vector<std::pair<std::string, int>> users;

    FetchListRes():
        ResponseBase("fetchlist") {}

    void addName(const std::string& name, int id) { users.push_back(std::make_pair(name, id)); }

    std::string dump();

    bool load(const std::string& s);
};
