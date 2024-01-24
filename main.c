#include "raylib.h"
#include "include/lexer.h"
#include "include/parser.h"

int main() {
    FILE* file = openFile("../test.txt");
    Token* head = parseFile(file);

    WindowSettings* settings = handleTokenStream(head);

    InitWindow(settings->width, settings->height, "Test");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
