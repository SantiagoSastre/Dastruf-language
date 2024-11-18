#include "lexer.hpp"
#include "dastruf.hpp"

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

void Lexer::scan_token() {
    char c = advance();
    switch (c)
    {
    case '(':
        add_token(TokenType::LEFT_PAREN);
        break;
    case ')':
        add_token(TokenType::RIGHT_PAREN);
        break;
        add_token(TokenType::COMMA);
        break;
    case '.':
        add_token(TokenType::DOT);
        break;
    case '-':
        add_token(TokenType::MINUS);
        break;
    case '+':
        add_token(TokenType::PLUS);
        break;
    default:
        Dastruf::error(line, "Unexpected character");
        break;

}
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
