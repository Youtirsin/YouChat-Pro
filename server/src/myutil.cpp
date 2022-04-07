#include "myutil.h"

std::string timestampnow() {
    time_t t = time(0);
    return ctime(&t);
}
