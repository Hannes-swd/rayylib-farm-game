// maus.cpp
#include "raylib.h"
#include "globals.h"
#include "Moovment.h"
//bilder laden

void Mausposition() {
	Vector2 mausPosition = GetMousePosition();
	mausX = static_cast<int>(mausPosition.x);
	mausY = static_cast<int>(mausPosition.y);
	
}
void markierungMaus()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int tileWidth = screenWidth / 25;
    int tileHeight = screenHeight / 20;
    int tileSize = (tileWidth < tileHeight) ? tileWidth : tileHeight;

    int offsetX = (screenWidth - (25 * tileSize)) / 2;
    int offsetY = (screenHeight - (20 * tileSize)) / 2;

    Vector2 mouse = GetMousePosition();

    Rectangle mapRect = {
        (float)offsetX,
        (float)offsetY,
        (float)(25 * tileSize),
        (float)(20 * tileSize)
    };

    // Wenn Maus nicht über der Map  Text anzeigen und raus
    if (!CheckCollisionPointRec(mouse, mapRect))
    {
        DrawText("Maus nicht auf der Map", 10, 10, 20, DARKGRAY);
        return;
    }

    int kachelX = (mouse.x - offsetX) / tileSize;
    int kachelY = (mouse.y - offsetY) / tileSize;

    // Hover-Rand zeichnen
    DrawRectangleLines(
        offsetX + kachelX * tileSize,
        offsetY + kachelY * tileSize,
        tileSize,
        tileSize,
        RED
    );

    // Tile-Typ bestimmen
    int tileType = map[kachelY][kachelX];
    const char* tileName =
        (tileType == 0) ? "Grass" :
        (tileType == 1) ? "Stone" : "Unknown";

    // Info oben anzeigen
    DrawText(
        TextFormat("Tile: X=%d Y=%d | Typ: %s", kachelX, kachelY, tileName),
        10, 10,
        20,
        BLACK
    );
}

