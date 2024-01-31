#include "../../include/components/box.h"

Box* createBox(Token* boxToken) {

    Box* box = (Box*)malloc(sizeof(Box));

    box->token = boxToken;

    setBoxSettings(box, boxToken->lexeme);

    
}

void setBoxSettings(Box* box, char* token_lexeme) {

    int position = 0;

    printf("HERE\n%s\n\n\n\n\n", token_lexeme);

}