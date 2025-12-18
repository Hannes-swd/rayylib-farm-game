//Main.cpp
#include "raylib.h"

//dateien
#include "globals.h"
#include "MapRender.h"
#include "Moovment.h"

int main(void)
{
    int screenWidth = 800;
    int screenHeight = 450;

    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Farm Game");

    SetWindowMinSize(400, 300);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //fenster
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        HandleMovement();
        DrawMap(screenWidth, screenHeight);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}