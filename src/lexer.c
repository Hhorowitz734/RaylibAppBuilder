#include "../include/lexer.h"

FILE* openFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) { return NULL; }
    return file;
}

void parseFile(FILE* file) {
    if (file == NULL) { 
        printf("File is null.\n"); 
        return;
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int position = 0;  

        while (buffer[position] != '\0') {
            processTag(buffer, &position); 
        }
    }

    fclose(file);
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

    printf("%s\n", tagLexeme);

    (*position)++;  
    return token;
}

TType typeSwitch(char* lexeme) {

    if (strcmp(lexeme, "<head>") == 0) { return HEAD_OPEN; }
    if (strcmp(lexeme, "</head>") == 0) { return HEAD_CLOSE; }
    else { return INVALID; }

}

