#include "token/TokenParse.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    string input = "3+9+1";
    cout << "输入字符串为: " << input << endl;
    auto    re  = TokenParse::parse(input);
    string *str = get_if< string >(&re);
    if (str == nullptr) {
        auto vec = get< vector< Token > >(re);
        for (auto &token : vec) {
            cout << token << endl;
        }
    }
    else {
        cout << *str << endl;
    }
    return 0;
}
