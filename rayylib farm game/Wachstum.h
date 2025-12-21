// Wachstum.h
#pragma once

#include "raylib.h"

#define MAP_W 25
#define MAP_H 20

struct PflanzenInfo {
    int startID;
    int maxWachstum;
    float wachstumsChance;
    int produktCount;
    float basisIntervall;
    float wachstumsFaktor;
    const char* name;
};

extern PflanzenInfo karotteInfo;
extern PflanzenInfo ErdbaereInfo;
extern PflanzenInfo BaumInfo;

// Separate Timer für jede Pflanzenart
extern float karottenTimer;
extern float erdbeerenTimer;
extern float baumTimer;

void InitWachstum();
void UpdateWachstum();
PflanzenInfo* GetPflanzenInfo(int blockID);