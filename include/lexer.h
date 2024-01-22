#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum TType {

    BODY_OPEN, //<body>
    HEAD_OPEN, //<head>
    HEAD_CLOSE, //</head>


    INVALID //Invalid Type


} TType;

typedef struct Token {
    TType type;
    char* lexeme;
} Token;

FILE* openFile(const char* filename);
void parseFile(FILE* file);

Token* processTag(char* input, int* position);
TType typeSwitch(char* lexeme);

#endif