#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "components/box.h"
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


/**
 * @brief Main parser function to be accessed by lexer after token stream creation
 * 
 * @param head Head token of token stream
 * 
 * @returns The WindowSettings of the raylib object
*/
WindowSettings* handleTokenStream(Token* head);

/**
 * @brief Parses all tokens in head section
 * 
 * @param head Pointer to pointer to head
 * @param settings WindowSettings to be modified in place
*/
void parseHead(Token** head, WindowSettings* settings);

/**
 * @brief Parses a SET directive to set raylib settings
 * 
 * @param lexeme The string lexeme of the set directive token
 * @param settings The WindowSettings object that contains the raylib settings
 * 
*/
void parseSetDirective(char* lexeme, WindowSettings* settings);

/**
 * @brief Given a directive type and end of lexeme, modifies the settings object to reflect set directive
 * 
 * @param end_of_lexeme The end of the lexeme, that is the part that contains the value the object is taking
 * @param settings The WindowSettings* object to be modified
 * @param dtype The type of the directive
 * 
*/
void setDirectiveSettings(char* end_of_lexeme, WindowSettings* settings, DirectiveType dtype);

//Utility functions for testing

/**
 * @brief Takes in a TType and returns the type as a string
 * 
 * @param type Type of a token
 * 
 * @returns The string representation of the type
*/
const char* TTypeToString(TType type);

/**
 * @brief Given the head of a token, prints all the tokens in the stream
 * 
 * @param head The head token. The function restores the pointer to the head when it is done
*/
void printTokenTypes(Token* head);

void parseComponent(Token* token);




#endif