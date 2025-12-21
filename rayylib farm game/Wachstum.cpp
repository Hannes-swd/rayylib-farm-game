// Wachstum.cpp
#include "Wachstum.h" 
#include "globals.h" 
#include <cstdlib>
#include <ctime>

//KAROTTEN
PflanzenInfo karotteInfo = {
    3,      // startID (Block 3)
    3,      // 3 Wachstumsstufen (3,4,5)
    0.2f,   // 40% Chance zu wachsen
    3,      // 3 Karotten bei Ernte
    20.0f,  // Basis: alle 20 Sekunden wachsen prüfen
    0.5f,   // WACHSTUMSFAKTOR: 0.5 = HALB SO SCHNELL!
    "Karotte"
};

//Erdbeere
PflanzenInfo ErdbaereInfo = {
    6,      
    3,      
    0.2f,   
    3,      
    20.0f,  
    0.5f,   
    "Erdbeere"
};

//Baum
PflanzenInfo BaumInfo = {
    9,      
    2,      
    0.2f,   
    3,      
    10.0f,  
    0.5f,   
    "Baum"
};

float karottenTimer = 0.0f;
float erdbeerenTimer = 0.0f;
float baumTimer = 0.0f;

void InitWachstum() {
    karottenTimer = 0.0f;
    erdbeerenTimer = 0.0f;
    baumTimer = 0.0f;
    srand((unsigned int)time(NULL));
}

PflanzenInfo* GetPflanzenInfo(int blockID) {
    if (blockID >= karotteInfo.startID &&
        blockID < karotteInfo.startID + karotteInfo.maxWachstum) {
        return &karotteInfo;
    }
    if (blockID >= ErdbaereInfo.startID &&
        blockID < ErdbaereInfo.startID + ErdbaereInfo.maxWachstum) {
        return &ErdbaereInfo;
    }
    if (blockID >= BaumInfo.startID &&
        blockID < BaumInfo.startID + BaumInfo.maxWachstum) {
        return &BaumInfo;
    }
    return nullptr;
}

void UpdateWachstum() {
    float deltaTime = GetFrameTime();

    // Karotten-Wachstum
    karottenTimer += deltaTime * karotteInfo.wachstumsFaktor;
    if (karottenTimer >= karotteInfo.basisIntervall) {
        karottenTimer = 0.0f;

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

    // Erdbeeren-Wachstum
    erdbeerenTimer += deltaTime * ErdbaereInfo.wachstumsFaktor;
    if (erdbeerenTimer >= ErdbaereInfo.basisIntervall) {
        erdbeerenTimer = 0.0f;

        for (int y = 0; y < MAP_H; y++) {
            for (int x = 0; x < MAP_W; x++) {
                int blockID = map[y][x];

                if (blockID >= ErdbaereInfo.startID &&
                    blockID < ErdbaereInfo.startID + ErdbaereInfo.maxWachstum - 1) {

                    float randomValue = (float)rand() / (float)RAND_MAX;
                    if (randomValue <= ErdbaereInfo.wachstumsChance) {
                        map[y][x] = blockID + 1;
                    }
                }
            }
        }
    }

    // Baum-Wachstum
    baumTimer += deltaTime * BaumInfo.wachstumsFaktor;
    if (baumTimer >= BaumInfo.basisIntervall) {
        baumTimer = 0.0f;

        for (int y = 0; y < MAP_H; y++) {
            for (int x = 0; x < MAP_W; x++) {
                int blockID = map[y][x];

                if (blockID >= BaumInfo.startID &&
                    blockID < BaumInfo.startID + BaumInfo.maxWachstum - 1) {

                    float randomValue = (float)rand() / (float)RAND_MAX;
                    if (randomValue <= BaumInfo.wachstumsChance) {
                        map[y][x] = blockID + 1;
                    }
                }
            }
        }
    }
}