#include "../include/lexer.h"

FILE* openFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) { return NULL; }
    return file;
}

Token* parseFile(FILE* file) {
    if (file == NULL) { 
        printf("File is null.\n"); 
        return NULL;
    }

    char buffer[1024];
    Token* curr = NULL;
    Token* temp = NULL;
    Token* head = NULL;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int position = 0;  

        while (buffer[position] != '\0') {
            if (buffer[position] == '<') {
                curr = processTag(buffer, &position);
            }
            else if (buffer[position] == 'S') {
                curr = processDirective(buffer, &position);
                //position++;
            } else {
                position++;
            }
            if (temp != NULL) { temp->next = curr; }
            else { head = curr; }
            temp = curr; 
            if (buffer[position] == '\n') {position++;}
        }
    }

    fclose(file);

    Token* end_token = (Token*)malloc(sizeof(Token));
    end_token->type = END;
    curr->next = end_token;

    return head;
}


Token* processTag(char* input, int* position) {
    int initial_position = *position;

    while (input[*position] != '>' && input[*position] != '\0') { 
        (*position)++; 
    }

    if (input[*position] == '\0') {
        return NULL;
    }

    int length = *position - initial_position;
    char* tagLexeme = malloc(length + 1);  

    if (tagLexeme == NULL) {
        return NULL;  
    }

    strncpy(tagLexeme, 
            input + initial_position, 
            length + 1);
    tagLexeme[length + 1] = '\0'; 

    Token* token = (Token*)malloc(sizeof(Token));
    if (token == NULL) {
        free(tagLexeme); 
        return NULL;    
    }
    token->lexeme = tagLexeme;
    token->type = typeSwitch(tagLexeme);

    (*position)++;  
    return token;
}

Token* processDirective(char* input, int* position) {

    int initial_position = *position;
    while (input[*position] != '\n' && input[*position] != '\0') {
        (*position)++;
    }

    if (input[*position] == '\0') {
        return NULL;
    }

    int length = *position - initial_position;
    char* tagLexeme = malloc(length);  

    if (tagLexeme == NULL) {
        return NULL;  
    }

    strncpy(tagLexeme, 
            input + initial_position, 
            length + 1);
    tagLexeme[length] = '\0'; 

    Token* token = (Token*)malloc(sizeof(Token));
    if (token == NULL) {
        free(tagLexeme); 
        return NULL;    
    }
    token->lexeme = tagLexeme;
    token->type = directiveSwitch(tagLexeme);

    (*position)++;
    return token;
}

TType typeSwitch(char* lexeme) {

    if (strcmp(lexeme, "<head>") == 0) { return HEAD_OPEN; }
    if (strcmp(lexeme, "</head>") == 0) { return HEAD_CLOSE; }
    else { return INVALID; }

}

TType directiveSwitch(char* lexeme) {
    if (strncmp(lexeme, "SET", 3) == 0) { return SET; }
    else { return INVALID; }
}

