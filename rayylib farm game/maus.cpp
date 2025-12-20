//maus.cpp
#include "raylib.h"
#include "globals.h"
#include "Textures.h"

constexpr int MAP_W = 25;
constexpr int MAP_H = 20;

void Mausposition()
{
    Vector2 m = GetMousePosition();
    mausX = (int)m.x;
    mausY = (int)m.y;
}

void markierungMaus()
{
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    int tileSize = (sw / MAP_W < sh / MAP_H) ? sw / MAP_W : sh / MAP_H;
    int offsetX = (sw - MAP_W * tileSize) / 2;
    int offsetY = (sh - MAP_H * tileSize) / 2;

    Rectangle mapRect = {
        (float)offsetX,
        (float)offsetY,
        (float)(MAP_W * tileSize),
        (float)(MAP_H * tileSize)
    };

    Vector2 mouse = GetMousePosition();

    if (!CheckCollisionPointRec(mouse, mapRect))
        return;

    int kx = (mouse.x - offsetX) / tileSize;
    int ky = (mouse.y - offsetY) / tileSize;

    if (kx < 0 || kx >= MAP_W || ky < 0 || ky >= MAP_H)
        return;

    DrawTexturePro(
        GridHover,
        { 0,0,(float)GridHover.width,(float)GridHover.height },
        { (float)(offsetX + kx * tileSize),(float)(offsetY + ky * tileSize),(float)tileSize,(float)tileSize },
        { 0,0 },
        0,
        WHITE
    );
}
