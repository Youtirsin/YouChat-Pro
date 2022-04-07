#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

// Base class of requests
// { "type" : "type_sample" }
struct RequestBase {

    std::string type;

    RequestBase() {}

    RequestBase(std::string type_): 
        type(type_) {}

    virtual std::string dump();

    virtual bool load(const std::string& s);
};


