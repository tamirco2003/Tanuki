#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include "token.h"

typedef struct _scanner_t {
    FILE* file;
    int length;
    char* buffer;
    int line;

    char current;
    char next;

    unsigned int keywordFlag : 1;
} Scanner_t;

Scanner_t Scanner_Init();
int Scanner_FileOpen(Scanner_t* scanner, const char* filepath);
void Scanner_Advance(Scanner_t* scanner);
void Scanner_AppendAdvance(Scanner_t* scanner);
char* Scanner_GetLexeme(Scanner_t* scanner);
Token_t Scanner_MakeToken(Scanner_t* scanner, TokenType_t type);
Token_t Scanner_NextToken(Scanner_t* scanner);
Token_t Scanner_Number(Scanner_t* scanner);
Token_t Scanner_Keyword(Scanner_t* scanner);

#endif