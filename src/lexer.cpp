#include "lexer.hpp"

Lexer::Lexer(const std::string &source) : source(source), start(0), current(0), line(1) {}

std::vector<Token> Lexer::scan_tokens()
{
    while (!is_at_end())
    {
        start = current;
        scan_token();
    }

    tokens.emplace_back(TokenType::EOF_TOKEN, "", "", line);
    return tokens;
}



bool Lexer::is_at_end() const {
        return current >= source.length();
    }

char Lexer::peek(){
    if (is_at_end())
            return '\0';
        return source[current];
}

bool Lexer::match(char expected) {
        if (is_at_end())
            return false;
        if (source[current] != expected)
            return false;
        current++;
        return true;
}

char Lexer::advance() {
        return source[current++];
}

void Lexer::add_token(TokenType type) {
        add_token(type, "");
}

void Lexer::add_token(TokenType type, const std::string &literal) {
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, literal, line);
}
