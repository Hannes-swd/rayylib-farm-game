//Textures.cpp
#include "Textures.h"

Texture2D grassTexture = { 0 };
Texture2D stoneTexture = { 0 };
Texture2D dirtTexture = { 0 };

Texture2D SpielerVorne = { 0 };
Texture2D SpielerHinten = { 0 };
Texture2D SpielerLinks = { 0 };
Texture2D SpielerRechts = { 0 };

Texture2D GridHover = { 0 };
Texture2D InventarSlot = { 0 };
Texture2D HerzIcon = { 0 };
Texture2D GeldIcon = { 0 };

Texture2D HackeItem = { 0 };
Texture2D spitzhackeItem = { 0 };

void LoadAllTextures()
{
    if (grassTexture.id != 0) return;

    grassTexture = LoadTexture("resources/grass.png");
    stoneTexture = LoadTexture("resources/stone.png");
	dirtTexture = LoadTexture("resources/dirt.png");

    SpielerVorne = LoadTexture("resources/spieler/Vor.png");
    SpielerHinten = LoadTexture("resources/spieler/Hinten.png");
    SpielerLinks = LoadTexture("resources/spieler/Links.png");
    SpielerRechts = LoadTexture("resources/spieler/rechts.png");

    GridHover = LoadTexture("resources/Ui/CurserRahmen.png");
	InventarSlot = LoadTexture("resources/Ui/InventarSlot.png");
	HerzIcon = LoadTexture("resources/Ui/Hart.png");
	GeldIcon = LoadTexture("resources/Ui/Geld.png");

	HackeItem = LoadTexture("resources/items/hacke.png");
	spitzhackeItem = LoadTexture("resources/items/spitzhacke.png");
}

void UnloadAllTextures()
{
    UnloadTexture(grassTexture);
    UnloadTexture(stoneTexture);
	UnloadTexture(dirtTexture);

    UnloadTexture(SpielerVorne);
    UnloadTexture(SpielerHinten);
    UnloadTexture(SpielerLinks);
    UnloadTexture(SpielerRechts);

    UnloadTexture(GridHover);
	UnloadTexture(InventarSlot);
	UnloadTexture(HerzIcon);
	UnloadTexture(GeldIcon);

	UnloadTexture(HackeItem);
	UnloadTexture(spitzhackeItem);
}
