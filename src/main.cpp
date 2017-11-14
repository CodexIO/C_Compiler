#include <stdio.h>

#include "Lexer.h"

int main()
{
    Lexer lx("../testfile.txt");
    
    printf("Keyword: 0\nConstant: 1\nOperator: 2\nIdentifier: 3\n\n");
    
    while (!lx.finished) {
        Token *tk = lx.parseToken();
        printf("TokenType = %i | String = %s\n", tk->type, tk->tk_string);
        delete(tk);
    }
}
