// Texturse.h 
#pragma once
#include "raylib.h"

// Map
extern Texture2D grassTexture;
extern Texture2D stoneTexture;
extern Texture2D dirtTexture;
extern Texture2D shopTexture;
extern Texture2D tiefeErde;
extern Texture2D Wasser;

//maschienen
extern Texture2D marmeladenTopf;


//pflanzen
extern Texture2D Karotte1Texture;
extern Texture2D Karotte2Texture;
extern Texture2D Karotte3Texture;

extern Texture2D Erdbere1Texture;
extern Texture2D Erdbere2Texture;
extern Texture2D Erdbere3Texture;

extern Texture2D Baum1Texture;
extern Texture2D Baum2Texture;

// Spieler
extern Texture2D SpielerVorne;
extern Texture2D SpielerHinten;
extern Texture2D SpielerLinks;
extern Texture2D SpielerRechts;

// UI
extern Texture2D GridHover;
extern Texture2D InventarSlot;
extern Texture2D HerzIcon;
extern Texture2D GeldIcon;
extern Texture2D AusgewaelterSlot;
extern Texture2D ausrufezeichen;

//items
extern Texture2D HackeItem;
extern Texture2D spitzhackeItem;
extern Texture2D steinItem;
extern Texture2D KarotteItem;
extern Texture2D ErdbaereItem;
extern Texture2D BaumSeplingItem;
extern Texture2D HolzItem;
extern Texture2D AxtItem;
extern Texture2D Schaufel;
extern Texture2D dirtItem;
extern Texture2D ErdbärMarmelade;

// Funktionen
void LoadAllTextures();
void UnloadAllTextures();
