//
// Created by luxts on 22-5-13.
//

#ifndef CPP_PARSE_SRC_TOKEN_TOKEN_HPP_
#define CPP_PARSE_SRC_TOKEN_TOKEN_HPP_

#include <iostream>
#include <string>
#include <variant>

using Num = double;

enum class Symbol {
    Uninitialized,
    LeftBracket,
    RightBracket,
    Add,
    Sub,
    Mul,
    Div,
    Blank,
    End,
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
    friend std::ostream &operator<<(std::ostream &output, const Token &token) {
        output << "token:{ position: " << token.position;
        if (std::get_if< Num >(&token.content) != nullptr) {
            output << ", content: Num(" << std::get< Num >(token.content)<<")";
        }
        else {
            switch (std::get< Symbol >(token.content)) {
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
    size_t                      position;
    std::variant< Num, Symbol > content;
    std::string                 origin;
};

#endif  // CPP_PARSE_SRC_TOKEN_TOKEN_HPP_
