#ifndef BOX_H
#define BOX_H

#include "raylib.h"
#include "../lexer.h"
#include <stdio.h>
#include <string.h>

typedef struct Box {

    char* name; 

    int x;
    int y;

    int width;
    int height;

    float borderWidth;
    Color borderColor;

    bool isFilled;
    Color fillColor;
    
    Token* token;

} Box;

void setBoxSettings(Box* box, char* token_lexeme);

Box* createBox(Token* boxToken);

void switchSettings(Box* box, char* setting, int value);








#endif