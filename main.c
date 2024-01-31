#include "raylib.h"
#include "include/lexer.h"
#include "include/parser.h"

int main() {
    FILE* file = openFile("../test.txt");
    Token* head = parseFile(file);

    printTokenTypes(head);


    WindowSettings* settings = handleTokenStream(head);

    if (settings == NULL) {
        printf("[Main]: Invalid token stream.\n");
        return 1;
    }

    InitWindow(settings->width, settings->height, settings->title);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();


    return 0;
}
