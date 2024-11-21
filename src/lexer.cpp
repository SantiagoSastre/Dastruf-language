#include "lexer.hpp"
#include "dastruf.hpp"
#include <cstdlib>


Lexer::Lexer(const std::string &source) : source(source), start(0), current(0), line(1) {}



const std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"and", TokenType::AND},
    {"class", TokenType::CLASS},
    {"false", TokenType::FALSE},
    {"for", TokenType::FOR},
    {"if", TokenType::IF},
    {"elif", TokenType::ELIF},
    {"else", TokenType::ELSE},
    {"null", TokenType::NULL_TOKEN},
    {"or", TokenType::OR},
    {"p", TokenType::P},
    {"return", TokenType::RETURN},
    {"super", TokenType::SUPER},
    {"this", TokenType::THIS},
    {"true", TokenType::TRUE},
    {"string", TokenType::STRING},
    {"int", TokenType::INT},
    {"bool", TokenType::BOOL},
    {"float", TokenType::FLOAT},
    {"while", TokenType::WHILE},
    {"end", TokenType::END}
};


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
    case '*':
        add_token(TokenType::STAR);
        break;
     case '!':
        if (match('='))
            add_token(TokenType::NOT_EQUAL);
        else
            add_token(TokenType::NOT);
        break;
    case '=':
        if (match('='))
            add_token(TokenType::EQUAL_EQUAL);
        else
            add_token(TokenType::EQUAL);
        break;
    case '<':
        if (match('='))
            add_token(TokenType::LESS_EQUAL);
        else
            add_token(TokenType::LESS);
        break;
    case '>':
        if (match('='))
            add_token(TokenType::GREATER_EQUAL);
        else
            add_token(TokenType::GREATER);
        break;
    case '/':
    if (match('/')) {
        while (peek() != '\n' && !is_at_end()) {
            advance();
        }
    } else {
        add_token(TokenType::SLASH);
    }
    break;
    case ' ':
    case '\r':
    case '\t':
    break;
    case '\n':
        line++;
        break;
    case '"':
        string();
        break;
    default:
        if (is_digit(c)) {
            number();
        } else if (is_alpha(c)) {
            identifier();
        }
        else {
            Dastruf::error(line, "Unexpected character");
        }
        break;

}
}

bool Lexer::is_at_end() const {
        return current >= source.length();
    }

bool Lexer::is_digit(char c) const {
    return c >= '0' && c <= '9'; 
}

bool Lexer::is_alpha(char c) const {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool Lexer::is_alphanumeric(char c)  const {
    return is_alpha(c) || is_digit(c);
}

char Lexer::peek() const {
    if (is_at_end())
            return '\0';
        return source[current];
}
char Lexer::peek_next() const {
    if (current + 1 >= source.length()) {
        return '\0';
    }
    return source[current + 1]; 
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

void Lexer::add_token(TokenType type, const std::variant<std::monostate, std::string, int, float, bool>& literal) {
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, literal, line);
}

void Lexer::string() {
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') {
            Dastruf::error(line, "Error: Unterminated string literal");
            return;
        }
        advance();
    }
    if (is_at_end()) {
        Dastruf::error(line, "Error: Unterminated string literal.");
        return;
    }
    advance();
    std::string value = source.substr(start + 1, current - start - 2);


    add_token(TokenType::STRING, value);
}

void Lexer::number() {
    while (is_digit(peek()))
    {
        advance();
    }
    if (peek() == '.'){
        if(is_digit(peek_next())) {
            advance();
            while (is_digit(peek())){
                 advance();
                }
            add_token(TokenType::FLOAT, std::stof(source.substr(start, current - start)));
        }
    } else {
        add_token(TokenType::INT_LITERAL, std::stoi(source.substr(start, current - start)));

    }
    
}

void Lexer::identifier() {
    while (is_alphanumeric(peek()))
    {
        advance();
    }
    std::string text = source.substr(start, current - start);
    TokenType type;
    std::unordered_map<std::string, TokenType>::const_iterator it = keywords.find(text);
    if (it == keywords.end()) {
        type = TokenType::IDENTIFIER;
    } else {
        type = it->second;
    }
    add_token(type);

}
