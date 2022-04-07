#pragma once

#include <iostream>
#include <jsoncpp/json/json.h>

#include "responsebase.h"

// response for permission denied
// {
//     "type": "denied",
//     "msg": "permission denied"
// }
struct DeniedRes: public ResponseBase {

    DeniedRes():
        ResponseBase("denied") {}

    std::string dump();
};
