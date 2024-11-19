#ifndef TOKEN_TYPE_HPP
#define TOKEN_TYPE_HPP

enum class TokenType {
      // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN,
  COMMA, DOT, MINUS, PLUS,SLASH, STAR,

  // One or two character tokens.
  NOT, NOT_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING_LITERAL, INT_LITERAL, FLOAT_LITERAL,

  // Keywords.
  AND, CLASS, FALSE, FOR, IF, ELIF, ELSE, NULL_TOKEN, OR,
  P, RETURN, SUPER, THIS, TRUE, STRING, INT, BOOL, FLOAT, WHILE, END,

  EOF_TOKEN
};

#endif