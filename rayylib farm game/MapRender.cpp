//MapRender.cpp	
#include "raylib.h"
#include "globals.h"

void DrawMap(int screenWidth, int screenHeight)
{
    //map einstellungen
    int tileWidth = screenWidth / 25;
    int tileHeight = screenHeight / 20;

    int tileSize = (tileWidth < tileHeight) ? tileWidth : tileHeight;

    int offsetX = (screenWidth - (25 * tileSize)) / 2;
    int offsetY = (screenHeight - (20 * tileSize)) / 2;

    // Map
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 25; x++)
        {
            int posX = offsetX + (x * tileSize);
            int posY = offsetY + (y * tileSize);

            if (map[y][x] == 0)
            {
                DrawRectangle(posX, posY, tileSize, tileSize, LIGHTGRAY);
                
            }
            if (map[y][x] == 1)
            {
                DrawRectangle(posX, posY, tileSize, tileSize, ORANGE);
            }
        }
    }

}