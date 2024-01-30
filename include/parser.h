#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <stdio.h>
#include <string.h>

typedef struct WindowSettings{
    int width;
    int height;
    char* title;
} WindowSettings;

typedef enum DirectiveType{
    
    WINDOWHEIGHT,
    WINDOWWIDTH,
    WINDOWTITLE

} DirectiveType;

void parseSetDirective(char* lexeme, WindowSettings* settings);
void setDirectiveSettings(char* end_of_lexeme, WindowSettings* settings, DirectiveType dtype);
WindowSettings* handleTokenStream(Token* head);

const char* TTypeToString(TType type);
void printTokenTypes(Token* head);




#endif