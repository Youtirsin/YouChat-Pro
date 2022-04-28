#include "configfileloader.h"


bool ConfigFileLoader::load(const string& filepath) {
    std::ifstream ireader(filepath);

    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(ireader, root)) {
        std::cout << "error occured reading config file.\n";
        ireader.close();
        return false;
    }
    ireader.close();

    try {
        if (root["redis"].isNull()) { return false; }
        if (root["mysql"].isNull()) { return false; }

        if (root["mysql"]["host"].isNull()) { return false; }
        if (root["mysql"]["user"].isNull()) { return false; }
        if (root["mysql"]["pwd"].isNull()) { return false; }
        if (root["mysql"]["dbname"].isNull()) { return false; }
        if (root["mysql"]["connsize"].isNull()) { return false; }

        redisconn = root["redis"].asString();

        sqlconfig.host = root["mysql"]["host"].asString();
        sqlconfig.user = root["mysql"]["user"].asString();
        sqlconfig.pwd = root["mysql"]["pwd"].asString();
        sqlconfig.dbname = root["mysql"]["dbname"].asString();
        sqlconfig.connsize = root["mysql"]["connsize"].asInt();

    } catch(...) {
        std::cout << "error occured reading config file.\n";
        return false;
    }
    
    return true;
}
