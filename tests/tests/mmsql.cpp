#include <iostream>
#include <cassert>
#include <mysql/mysql.h>
// #include "myDB/MyDB.h"
using namespace std;



MYSQL *init() {
    MYSQL *mysql = new MYSQL;

    if (!(mysql = mysql_init(mysql))) {
        cout << "mysql_init(): " << mysql_error(mysql) << endl;
        assert(mysql);
    }

    if (!(mysql == mysql_real_connect(mysql,"127.0.0.1","root","123456","youchatpro",0,NULL,0))) {
        cout << "mysql_real_connect():" << mysql_error(mysql) << endl;
        assert(mysql);
    }

    cout << "connected to MySQL.\n";
    return mysql;
}



int main() {
    auto sql = init();

    string str = "select username, password from user";

    mysql_real_query(sql, str.c_str(), str.size());

    MYSQL_RES* res = mysql_store_result(sql);
    int rowlen = mysql_num_rows(res);
    int collen = mysql_num_fields(res);

    // for (int i = 0; i < len; i++) {
    //     MYSQL_ROW row = mysql_fetch_row(res);
    // }
    

    cout << rowlen << endl;
    cout << collen << endl;

    mysql_free_result(res);
    mysql_close(sql);

    return 0;
}

