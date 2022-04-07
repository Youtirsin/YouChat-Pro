#include <iostream>

#include "server.h"
#include "configfileloader.h"


int main() {

    ConfigFileLoader loader;
    if (!loader.load("config.json")) {
        return -1;
    }

    Server server(loader.getSQLConfig(), loader.getRedisConn());

    server.start();

    return 0;
}
