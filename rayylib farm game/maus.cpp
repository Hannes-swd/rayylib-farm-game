//maus.cpp
#include <cstdlib>
#include "raylib.h"
#include "globals.h"
#include "Textures.h"
#include "ItemUse.h"
#include "marmelade.h"

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
            //ERDE ZU DIRT
            if (map[ky][kx] == 0) {
                map[ky][kx] = 2;
                int random = 1 + rand() % 4;
                if (random == 1) AddItem(ITEM_Stein, 1);
            }
            // KAROTTEN ERNTE
            else if (map[ky][kx] == 5) { // was es abbaut
                map[ky][kx] = 2; // Endert zu
                AddItem(ITEM_Karrotte, 3); // giebt 3
            }

            //ERDBERE ERNTE
            else if (map[ky][kx] == 8) { 
                map[ky][kx] = 7;
                int random = 1 + rand() % 4;
                AddItem(ITEM_Erdbaere, random);
			}

            
        }
        else if (AktuellesItem == ITEM_spitzhacke) {
            //STEIN ABBAU
            if (map[ky][kx] == 1) {
                int steinCount = GetItemCount(ITEM_Stein);
                int maxStack = GetMaxStack(ITEM_Stein);

                if (steinCount < maxStack) {
                    map[ky][kx] = 0;
                    AddItem(ITEM_Stein, 1);
                }
            }
            //ERDERE ZERSTÖREN
            if (map[ky][kx] == 6 || map[ky][kx] == 7 || map[ky][kx] == 8) {
                map[ky][kx] = 0;
				AddItem(ITEM_Erdbaere, 1);
			}
        }
        else if (AktuellesItem == ITEM_AxtItem) {
            //BAUM ABFELLEN
            if (map[ky][kx] == 10) {
                int Holzcount = GetItemCount(ITEM_HolzItem);
                int maxStack = GetMaxStack(ITEM_HolzItem);
                if (Holzcount < maxStack) {
                    map[ky][kx] = 0;
                    int random = 1 + rand() % 4;
                    AddItem(ITEM_HolzItem, random);
                    int random2 = 1 + rand() % 2;
                    AddItem(ITEM_BaumSepling, random2);
                }
            }
        }
        else if (AktuellesItem == ITEM_Stein) {
            //STEIN PLAZIEREN
            int steinCount = GetItemCount(ITEM_Stein);

            if (steinCount > 0) {
                if (map[ky][kx] == 0 || map[ky][kx] == 2) {
                    map[ky][kx] = 1;
                    RemoveItem(ITEM_Stein, 1);
                }
            }
        }
        
        else if (AktuellesItem == ITEM_Karrotte) {
            //KAROTTE ANPFKLANZEN
            int karrotteCount = GetItemCount(ITEM_Karrotte);
            if (karrotteCount > 0) {
                if (map[ky][kx] == 2) { 
                    map[ky][kx] = 3; 
                    RemoveItem(ITEM_Karrotte, 1);
                }
            }
        }
        else if (AktuellesItem == ITEM_Erdbaere) {
            //ERDBÄRE ANPFLANZEN && IN MARMELADE VERWANDELN
            int erdbaereCount = GetItemCount(ITEM_Erdbaere);
            if (erdbaereCount > 0) {
                if (map[ky][kx] == 0) { 
                    map[ky][kx] = 6; 
                    RemoveItem(ITEM_Erdbaere, 1);
                }
                else if (map[ky][kx] == 14) {
                    if (MarmeladeMachen) {
                        marmelade(ITEM_Erdbaere, 1, kx, ky);
                    }
                }
            }
		}
        else if (AktuellesItem == ITEM_BaumSepling) {
            //BAUM ANPFLANZEN
            int Baumseplingcount = GetItemCount(ITEM_BaumSepling);
            if (Baumseplingcount > 0) {
                if (map[ky][kx] == 0) {
                    map[ky][kx] = 9;
                    RemoveItem(ITEM_BaumSepling, 1);
                }
            }
        }
        //schaufel graben wasser
        else if (AktuellesItem == ITEM_Schaufel) {
            if (map[ky][kx] == 0 || map[ky][kx] == 2) {
                AddItem(ITEM_dirt, 1);
                bool wasserGefunden = false;

                // Prüfe 4 Richtungen auf Wasser
                int dy[] = { -1, 1, 0, 0 };
                int dx[] = { 0, 0, -1, 1 };

                for (int i = 0; i < 4; i++) {
                    int ny = ky + dy[i];
                    int nx = kx + dx[i];
                    if (ny >= 0 && ny < MAP_H && nx >= 0 && nx < MAP_W && map[ny][nx] == 13) {
                        wasserGefunden = true;
                        break;
                    }
                }

                if (wasserGefunden) {
                    map[ky][kx] = 13;

                    bool neuWasser;
                    do {
                        neuWasser = false;
                        for (int y = 0; y < MAP_H; y++) {
                            for (int x = 0; x < MAP_W; x++) {
                                if (map[y][x] == 13) {
                                    for (int i = 0; i < 4; i++) {
                                        int ny = y + dy[i];
                                        int nx = x + dx[i];
                                        if (ny >= 0 && ny < MAP_H && nx >= 0 && nx < MAP_W && map[ny][nx] == 12) {
                                            map[ny][nx] = 13;
                                            neuWasser = true;
                                        }
                                    }
                                }
                            }
                        }
                    } while (neuWasser);
                }
                else {
                    map[ky][kx] = 12;
                }
            }
        }
        //löcher füllen
        else if (AktuellesItem == ITEM_dirt) {
            if (map[ky][kx] == 12 || map[ky][kx] == 13) {
                int dirtCount = GetItemCount(ITEM_dirt);
                if (dirtCount > 0) {
                    RemoveItem(ITEM_dirt, 1);
                    map[ky][kx] = 0;
                }
            }
        }
        else if (AktuellesItem == 0) {
            //AKERLAND ZU GRASS
            if (map[ky][kx] == 2) {
                map[ky][kx] = 0;
            }
            
        }
        if (map[ky][kx] == 11 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            shopoffen = true;
            inventaroffen = false; // Inventar schließen, wenn Shop öffnet
        }
        
    }
}