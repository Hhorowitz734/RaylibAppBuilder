#ifndef BOX_H
#define BOX_H

#include "raylib.h"
#include "../lexer.h"
#include <stdio.h>

typedef struct Box {
    float width;
    float height;

    float borderWidth;
    Color borderColor;

    bool isFilled;
    Color fillColor;
    
    Token* token;

} Box;

void setBoxSettings(Box* box, char* token_lexeme);

Box* createBox(Token* boxToken);








#endif