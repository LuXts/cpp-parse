//
// Created by luxts on 22-5-13.
//

#include "TokenParse.hpp"
#include <stdexcept>

// 字符串转 double
std::variant< double, std::string > parse_number(const std::string &input) {
    try {
        size_t pos;
        double out = std::stod(input, &pos);
        // pos 代表函数处理了多少个字符，比如 "2a" 处理的结果是 out = 2 ， pos = 1
        if (pos != input.length()) {
            // 接上面的情况，如果函数没有解析完输入的字符串，证明解析失败，返回错误。
            return std::string("遇到未预期的输入: '" + input + "' ！");
        }
        return out;
    }
    catch (std::invalid_argument &_) {
        return std::string("遇到未预期的输入: '" + input + "' ！");
    }
}

std::variant< std::vector< Token >, std::string > TokenParse::Parse(const std::string &input) {
    auto   tokens   = std::vector< Token >();
    size_t slow_ptr = 0;  // 慢指针
    for (size_t current_ptr = 0 /*当前指针*/; current_ptr <= input.length(); current_ptr++) {
        Symbol symbol = Symbol::Uninitialized;
        char   item;
        if (current_ptr != input.length()) {
            item = input[current_ptr];
            switch (item) {
            case '(': {
                symbol = Symbol::LeftBracket;
                break;
            }
            case ')': {
                symbol = Symbol::RightBracket;
                break;
            }
            case '+': {
                symbol = Symbol::Add;
                break;
            }
            case '-': {
                symbol = Symbol::Sub;
                break;
            }
            case '*': {
                symbol = Symbol::Mul;
                break;
            }
            case '/': {
                symbol = Symbol::Div;
                break;
            }
            case ' ': {
                symbol = Symbol::Blank;
                break;
            }
            }
        }
        else {
            symbol = Symbol::End;
        }

        if (symbol != Symbol::Uninitialized) {
            if (slow_ptr != current_ptr) {
                // 截取 慢指针 到 当前指针 这一段字符串解析为数字。
                std::string temp = std::string(input.begin() + static_cast< long >(slow_ptr),
                                               input.begin() + static_cast< long >(current_ptr));
                auto        re   = parse_number(temp);
                double     *num  = std::get_if< Num >(&re);
                if (num == nullptr) {
                    return std::string("在位置 ") + std::to_string(slow_ptr) + " 处遇到" + std::get< std::string >(re);
                }
                else {
                    tokens.emplace_back(slow_ptr, *num, temp);
                }
            }
            if (symbol != Symbol::Blank) {
                tokens.emplace_back(current_ptr, symbol, std::string(1, item));
            }
            slow_ptr = current_ptr + 1;
        }
    }

    return tokens;
}
