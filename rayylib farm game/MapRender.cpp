//MapRender.cpp
#include "raylib.h"
#include "globals.h"
#include "Textures.h"

constexpr int MAP_W = 25;
constexpr int MAP_H = 20;

void DrawMap(int screenWidth, int screenHeight)
{
    int tileWidth = screenWidth / MAP_W;
    int tileHeight = screenHeight / MAP_H;
    int tileSize = (tileWidth < tileHeight) ? tileWidth : tileHeight;

    int offsetX = (screenWidth - (MAP_W * tileSize)) / 2;
    int offsetY = (screenHeight - (MAP_H * tileSize)) / 2;

    // Map
    for (int y = 0; y < MAP_H; y++)
    {
        for (int x = 0; x < MAP_W; x++)
        {
            int posX = offsetX + x * tileSize;
            int posY = offsetY + y * tileSize;

            Texture2D tex = (map[y][x] == 0) ? grassTexture : stoneTexture;

            DrawTexturePro(
                tex,
                { 0,0,(float)tex.width,(float)tex.height },
                { (float)posX,(float)posY,(float)tileSize,(float)tileSize },
                { 0,0 },
                0,
                WHITE
            );
        }
    }

    // Spieler
    float px = offsetX + spielerX * tileSize;
    float py = offsetY + spielerY * tileSize;

    Texture2D spielerTex = SpielerVorne;
    if (richtung == 1) spielerTex = SpielerHinten;
    if (richtung == 2) spielerTex = SpielerLinks;
    if (richtung == 3) spielerTex = SpielerRechts;

    DrawTexturePro(
        spielerTex,
        { 0,0,(float)spielerTex.width,(float)spielerTex.height },
        { px,py,(float)tileSize,(float)tileSize },
        { 0,0 },
        0,
        WHITE
    );
}
