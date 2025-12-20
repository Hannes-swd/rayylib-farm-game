//maus.cpp
#include <cstdlib>
#include "raylib.h"
#include "globals.h"
#include "Textures.h"
#include "ItemUse.h"

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

    // abstand zum Spieler
    int dx = abs(kx - spielerX);
    int dy = abs(ky - spielerY);

    if (dx + dy > 2)
        return;

    // Zeichne die Markierung
    DrawTexturePro(
        GridHover,
        { 0, 0, (float)GridHover.width, (float)GridHover.height },
        { (float)(offsetX + kx * tileSize),
          (float)(offsetY + ky * tileSize),
          (float)tileSize,
          (float)tileSize },
        { 0, 0 },
        0,
        WHITE
    );

    // Mausklicks
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (AktuellesItem == ITEM_hacke) {
            if (map[ky][kx] == 0) {
                map[ky][kx] = 2;
                int that = 1 + rand() % 4;
                if (that == 1) AddItem(ITEM_Stein, 1);
            }
        }
        else if (AktuellesItem == ITEM_spitzhacke) {
            if (map[ky][kx] == 1) {
                int steinCount = GetItemCount(ITEM_Stein);
                int maxStack = GetMaxStack(ITEM_Stein);

                if (steinCount < maxStack) {
                    map[ky][kx] = 0;
                    AddItem(ITEM_Stein, 1);
                }
            }
        }
        else if (AktuellesItem == ITEM_Stein) {
            int steinCount = GetItemCount(ITEM_Stein);

            if (steinCount > 0) {
                if (map[ky][kx] == 0 || map[ky][kx] == 2) {
                    map[ky][kx] = 1;
                    RemoveItem(ITEM_Stein, 1);
                }
            }
        }
    }
}