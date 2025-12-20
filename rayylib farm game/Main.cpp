#include "raylib.h"
#include "globals.h"
#include "MapRender.h"
#include "Moovment.h"
#include "maus.h"
#include "Textures.h"
#include "Ui.h"
#include "ItemUse.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "Farm Game");

    SetTargetFPS(60);

    LoadAllTextures();

    while (!WindowShouldClose())
    {
        HandleMovement();
        Mausposition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawMap(GetScreenWidth(), GetScreenHeight());
        markierungMaus();

        DrawUI();

        inventarMangage();
		//DevAnsicht(GetScreenWidth(), GetScreenHeight());

        EndDrawing();

        //tests

        
    }

    UnloadAllTextures();
    CloseWindow();
    return 0;
}
