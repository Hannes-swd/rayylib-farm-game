//globals.h
#pragma once


extern int map[20][25];

//spiler informationen
extern int spielerX;
extern int spielerY;
extern int spielerLeben;
extern int Geld;
extern int tag;
extern int richtung; // 0 = vorne, 1 = hinten

//blöcke
constexpr int TILE_COUNT = 3;
struct Tile {
    bool begangbar;
    bool hackbar;
    bool bepflanzbar;
    bool wasserbar;
};

extern Tile tiles[TILE_COUNT];

//maus position
extern int mausX;
extern int mausY;

//inventar

extern int AktuellesItem;


typedef struct {
    int id;
    int maxStack;
    bool placeable;
    bool consumable;
    bool usable;
    int value;
} ItemDef;

extern ItemDef itemDB[];
extern int itemDBSize;

typedef enum {
    ITEM_hacke = 1,
	ITEM_spitzhacke = 2,
	ITEM_Stein = 3
    
} ItemID;

//items hinzufügen / entfernen
void AddItem(int id, int amount);
void RemoveItem(int id, int amount);
