//Texturse.h
#pragma once
#include "raylib.h"

// Map
extern Texture2D grassTexture;
extern Texture2D stoneTexture;

// Spieler
extern Texture2D SpielerVorne;
extern Texture2D SpielerHinten;
extern Texture2D SpielerLinks;
extern Texture2D SpielerRechts;

// UI
extern Texture2D GridHover;

// Funktionen
void LoadAllTextures();
void UnloadAllTextures();
