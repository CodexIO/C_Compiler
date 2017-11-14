#pragma once

enum TokenType {
    Keyword,
    Constant,
    Operator,
    Identifier
};

struct Token {
    
    TokenType type;
    char *tk_string;
    
    Token(TokenType type, char *tk_string);
    ~Token();
};