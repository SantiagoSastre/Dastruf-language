#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <variant>
#include "token_type.hpp"


class Token {
    private:
        const TokenType type;
        const std::string lexeme;
        const std::variant<std::monostate, std::string, int, float, bool> literal;
        const int line;
        std::string token_type_to_string(TokenType type) const;
        std::string literal_to_string(const std::variant<std::monostate, std::string, int, float, bool>& l);
    public:
        Token(TokenType type, std::string lexeme, std::variant<std::monostate, std::string, int, float, bool> literal, int line);
        std::string to_string();
};


#endif