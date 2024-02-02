#include "include/lexer.h"
#include "include/parser.h"
#include "include/display.h"

int main() {

    initLogfile();

    FILE* file = openFile("../test.txt");
    Token* head = parseFile(file);

    printTokenTypes(head);
    RunContainer* container = handleTokenStream(head);

    displayContainer(container);



    return 0;
}
