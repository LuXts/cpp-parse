//
// Created by luxts on 22-5-13.
//

#ifndef CPP_PARSE_SRC_TOKEN_TOKENPARSE_HPP_
#define CPP_PARSE_SRC_TOKEN_TOKENPARSE_HPP_

#include "Token.hpp"
#include <string>
#include <vector>

class TokenParse {

public:
    // 解析字符串，输出 Tokens 的函数
    static std::variant< std::vector< Token >, std::string > Parse(const std::string &input);
};

#endif  // CPP_PARSE_SRC_TOKEN_TOKENPARSE_HPP_
