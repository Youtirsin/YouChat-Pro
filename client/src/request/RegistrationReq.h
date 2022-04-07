#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "RequestBase.h"

// registration request
// { "type": "register", "name": "sample_name" }
struct RegistrationReq: public RequestBase {

    std::string name;

    RegistrationReq() {}

    RegistrationReq(const std::string& name_):
        name(name_), 
        RequestBase("register") {}

    std::string dump();

    bool load(const std::string& s);
};
