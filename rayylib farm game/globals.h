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
    int tileId;
    bool placeable;
    bool consumable;
	bool usable;
    int value;
} ItemDef;

typedef enum {
    ITEM_hacke = 1,
	ITEM_spitzhacke = 2
    
} ItemID;