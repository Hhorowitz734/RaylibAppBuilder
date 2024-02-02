#include "../include/display.h"

void displayContainer(RunContainer* container) {

    //Extract settings and head component node from runcontainer
    WindowSettings* settings = container->settings;
    ComponentNode* headComponent = container->head;

    //Initialize a raylib window with proper settings

    if (settings == NULL) {
        printf("[Display Engine]: Invalid token stream.\n");
        logMessage("[Display Engine]: Invalid token stream");
    }

    InitWindow(settings->width, settings->height, settings->title);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();



}