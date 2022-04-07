#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "ResponseBase.h"

// regstration response
// { "type": "register", "name": "han", "result": 0 | 1 }
struct RegistrationRes: public ResponseBase {

    std::string name;

    int result;

    RegistrationRes(const std::string& name_, int result_):
        name(name_), 
        result(result_),
        ResponseBase("register") {}

    std::string dump();

    bool load(const std::string& s);
};
