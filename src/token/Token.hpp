//
// Created by luxts on 22-5-13.
//

#ifndef CPP_PARSE_SRC_TOKEN_TOKEN_HPP_
#define CPP_PARSE_SRC_TOKEN_TOKEN_HPP_

#include <iostream>
#include <string>
#include <variant>

// 定义我们的数字类型是 double
using Num = double;

// 符号种类
enum class Symbol {
    Uninitialized,  // 未定义
    LeftBracket,    // 左括号
    RightBracket,   // 右括号
    Add,            // + 号
    Sub,            // - 号
    Mul,            // * 号
    Div,            // / 号
    Blank,          // 空格
    End,            // 输入结束符号
};

class Token {
public:
    Token() {}

    Token(size_t position, const std::variant< Num, Symbol > &content, const std::string &origin)
        : position(position), content(content), origin(origin) {}

    size_t GetPosition() const {
        return position;
    }
    void SetPosition(size_t position) {
        Token::position = position;
    }
    const std::variant< Num, Symbol > &GetContent() const {
        return content;
    }
    void SetContent(const std::variant< Num, Symbol > &content) {
        Token::content = content;
    }
    const std::string &GetOrigin() const {
        return origin;
    }
    void SetOrigin(const std::string &origin) {
        Token::origin = origin;
    }

    // 输出用函数。
    friend std::ostream &operator<<(std::ostream &output, const Token &token) {
        output << "token:{ position: " << token.position;
        if (token.content.index() == 0) {
            output << ", content: Num(" << std::get< Num >(token.content) << ")";
        }
        else if (token.content.index() == 1) {
            switch (std::get< Symbol >(token.content)) {
            case Symbol::Uninitialized: {
                break;
            }
            case Symbol::LeftBracket: {
                output << ", content: '('";
                break;
            }
            case Symbol::RightBracket: {
                output << ", content: ')'";
                break;
            }
            case Symbol::Add: {
                output << ", content: '+'";
                break;
            }
            case Symbol::Sub: {
                output << ", content: '-'";
                break;
            }
            case Symbol::Mul: {
                output << ", content: '*'";
                break;
            }
            case Symbol::Div: {
                output << ", content: '/'";
                break;
            }
            case Symbol::Blank: {
                output << ", content: '_'";
                break;
            }
            case Symbol::End: {
                output << ", content: '#'";
                break;
            }
            }
        }

        output << ", origin: \"" << token.origin << "\"}";
        return output;
    }

private:
    size_t                      position;  // token 在输入串的位置
    std::variant< Num, Symbol > content;   // token 的内容
    std::string                 origin;    // token 的原输入
};

#endif  // CPP_PARSE_SRC_TOKEN_TOKEN_HPP_
