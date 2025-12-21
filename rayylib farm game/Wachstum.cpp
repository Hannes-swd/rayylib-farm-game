// Wachstum.cpp
#include "Wachstum.h"      // WICHTIG: Eigene Header zuerst
#include "globals.h"       // Dann globals
#include <cstdlib>
#include <ctime>

// --- KAROTTEN DEFINIEREN (hier, nicht in .h) ---
PflanzenInfo karotteInfo = {
    3,      // startID (Block 3)
    3,      // 3 Wachstumsstufen (3,4,5)
    0.2f,   // 40% Chance zu wachsen
    3,      // 3 Karotten bei Ernte
    20.0f,  // Basis: alle 10 Sekunden wachsen prüfen
    0.5f,   // WACHSTUMSFAKTOR: 0.5 = HALB SO SCHNELL!
    "Karotte"
};

// Timer
float wachstumsTimer = 0.0f;

void InitWachstum() {
    wachstumsTimer = 0.0f;
    srand((unsigned int)time(NULL));
}

PflanzenInfo* GetPflanzenInfo(int blockID) {
    if (blockID >= karotteInfo.startID &&
        blockID < karotteInfo.startID + karotteInfo.maxWachstum) {
        return &karotteInfo;
    }
    return nullptr;
}

//WACHSTUM UPDATE
void UpdateWachstum() {
    float deltaTime = GetFrameTime();

    
    wachstumsTimer += deltaTime * karotteInfo.wachstumsFaktor;

    if (wachstumsTimer >= karotteInfo.basisIntervall) {
        wachstumsTimer = 0.0f;

        // Alle Karotten auf der Map
        for (int y = 0; y < MAP_H; y++) {
            for (int x = 0; x < MAP_W; x++) {
                int blockID = map[y][x];

                if (blockID >= karotteInfo.startID &&
                    blockID < karotteInfo.startID + karotteInfo.maxWachstum - 1) {

                    float randomValue = (float)rand() / (float)RAND_MAX;
                    if (randomValue <= karotteInfo.wachstumsChance) {
                        map[y][x] = blockID + 1;
                    }
                }
            }
        }
    }
}