#include "raylib.h"
#include "include/lexer.h"

int main() {
    FILE* file = openFile("../test.txt");
    Token* head = parseFile(file);

    while (head != NULL){
        printf("%s\n", head->lexeme);
        head = head->next;
    }

    return 0;
}
