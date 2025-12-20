//Texturse.h
#pragma once
#include "raylib.h"

// Map
extern Texture2D grassTexture;
extern Texture2D stoneTexture;
extern Texture2D dirtTexture;

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

extern Texture2D HackeItem;
extern Texture2D spitzhackeItem;

// Funktionen
void LoadAllTextures();
void UnloadAllTextures();
