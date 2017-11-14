 #include "Token.h"
#include <stdlib.h>
#include <stdio.h>
 
 Token::Token(TokenType type, char *tk_string) : type(type), tk_string(tk_string)
 {
 }
 
 Token::~Token()
 {
     free(tk_string);
 }