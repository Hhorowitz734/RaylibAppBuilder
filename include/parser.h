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
    WINDOWWIDTH

} DirectiveType;

void parseSetDirective(char* lexeme, WindowSettings* settings);
void setDirectiveSettings(char* end_of_lexeme, WindowSettings* settings, DirectiveType dtype);


WindowSettings* handleTokenStream(Token* head) {

    WindowSettings* settings = (WindowSettings*)malloc(sizeof(WindowSettings));

    if (head->type != HEAD_OPEN) {
        printf("Token stream must begin with head token.");
    }

    head = head->next;

    while (head->type != HEAD_CLOSE) { //Configures raylib settings

        parseSetDirective(head->lexeme, settings);
        head = head->next;

    }

    return settings; 
    
}

void parseSetDirective(char* lexeme, WindowSettings* settings) {

    int position = 0;

    while (lexeme[position] != ' ' && lexeme[position] != '\0') { position++; } //Iterates past any spaces
    
    position++;
    int initial_position = position;


    while (lexeme[position] != ' ' && lexeme[position] != '\0') { position++; }

    if (strncmp(&lexeme[initial_position], "WINDOWHEIGHT", 12) == 0) {
        setDirectiveSettings(&lexeme[initial_position], settings, WINDOWHEIGHT);
    } else if (strncmp(&lexeme[initial_position], "WINDOWWIDTH", 11) == 0) {
        setDirectiveSettings(&lexeme[initial_position], settings, WINDOWWIDTH);
    }

}

void setDirectiveSettings(char* end_of_lexeme, WindowSettings* settings, DirectiveType dtype) {

    int position = 0;

    //Skip through spaces to number
    while (end_of_lexeme[position] != ' ') { position++; }
    position++;

    if (dtype == WINDOWHEIGHT) {
        settings->height = atoi(&end_of_lexeme[position]);
        printf("[Parser]: Sucessfully set height to: %d\n", settings->height);
    }
    else if (dtype == WINDOWWIDTH) {
        settings->width = atoi(&end_of_lexeme[position]);
        printf("[Parser]: Sucessfully set width to: %d\n", settings->width);
    }

}



#endif