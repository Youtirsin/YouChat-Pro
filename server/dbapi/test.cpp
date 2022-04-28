#include "dbapi.h"


int main(int argc, char const *argv[]) {

    const SqlConnPool::Config SQLConfig = {
        "127.0.0.1",
        "root",
        "123456",
        "youchatpro",
        10
    };

    DBApi api(SQLConfig);

    auto res = api.saveUser("han", "123456");

    cout << "create user result: " << res << endl;

    return 0;
}
