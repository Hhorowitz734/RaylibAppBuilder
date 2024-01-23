#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum TType {

    BODY_OPEN, //<body>
    HEAD_OPEN, //<head>
    HEAD_CLOSE, //</head>
    SET, //SET

    END, //End Token
    INVALID //Invalid Type


} TType;

typedef struct Token {
    TType type;
    char* lexeme;
    struct Token* next;
} Token;

FILE* openFile(const char* filename);
Token* parseFile(FILE* file);

Token* processTag(char* input, int* position);
TType typeSwitch(char* lexeme);

Token* processDirective(char* input, int* position);
TType directiveSwitch(char* lexeme);

#endif