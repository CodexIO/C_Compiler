#include <stdio.h>
#include <stdlib.h>

#include "Lexer.h"

int main(int argc, char *argv[])
{
    
    char *filename;
    
    if (argc == 1) {
        
        printf("Pls enter the file to compile or specify it as argument!\n");
        
        filename = (char*) malloc(sizeof(char) * 1024);
        scanf("%s", filename);
        
    } else { // only supporting 1 File at the Moment, probably for a long time!
        filename = argv[1];
    }
    
    Lexer lx(filename);
    
    printf("Keyword: 0\nConstant: 1\nOperator: 2\nIdentifier: 3\n\n");
    
    while (!lx.finished) {
        Token *tk = lx.parseToken();
        printf("TokenType = %i | String = %s\n", tk->type, tk->tk_string);
        delete(tk);
    }
}
