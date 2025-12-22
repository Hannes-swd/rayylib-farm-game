#include "globals.h"
#include <cstdlib>
#include <ctime>

int map[20][25] = {
    {0} 
};

// Spielerinformationen
int spielerX = 1, spielerY = 1;
int spielerLeben = 100;
int Geld = 0;
int tag = 1;
int richtung = 0; // 0 = vorne, 1 = hinten, 2 = links, 3 = rechts

void InitMap() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 25; x++) {
            // Gras
            map[y][x] = 0;

            
            // 5% baum
            if (std::rand() % 100 < 5) {
                map[y][x] = 10;
            }

            if (x == 0 || x == 24 || y == 0 || y == 19) {
                map[y][x] = 1;
            }
        }
    }

    map[spielerY][spielerX] = 0; 
    map[1][2] = 11;
}

// Blöcke
Tile tiles[TILE_COUNT] = {
    { true,  false, false, false}, // 0: Grass
    { false, false, false, false}, // 1: Stone
    { true,  true,  false, false},  // 2: Dirt
    { true, false, false, true }, // 3: karotte
    { true, false, false, false }, // 4: Erdbere
    { false, false, false, false},  // 5: Baum
    { false, false, false, false} //6: Shop
};

// Mausposition
int mausX = 0;
int mausY = 0;

int AktuellesItem = 0;
int AktuellerSlot = 1;

bool inventaroffen = false;

int inventar[INVENTAR_SLOTS] = { 0 };
int inventarMenge[INVENTAR_SLOTS] = { 0 };

int dragSlot = -1;
bool isDragging = false;

int GetMaxStack(int id) {
    switch (id) {
    case ITEM_hacke: return 1;
    case ITEM_spitzhacke: return 1;
    case ITEM_AxtItem: return 1;
    case ITEM_Stein: return 99;
    case ITEM_HolzItem: return 99;
    

    //Pflanzen
	case ITEM_Karrotte: return 99;
    case ITEM_Erdbaere: return 99;
	case ITEM_BaumSepling: return 99;
    
    default: return 1;
    }
}

int GetItemCount(int id) {
    int total = 0;
    for (int i = 0; i < INVENTAR_SLOTS; i++) {
        if (inventar[i] == id) {
            total += inventarMenge[i];
        }
    }
    return total;
}

void AddItem(int id, int amount) {
    for (int i = 0; i < INVENTAR_SLOTS && amount > 0; i++) {
        if (inventar[i] == id) {
            int maxStack = GetMaxStack(id);
            int space = maxStack - inventarMenge[i];

            if (space > 0) {
                int toAdd = (amount < space) ? amount : space;
                inventarMenge[i] += toAdd;
                amount -= toAdd;
            }
        }
    }

    bool itemExists = false;
    for (int i = 0; i < INVENTAR_SLOTS; i++) {
        if (inventar[i] == id) {
            itemExists = true;
            break;
        }
    }

    if (!itemExists) {
        int hotbarStart = INVENTAR_SLOTS - 5;

        for (int i = hotbarStart; i < INVENTAR_SLOTS && amount > 0; i++) {
            if (inventar[i] == 0) {
                inventar[i] = id;
                int maxStack = GetMaxStack(id);
                int toAdd = (amount < maxStack) ? amount : maxStack;
                inventarMenge[i] = toAdd;
                amount -= toAdd;
            }
        }

        for (int i = 0; i < hotbarStart && amount > 0; i++) {
            if (inventar[i] == 0) {
                inventar[i] = id;
                int maxStack = GetMaxStack(id);
                int toAdd = (amount < maxStack) ? amount : maxStack;
                inventarMenge[i] = toAdd;
                amount -= toAdd;
            }
        }
    }
    else {
        for (int i = 0; i < INVENTAR_SLOTS && amount > 0; i++) {
            if (inventar[i] == 0) {
                inventar[i] = id;
                int maxStack = GetMaxStack(id);
                int toAdd = (amount < maxStack) ? amount : maxStack;
                inventarMenge[i] = toAdd;
                amount -= toAdd;
            }
        }
    }
}
// Item entfernen
void RemoveItem(int id, int amount) {

    for (int i = INVENTAR_SLOTS - 1; i >= 0 && amount > 0; i--) {
        if (inventar[i] == id) {
            if (inventarMenge[i] >= amount) {
                inventarMenge[i] -= amount;
                amount = 0;
                if (inventarMenge[i] == 0) {
                    inventar[i] = 0;
                }
            }
            else {
                amount -= inventarMenge[i];
                inventar[i] = 0;
                inventarMenge[i] = 0;
            }
        }
    }
}

// Inventar
void InitInventar() {
    
    for (int i = 0; i < INVENTAR_SLOTS; i++) {
        inventar[i] = 0;
        inventarMenge[i] = 0;
    }
}