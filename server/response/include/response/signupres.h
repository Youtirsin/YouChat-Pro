#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "responsebase.h"

// sign up response
// {
//    "type": "signup",
//    "result": 0 | 1 
// }
struct SignUpRes: public ResponseBase {
    int result;

    SignUpRes(int result_):
        result(result_),
        ResponseBase("signup") {}

    std::string dump();

    bool load(const std::string& s);
};

