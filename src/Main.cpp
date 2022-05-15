#include "token/TokenParse.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv) {
    string input = "1.23e1 + 3";
    cout << "输入字符串为: " << input << endl;
    auto re = TokenParse::Parse(input);

    if (re.index() == 0) {
        auto vec = std::get< std::vector< Token > >(re);
        for (auto &token : vec) {
            cout << token << endl;
        }
    }
    else {
        cout << std::get< string >(re) << endl;
    }
    return 0;
}
