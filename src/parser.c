#include "../include/parser.h"

RunContainer* handleTokenStream(Token* head) {

    WindowSettings* settings = (WindowSettings*)malloc(sizeof(WindowSettings));
    ComponentNode* headComponent = (ComponentNode*)malloc(sizeof(ComponentNode));

    parseHead(&head, settings);

    parseBody(&head, headComponent);

    RunContainer* container = (RunContainer*)malloc(sizeof(RunContainer));
    container->head = headComponent;
    container->settings = settings;

    return container;

}

void parseHead(Token** head, WindowSettings* settings) {

    if ((*head)->type != HEAD_OPEN) {
        printf("[Parser]: Token stream must begin with head token.\n");
        logMessage("[Parser]: Token stream must begin with head token. See function parseHead.");
    }

    *head = (*head)->next; // Skips HEAD_OPEN

    while ((*head)->type != HEAD_CLOSE && (*head)->type != END && (*head)->next != NULL) { //Configures raylib settings

        parseSetDirective((*head)->lexeme, settings);
        *head = (*head)->next;

    }

    *head = (*head)->next; //Skips HEAD_CLOSE
}

void parseBody(Token** head, ComponentNode* headCNode) {

    if ((*head)->type != BODY_OPEN) {
        printf("[Parser]: Unrecognized token %s between head and body.\n", TTypeToString((*head)->type));
        logMessage("[Parser]: Unrecognized token %s between head and body.\n", TTypeToString((*head)->type));
    }

    *head = (*head)->next; //Skips BODY_OPEN

    while ((*head)->type != BODY_CLOSE && (*head)->type != END && (*head)->next != NULL) {
        
        parseComponent(*head, headCNode);
        *head = (*head)->next;
    }


}


void parseSetDirective(char* lexeme, WindowSettings* settings) {

    int position = 0;

    while (lexeme[position] != ' ' && lexeme[position] != '\0') { position++; } //Iterates past any spaces
    
    position++;
    int initial_position = position;


    while (lexeme[position] != ' ' && lexeme[position] != '\0') { position++; }

    DirectiveType directiveType = WINDOWHEIGHT; //CREATE A DEFAULT VALUE INSTEAD OF USING THIS

    if (strncmp(&lexeme[initial_position], "WINDOWHEIGHT", 12) == 0) {
        directiveType = WINDOWHEIGHT;
    } else if (strncmp(&lexeme[initial_position], "WINDOWWIDTH", 11) == 0) {
        directiveType = WINDOWWIDTH;
    } else if (strncmp(&lexeme[initial_position], "WINDOWTITLE", 11) == 0) {
        directiveType = WINDOWTITLE;
    }

    if (directiveType != -1) {
        setDirectiveSettings(&lexeme[initial_position], settings, directiveType);
    }

}

void setDirectiveSettings(char* end_of_lexeme, WindowSettings* settings, DirectiveType dtype) {

    int position = 0;

    //Skip through spaces to number
    while (end_of_lexeme[position] != ' ') { position++; }
    position++;

    switch (dtype) {

        case WINDOWHEIGHT:
            settings->height = atoi(&end_of_lexeme[position]);
            printf("[Parser]: Successfully set height to: %d\n", settings->height);
            logMessage("[Parser]: Successfully set height to: %d", settings->height);
            break;

        case WINDOWWIDTH:
            settings->width = atoi(&end_of_lexeme[position]);
            printf("[Parser]: Successfully set width to: %d\n", settings->width);
            logMessage("[Parser]: Successfully set width to: %d", settings->width);
            break;

        case WINDOWTITLE:
            settings->title = &end_of_lexeme[position];
            // BE CAREFUL WITH MEMORY DEALLOCATION ERROR HERE !!!!! VERY ERROR PRONE CODE
            printf("[Parser]: Successfully set title to: %s\n", settings->title);
            logMessage("[Parser]: Successfully set title to: %s", settings->title);
            break;

        default:
            break;
    }



}


const char* TTypeToString(TType type) {
    switch (type) {
        case BODY_OPEN:
            return "BODY_OPEN";
        case BODY_CLOSE:
            return "BODY_CLOSE";
        case HEAD_OPEN:
            return "HEAD_OPEN";
        case HEAD_CLOSE:
            return "HEAD_CLOSE";
        case SET:
            return "SET";
        case BOX:
            return "BOX";
        case END:
            return "END";
        case INVALID:
            return "INVALID";
        default:
            return "UNKNOWN";
    }
}

void printTokenTypes(Token* head) {

    Token* temp = head;

    logMessage("Parser recieved following types\n-------------------------------");

    if (head != NULL) {
        printf("%s\n", TTypeToString(head->type));
        logMessage("%s", TTypeToString(head->type));
    }

    while (head != NULL && head->type != END) {
        head = head->next;
        printf("%s\n", TTypeToString(head->type));
        logMessage("%s", TTypeToString(head->type));
    }

    logMessage("Token stream ended.\n-------------------------------");

    head = temp;

}


void parseComponent(Token* token, ComponentNode* head) {

    ComponentNode* temp = head;

    if (token->type == BOX) {
        
        Box* box = createBox(token);

        while (temp->left != NULL) { temp = temp->left; } //Add a tree structure addition later
        
        ComponentNode* newNode = (ComponentNode*)malloc(sizeof(ComponentNode));
        newNode->box = box;
        newNode->left = NULL;
        newNode->right = NULL;

        temp->left = newNode;   
        
    }
    

    
}