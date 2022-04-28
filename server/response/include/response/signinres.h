#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "responsebase.h"

// sign in response
// {
//    "type": "signin",
//    "result": 0 | 1 
// }
struct SignInRes: public ResponseBase {
    int result;

    SignInRes(int result_):
        result(result_),
        ResponseBase("signin") {}

    std::string dump();

    bool load(const std::string& s);
};
