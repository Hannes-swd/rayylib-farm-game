//maus.cpp
#include <cstdlib>
#include "raylib.h"
#include "globals.h"
#include "Textures.h"
#include "ItemUse.h"
#pragma once


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

    // Distanz zum Spieler
    int dx = abs(kx - spielerX);
    int dy = abs(ky - spielerY);

    if (dx + dy > 2)
        return;
    
    
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
                int index = ITEM_Stein - 1;
                if (itemDB[index].value < itemDB[index].maxStack) {
                    map[ky][kx] = 0;
                    AddItem(ITEM_Stein, 1);
                }
                // leer
            }
        }
        else if (AktuellesItem == ITEM_Stein) {
            int index = ITEM_Stein - 1;
            if (itemDB[index].value > 0) {
                if (map[ky][kx] == 0 || map[ky][kx] == 2) {
                    map[ky][kx] = 1;
                    RemoveItem(ITEM_Stein, 1);
                }
            }
        }

    }
}
