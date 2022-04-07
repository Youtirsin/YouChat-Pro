#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

// base class of response including an attr of type
// { "type" : "type_sample"}
struct ResponseBase {

    std::string type;

    ResponseBase(std::string type_): 
        type(type_) {}

    virtual std::string dump();

    virtual bool load(const std::string& s);
};
