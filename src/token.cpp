#include "token.hpp"
#include <sstream>
#include <variant>



std::string Token::token_type_to_string(TokenType type) const {
    switch (type) {
// Single-character tokens
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::MINUS: return "MINUS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::SLASH: return "SLASH";
        case TokenType::STAR: return "STAR";

        // One or two character tokens
        case TokenType::NOT: return "NOT";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";

        // Literals
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::NUMBER: return "NUMBER";

        // Keywords
        case TokenType::AND: return "AND";
        case TokenType::CLASS: return "CLASS";
        case TokenType::FALSE: return "FALSE";
        case TokenType::FOR: return "FOR";
        case TokenType::IF: return "IF";
        case TokenType::ELIF: return "ELIF";
        case TokenType::ELSE: return "ELSE";
        case TokenType::NULL_TOKEN: return "NULL_TOKEN";
        case TokenType::OR: return "OR";
        case TokenType::P: return "P";
        case TokenType::RETURN: return "RETURN";
        case TokenType::SUPER: return "SUPER";
        case TokenType::THIS: return "THIS";
        case TokenType::TRUE: return "TRUE";
        case TokenType::STRING: return "STRING";
        case TokenType::INT: return "INT";
        case TokenType::BOOL: return "BOOL";
        case TokenType::FLOAT: return "FLOAT";
        case TokenType::WHILE: return "WHILE";
        case TokenType::END: return "END";

        // Special token
        case TokenType::EOF_TOKEN: return "EOF_TOKEN";

        default: return "UNKNOWN_TOKEN";
    }
};

std::string Token::literal_to_string(const std::variant<std::monostate, std::string, int, float, bool>& l)  {
    return std::visit([](auto&& arg) -> std::string {
        if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::monostate>) {
            return "null"; 
        } else {
            std::stringstream ss;
            ss << arg;
            return ss.str();
        }
    }, l);
}

Token::Token(TokenType type, std::string lexeme, std::variant<std::monostate, std::string, int, float, bool> literal, int line) : type(type), lexeme(lexeme), literal(literal), line(line) {}

std::string Token::to_string() {
    std::ostringstream oss;
    oss << token_type_to_string(type) << " " << lexeme << " " << literal_to_string(literal);
    return oss.str();
}
