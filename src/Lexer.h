                                    #pragma once
#include "Token.h"
                                    
                                    static const char operators[] = {'+', '-', '=', ';'};
                                    static const char whitespace[] = {' ', '\n', '\r', '\t'};
                                    static const char* keywords[] = {"int", "if"};
                                    
#define MAX_IDENTIFIER_LENGTH 1024
                                    
                                    struct Lexer {
                                        
                                        char* text;       //text to Lex
                                        int position; //position in the text
                                        bool finished;
                                        
                                        Lexer(const char* filename);
                                        
                                        Token* parseToken();
                                        
                                        char peekChar();
                                        void eatChar();
                                        void eatWhitespace();
                                        
                                        bool isWhitespace(char c);
                                        bool isCharacter(char c);
                                        bool isOperator(char c);
                                        bool isKeyword(char *string);
                                        bool isNumber(char c);
                                        
                                        char* parseNumber();
                                        char* parseKeywordOrIdentifier();
                };