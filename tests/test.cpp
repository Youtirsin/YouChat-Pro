#include <bits/stdc++.h>
#include <fstream>
#include "jsoncpp/json/json.h"
using namespace std;


class A {
public:
    void setd(int dd) { d = dd; }

    const int& getd() const { 
        cout << &d << endl;
        return d;
    }
private:
    int d;
};

void test(const int& d) {
    cout << d << endl;
    cout << &d << endl;
}


int main() {
    A a;

    a.setd(12);

    test(a.getd());

    return 0;
}

