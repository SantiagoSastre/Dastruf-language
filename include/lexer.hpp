#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <variant>
#include "token.hpp"



class Lexer {
    public:
        Lexer(const std::string &source);
        std::vector<Token> scan_tokens();
    private:
        std::string source;
        std::vector<Token> tokens;
        int start;
        int current;
        int line;
        bool is_at_end() const;
        bool is_digit(char c) const;
        bool is_alpha(char c) const;
        bool is_alphanumeric(char c) const;
        void scan_token();
        char advance();
        void add_token(TokenType type);
        void add_token(TokenType type, const std::variant<std::monostate, std::string, int, float, bool>& literal);
        bool match(char expected);
        void string();
        void number();
        void identifier();
        char peek() const;
        char peek_next() const;
};

#endif