#include "Lexer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

char* readFile(const char* filename)
{
    HANDLE file = CreateFile(filename,
                             GENERIC_READ,
                             FILE_SHARE_READ,
                             NULL,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL
                             );
    
    if(file == INVALID_HANDLE_VALUE) printf("ERROR OPENING FILE, ERROR_CODE = %i\n", GetLastError());
    
    int file_size = GetFileSize(file, NULL);
    
    char* data = (char*) malloc(file_size * sizeof(char) + 1);
    
    DWORD characters_read;
    
    if(ReadFile(file, data, file_size, &characters_read, NULL) == 0) {
        printf("Error Reading File, Error_Code = %i\n", GetLastError());
    }
    
    if(characters_read != file_size) printf("Error not the whole File got read\n");
    
    data[file_size] = '\0';
    
    CloseHandle(file);
    
    return data;
}

Lexer::Lexer(const char* filename)
{
    text = readFile(filename);
    position = 0;
    finished = false;
}

char Lexer::peekChar()
{
    return text[position];
}

void Lexer::eatChar()
{
    position++;
}

void Lexer::eatWhitespace()
{
    while( isWhitespace(peekChar()) ) {
        eatChar();
    }
}

bool Lexer::isWhitespace(char c)
{
    for (char w : whitespace) {
        if (c == w) return true;
    }
    return false;
}

bool Lexer::isNumber(char c)
{
    return c >= '0' && c <= '9';
}

bool Lexer::isKeyword(char* string)
{
    for(const char* s : keywords) {
        if (!strcmp(string, s)) return true;
    }
    return false;
}

bool Lexer::isCharacter(char c)
{
    return isalpha(c);
}

bool Lexer::isOperator(char c)
{
    for (char o : operators) {
        if (c == o) return true;
    }
    return false;
}

char* Lexer::parseNumber()
{
    char c = peekChar();
    char* number = (char*) malloc(sizeof(char) * MAX_IDENTIFIER_LENGTH);
    
    int i;
    for(i = 0; isNumber(c); i++) {
        eatChar();
        
        number[i] = c;
        c = peekChar();
    }
    number[i] = '\0';
    
    return number;
}

char* Lexer::parseKeywordOrIdentifier()
{
    char *start = &text[position];
    char *keyw_or_ident = (char*) malloc(sizeof(char) * MAX_IDENTIFIER_LENGTH);
    
    char c = peekChar();
    int i;
    for(i = 0; isCharacter(c) ; i++) {
        keyw_or_ident[i] = c;
        
        eatChar();
        c = peekChar();
    }
    
    keyw_or_ident[i] = '\0';
    
    return keyw_or_ident;
}

Token* Lexer::parseToken()
{
    eatWhitespace();
    char c = peekChar();
    char *tk_string;
    enum TokenType tk_type; // Dunno why we need C style enum variable declaration
    
    if (isNumber(c)) {
        
        tk_string = parseNumber();
        tk_type = Constant;
        
    }
    
    else if (isCharacter(c)){
        
        tk_string = parseKeywordOrIdentifier();
        tk_type = isKeyword(tk_string) ? Keyword : Identifier;
        
    }
    
    else if (isOperator(c)) {
        eatChar();
        
        tk_string = (char*) malloc(sizeof(char) * 3);
        tk_string[0] = c;
        
        if(peekChar() == '=') {
            tk_string[1] = '=';
            tk_string[2] = '\0';
            
            eatChar();
        } else {
            tk_string[1] = '\0';
        }
        
        tk_type = Operator;
        
    } else {
        printf("Error Unknown TokenType\n");
    }
    
    eatWhitespace();
    if(peekChar() == '\0') finished = true;
    
    return new Token(tk_type, tk_string);
}