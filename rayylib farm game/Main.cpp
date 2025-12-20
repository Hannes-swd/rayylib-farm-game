//Main.cpp
#include "raylib.h"

//dateien
#include "globals.h"
#include "MapRender.h"
#include "Moovment.h"
#include "maus.h"

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
		//hintergrund
        ClearBackground(RAYWHITE);
        //map
        DrawMap(screenWidth, screenHeight);
        
		//spieler bewegung
        HandleMovement();
        Mausposition();
        markierungMaus();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}