#include "raylib.h"
#include "globals.h"
#include "MapRender.h"
#include "Moovment.h"
#include "maus.h"
#include "Textures.h"
#include "Ui.h"
#include "ItemUse.h"
#include "inventar.h"
#include "Wachstum.h"
#include "shop.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "Farm Game");

    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    LoadAllTextures();
    InitWachstum();

    InitMap();


    InitInventar();
    InitShop();
    UpdateWachstum();

	AddItem(ITEM_hacke, 1);
	AddItem(ITEM_spitzhacke, 1);
    AddItem(ITEM_AxtItem, 1);
    AddItem(ITEM_Schaufel, 1);
    //AddItem(ITEM_dirt, 10);
	//AddItem(ITEM_Karrotte, 10);
	//AddItem(ITEM_Erdbaere, 10);
    //AddItem(ITEM_BaumSepling, 10);
    //AddItem(ITEM_HolzItem, 10);

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
        if (shopoffen) {
            openShop();
        }
		
        UpdateWachstum();

        EndDrawing();

        //tests

        
    }

    UnloadAllTextures();
    CloseWindow();
    return 0;
}
