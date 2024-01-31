#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum TType {

    // Section definition tokens
    BODY_OPEN, //<body>
    BODY_CLOSE, //</body>
    HEAD_OPEN, //<head>
    HEAD_CLOSE, //</head>

    // Directive Tokens
    SET, //SET

    // Component Tokens
    BOX,

    // Utility Type Tokens
    END, //End Token
    INVALID //Invalid Type


} TType;

typedef struct Token {
    TType type;
    char* lexeme;
    struct Token* next;
} Token;

/**
 * @brief Opens a file given its filename
 * 
 * @note Used as a utility function to read whatever file we are parsing
 * 
 * @param filename String name of the file to open
*/
FILE* openFile(const char* filename);

/**
 * @brief Lexes the file, breaks it down into tokens to be further processed by parser
 * 
 * @param file The file object, obtained using openFile utility function
 * 
 * @returns The head token of the token stream
 * @note Token stream operates as a linked list, with end token having type END
*/
Token* parseFile(FILE* file);

/**
 * @brief Processes a <> tag for an element
 * 
 * @param input The input string (line of a file provided by parseFile function)
 * @param position Pointer to int holding position in line
 * 
 * @returns The Token* of the tag
 * 
 * @note Used as a utility function for parseFile
*/
Token* processTag(char* input, int* position);

/**
 * @brief Returns the token type of a Token given its lexeme
 * 
 * @param lexeme The lexeme to get the type of
 * 
 * @returns The TType that should be assigned to a token with that lexeme
 * 
 * @note Potentially will be renamed to tagSwitch in a future version of this program
 * @note Used as a utility function for processTag
*/
TType typeSwitch(char* lexeme);

/**
 * @brief Processes a directive tag like SET as part of the head
 * 
 * @param input The input string (line of a file provided by parseFile function)
 * @param position Pointer to int holding position in line
 * 
 * @returns The Token* pointer to the directive's token
 * 
 * @note Used as a utility function for parseFile
*/
Token* processDirective(char* input, int* position);

Token* processComponent(char* input, int* position);

/**
 * @brief Returns the token type of a directive Token given its lexeme
 * 
 * @param lexeme The lexeme to get the type of
 * 
 * @returns The TType that should be assigned to a token with that lexeme
 * 
 * @note Potentially will be renamed to tagSwitch in a future version of this program
 * @note Used as a utility function for processTag
*/
TType directiveSwitch(char* lexeme);

TType componentSwitch(char* lexeme);

#endif