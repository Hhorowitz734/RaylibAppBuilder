#include "raylib.h"
#include "include/lexer.h"

int main() {
    FILE* file = openFile("../test.txt");
    parseFile(file);

    return 0;
}
