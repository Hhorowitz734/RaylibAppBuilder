#include "../../include/components/box.h"

Box* createBox(Token* boxToken) {

    Box* box = (Box*)malloc(sizeof(Box));

    box->token = boxToken;

    setBoxSettings(box, boxToken->lexeme);

    return box;

    
}

void setBoxSettings(Box* box, char* tokenLexeme) {

    int position = 0;
    int initial_position = 0;

    //Skips the "<BOX " part
    while (tokenLexeme[position] != ' ') { position++; }

    while (tokenLexeme[position] != '\0') {  //Until lexeme ends

        initial_position = position;
        
        while (tokenLexeme[position] != '=') { position++; } // Goes up to the first settings, if it exists

        char* setting = malloc(position - initial_position + 1);
        strncpy(setting, &tokenLexeme[initial_position + 1], position - initial_position);

        setting[position - initial_position] = '\0';

        while (tokenLexeme[position] == ' ' || tokenLexeme[position] == '=') { position++; } //Skips to value

        initial_position = position;

        while (tokenLexeme[position] != ' ') { position++; } //Goes through value

        char* value = malloc(position - initial_position + 1);
        strncpy(value, &tokenLexeme[initial_position], position - initial_position);
        value[position - initial_position] = '\0';

        int i_value = atoi(value);

        switchSettings(box, setting, i_value);

        while (tokenLexeme[position] != '\0' && tokenLexeme[position] != '|') { position++; } //Goes until next variable or end


        
    }

}

void switchSettings(Box* box, char* setting, int value) {

    if (strncmp(setting, "WIDTH", 5) == 0) { 
        box->width = value;
        printf("[Box Parser]: Set box width to: %d\n", box->width); 
        logMessage("[Box Parser]: Set box width to: %d", box->width);
    }

    else if (strncmp(setting, " HEIGHT", 7) == 0 || strncmp(setting, "HEIGHT", 6) == 0) {
        box->height = value;
        printf("[Box Parser]: Set box height to: %d\n", box->height);
        logMessage("[Box Parser]: Set box height to: %d", box->height);
    }
    else {
        printf("%s\n", setting);
    }

}
