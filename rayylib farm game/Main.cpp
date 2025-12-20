#include "raylib.h"
#include "globals.h"
#include "MapRender.h"
#include "Moovment.h"
#include "maus.h"
#include "Textures.h"
#include "Ui.h"
#include "ItemUse.h"
#include "inventar.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "Farm Game");

    SetTargetFPS(60);

    LoadAllTextures();

    InitInventar();

	AddItem(ITEM_hacke, 1);
	AddItem(ITEM_spitzhacke, 1);

    while (!WindowShouldClose())
    {
        HandleMovement();
        Mausposition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawMap(GetScreenWidth(), GetScreenHeight());

		//plazieren/entfernen/bearbeiten von blöcken
        markierungMaus();

        DrawUI();

        inventarMangage();

        openinventar();
		//DevAnsicht(GetScreenWidth(), GetScreenHeight());

        EndDrawing();

        //tests

        
    }

    UnloadAllTextures();
    CloseWindow();
    return 0;
}
