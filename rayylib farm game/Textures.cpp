//Textures.cpp
#include "Textures.h"

Texture2D grassTexture = { 0 };
Texture2D stoneTexture = { 0 };

Texture2D SpielerVorne = { 0 };
Texture2D SpielerHinten = { 0 };
Texture2D SpielerLinks = { 0 };
Texture2D SpielerRechts = { 0 };

Texture2D GridHover = { 0 };

void LoadAllTextures()
{
    if (grassTexture.id != 0) return;

    grassTexture = LoadTexture("resources/grass.png");
    stoneTexture = LoadTexture("resources/stone.png");

    SpielerVorne = LoadTexture("resources/spieler/Vor.png");
    SpielerHinten = LoadTexture("resources/spieler/Hinten.png");
    SpielerLinks = LoadTexture("resources/spieler/Links.png");
    SpielerRechts = LoadTexture("resources/spieler/rechts.png");

    GridHover = LoadTexture("resources/Ui/CurserRahmen.png");
}

void UnloadAllTextures()
{
    UnloadTexture(grassTexture);
    UnloadTexture(stoneTexture);

    UnloadTexture(SpielerVorne);
    UnloadTexture(SpielerHinten);
    UnloadTexture(SpielerLinks);
    UnloadTexture(SpielerRechts);

    UnloadTexture(GridHover);
}
