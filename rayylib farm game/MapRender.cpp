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

            
            //zeichne  blöcke

			// 0 = grass
            if (map[y][x] == 0) {
                DrawTexturePro(
                    grassTexture,
                    { 0,0,(float)grassTexture.width,(float)grassTexture.height },
                    { (float)posX,(float)posY,(float)tileSize,(float)tileSize },
                    { 0,0 },
                    0,
                    WHITE
				);
            }
			// 1 = stone
            else if (map[y][x] == 1) {
                DrawTexturePro(
                    stoneTexture,
                    { 0,0,(float)stoneTexture.width,(float)stoneTexture.height },
                    { (float)posX,(float)posY,(float)tileSize,(float)tileSize },
                    { 0,0 },
                    0,
					WHITE
				);
			}
            // 2 = dirt
            else if (map[y][x] == 2) {
                DrawTexturePro(
                    dirtTexture,
                    { 0,0,(float)dirtTexture.width,(float)dirtTexture.height },
                    { (float)posX,(float)posY,(float)tileSize,(float)tileSize },
                    { 0,0 },
                    0,
                    WHITE
                );
			}
            // 3 = karotte1
            else if (map[y][x] == 3) {
                DrawTexturePro(
                    Karotte1Texture,
                    { 0,0,(float)Karotte1Texture.width,(float)Karotte1Texture.height },
                    { (float)posX,(float)posY,(float)tileSize,(float)tileSize },
                    { 0,0 },
                    0,
                    WHITE
                );
			}
            else if (map[y][x] == 4) {
                DrawTexturePro(
                    Karotte2Texture,
                    { 0,0,(float)Karotte2Texture.width,(float)Karotte2Texture.height },
                    { (float)posX,(float)posY,(float)tileSize,(float)tileSize },
                    { 0,0 },
                    0,
                    WHITE
                );
            }
            else if (map[y][x] == 5) {
                DrawTexturePro(
                    Karotte3Texture,
                    { 0,0,(float)Karotte3Texture.width,(float)Karotte3Texture.height },
                    { (float)posX,(float)posY,(float)tileSize,(float)tileSize },
                    { 0,0 },
                    0,
                    WHITE
                );
			}
            //karotte fertig

            //fehler
            else {
                DrawRectangle(posX, posY, tileSize, tileSize, MAGENTA);
			}
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

void DevAnsicht(int screenWidth, int screenHeight)
{
    //spielerposition
	DrawText(TextFormat("Spieler X: %d", spielerX), 10, 10, 20, BLACK);
	DrawText(TextFormat("Spieler Y: %d", spielerY), 10, 40, 20, BLACK);

    //markierung
	DrawText(TextFormat("Maus X: %d", mausX), 10, 80, 20, BLACK);
	DrawText(TextFormat("Maus Y: %d", mausY), 10, 110, 20, BLACK);

    DrawText(TextFormat("Markiert: %d, %d", (mausX - (screenWidth - (MAP_W * (screenWidth / MAP_W < screenHeight / MAP_H ? screenWidth / MAP_W : screenHeight / MAP_H))) / 2) / (screenWidth / MAP_W < screenHeight / MAP_H ? screenWidth / MAP_W : screenHeight / MAP_H),
        (mausY - (screenHeight - (MAP_H * (screenWidth / MAP_W < screenHeight / MAP_H ? screenWidth / MAP_W : screenHeight / MAP_H))) / 2) / (screenWidth / MAP_W < screenHeight / MAP_H ? screenWidth / MAP_W : screenHeight / MAP_H)), 10, 140, 20, BLACK);
    DrawText(TextFormat("MArkierter Block: %d", map[(mausY - (screenHeight - (MAP_H * (screenWidth / MAP_W < screenHeight / MAP_H ? screenWidth / MAP_W : screenHeight / MAP_H))) / 2) / (screenWidth / MAP_W < screenHeight / MAP_H ? screenWidth / MAP_W : screenHeight / MAP_H)]
		[(mausX - (screenWidth - (MAP_W * (screenWidth / MAP_W < screenHeight / MAP_H ? screenWidth / MAP_W : screenHeight / MAP_H))) / 2) / (screenWidth / MAP_W < screenHeight / MAP_H ? screenWidth / MAP_W : screenHeight / MAP_H)]), 10, 170, 20, BLACK);

}
