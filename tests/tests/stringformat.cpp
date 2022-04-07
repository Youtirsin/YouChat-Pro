#include <sstream>
#include <iostream>
using namespace std;

int main() {
    string username("test");
    string password("pass");
    stringstream fmt;
    string res;
    
    fmt << "insert into user(username, password) values('" << username << "', '" << password << "')";
    
    cout << fmt.str() << endl;

    fmt.str("");
    fmt << "select id from user where username = '" << username << "'";
    
    cout << fmt.str() << endl;
    return 0;
}

