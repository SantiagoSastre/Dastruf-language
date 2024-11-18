#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include "token_type.hpp"


class Token {
    private:
        const TokenType type;
        const std::string lexeme;
        const std::string literal;
        const int line;
        std::string token_type_to_string(TokenType type) const;
    public:
        Token(TokenType type, std::string lexeme, std::string literal, int line);
        std::string to_string() const;
};


#endif