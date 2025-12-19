//MapRender.cpp	
#include "raylib.h"
#include "globals.h"
#include "Moovment.h"

void DrawMap(int screenWidth, int screenHeight)
{
    //Bilder
	Texture2D grassTexture = LoadTexture("resources/grass.png");
    Texture2D stoneTexture = LoadTexture("resources/stone.png");

	//bilder laden
    if (grassTexture.id == 0)
    {
        CloseWindow();
	}
    if (grassTexture.id == 0)
    {
        CloseWindow();
    }
    
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
                //DrawRectangle(posX, posY, tileSize, tileSize, LIME);
                DrawTexturePro(
                    grassTexture,
                    { 0.0f, 0.0f, (float)grassTexture.width, (float)-grassTexture.height },
                    { (float)posX, (float)posY, (float)tileSize, (float)tileSize },
                    { 0.0f, 0.0f },
                    0.0f,
                    WHITE
                );
            }
            else if (map[y][x] == 1)
            {
                DrawRectangle(posX, posY, tileSize, tileSize, LIGHTGRAY);
                DrawTexturePro(
                    stoneTexture,
                    { 0.0f, 0.0f, (float)stoneTexture.width, (float)-stoneTexture.height },
                    { (float)posX, (float)posY, (float)tileSize, (float)tileSize },
                    { 0.0f, 0.0f },
                    0.0f,
                    WHITE
				);
            }
            else
            {
                DrawRectangle(posX, posY, tileSize, tileSize, ORANGE);
            }
        }
    }

    //spieler
	DrawCircle(offsetX + (spielerX * tileSize) + tileSize / 2, offsetY + (spielerY * tileSize) + tileSize / 2, tileSize / 3, BLUE);

}