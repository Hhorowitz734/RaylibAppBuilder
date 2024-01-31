#include "../../include/components/box.h"

Box* createBox(Token* boxToken) {

    Box* box = (Box*)malloc(sizeof(Box));

    box->token = boxToken;

    setBoxSettings(box, boxToken->lexeme);

    
}

void setBoxSettings(Box* box, char* tokenLexeme) {

    int position = 0;
    int initial_position = 0;

    while (tokenLexeme[position] != ' ') { position++; }

    while (tokenLexeme[position] != '\0') { 

        initial_position = position;
        
        while (tokenLexeme[position] != '=') { position++; }

        char* setting = malloc(position - initial_position + 1);
        strncpy(setting, &tokenLexeme[initial_position + 1], position - initial_position);

        setting[position - initial_position] = '\0';

        while (tokenLexeme[position] == ' ' || tokenLexeme[position] == '=') { position++; }

        initial_position = position;

        while (tokenLexeme[position] != ' ') { position++; }

        char* value = malloc(position - initial_position + 1);
        strncpy(value, &tokenLexeme[initial_position], position - initial_position);
        value[position - initial_position] = '\0';

        int i_value = atoi(value);

        switchSettings(box, setting, i_value);

        while (tokenLexeme[position] != '\0' && tokenLexeme[position] != '|') { position++; }


        
    }

}

void switchSettings(Box* box, char* setting, int value) {

    if (strncmp(setting, "WIDTH", 5) == 0) { 
        box->width = value;
        printf("[Box Parser]: Set box width to: %d\n", box->width); }
    else if (strncmp(setting, " HEIGHT", 7) == 0) {
        box->height = value;
        printf("[Box Parser]: Set box height to: %d\n", box->height);
    }
    else {
        printf("%s\n", setting);
    }

}
