#pragma once
#include "raylib.h"

// Map
extern int map[20][25];

// Spielerinformationen
extern int spielerX;
extern int spielerY;
extern int spielerLeben;
extern int Geld;
extern int tag;
extern int richtung; // 0 = vorne, 1 = hinten, 2 = links, 3 = rechts

// Blöcke
constexpr int TILE_COUNT = 7;
struct Tile {
    bool begangbar;
    bool hackbar;
    bool bepflanzbar;
    bool wasserbar;
};
extern Tile tiles[TILE_COUNT];

// Mausposition
extern int mausX;
extern int mausY;

// Inventar
extern int AktuellesItem;
extern int AktuellerSlot;

// Item liste
typedef enum {
    ITEM_hacke = 1,
    ITEM_spitzhacke = 2,
    ITEM_Stein = 3,
	ITEM_Karrotte = 4,
    ITEM_Erdbaere = 5,
	ITEM_BaumSepling = 6,
    ITEM_HolzItem = 7,
    ITEM_AxtItem = 8
} ItemID;

// Funktionen di braucht
int GetMaxStack(int id);
int GetItemCount(int id);
void AddItem(int id, int amount);
void RemoveItem(int id, int amount);

// Inventar
extern bool inventaroffen;

constexpr int INVENTAR_ROWS = 4;
constexpr int INVENTAR_COLS = 5;
constexpr int INVENTAR_SLOTS = INVENTAR_ROWS * INVENTAR_COLS;

extern int inventar[INVENTAR_SLOTS];
extern int inventarMenge[INVENTAR_SLOTS]; 
void InitInventar(); 

extern int dragSlot; 
extern bool isDragging; 

