//Wachstum.cpp
#include "raylib.h"
#include "globals.h"
#include <cstdlib>
#include <ctime>

#define MAP_W 25
#define MAP_H 20
// Wachstum-Einstellungen
#define WACHSTUMS_INTERVALL 10.0f    //zeit zwischen wachsen

struct PflanzenInfo {
    int startID;        
    int maxWachstum;    
    float wachstumsChance; 
};

// Pflanzen-Definitionen
PflanzenInfo karotteInfo = {
    3,           
    3,           
    0.3f         
};

float wachstumsTimer = 0.0f;

void InitWachstum() {
    wachstumsTimer = 0.0f;
}

bool IstPflanze(int blockID, PflanzenInfo* pflanze) {
    if (pflanze == nullptr) return false;
    return blockID >= pflanze->startID &&
        blockID < pflanze->startID + pflanze->maxWachstum;
}

// Wachsfunktion
void LassePflanzeWachsen(int x, int y, PflanzenInfo* pflanze) {
    if (pflanze == nullptr) return;

    int currentID = map[y][x];

    if (currentID < pflanze->startID + pflanze->maxWachstum - 1) {

        float chance = pflanze->wachstumsChance;

        float randomValue = (float)rand() / (float)RAND_MAX;

        if (randomValue <= chance) {
            map[y][x] = currentID + 1;
        }
    }
}

void UpdateWachstum() {
    float deltaTime = GetFrameTime();
    wachstumsTimer += deltaTime;

    if (wachstumsTimer >= WACHSTUMS_INTERVALL) {
        wachstumsTimer = 0.0f;

        for (int y = 0; y < MAP_H; y++) {
            for (int x = 0; x < MAP_W; x++) {
                int blockID = map[y][x];

                if (IstPflanze(blockID, &karotteInfo)) {
                    LassePflanzeWachsen(x, y, &karotteInfo);
                }
            }
        }
    }
}