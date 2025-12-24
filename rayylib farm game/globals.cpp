#include "globals.h"
#include <cstdlib>
#include <ctime>

int map[20][25] = {
    {0} 
};

// Spielerinformationen
int spielerX = 1, spielerY = 1;
int spielerLeben = 100;
int Geld = 100;
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
    map[4][4] = 13;
    map[5][4] = 14;
}

// Blöcke
Tile tiles[15] = {  // Erweitere auf 14, da du Block-IDs bis 13 hast
    // 0: Grass
    { true,  false, false, false},
    // 1: Stone
    { false, false, false, false},
    // 2: Dirt
    { true,  true,  false, false},
    // 3: Karotte1 (erstes Stadium)
    { true, false, false, true },
    // 4: Karotte2 (zweites Stadium)
    { true, false, false, false },
    // 5: Karotte3 (drittes Stadium)
    { true, false, false, false },
    // 6: Erdbere1 (erstes Stadium)
    { true, false, false, false },
    // 7: Erdbere2 (zweites Stadium)
    { false, false, false, false },
    // 8: Erdbere3 (drittes Stadium)
    { false, false, false, false },
    // 9: Baum2 (zweites Stadium)
    { false, false, false, false },
    // 10: Baum1 (erstes Stadium)
    { false, false, false, false },
    // 11: Shop
    { false, false, false, false },
    // 12: tiefe Erde
    { false, false, false, false },
    // 13: Wasser
    { true, false, false, false },
    // 14: marmeladenTopf
    { false, false, false, false }
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
    case ITEM_Schaufel: return 1;
    case ITEM_Stein: return 99;
    case ITEM_HolzItem: return 99;
    case ITEM_dirt: return 99;
    
    

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


constexpr int MAP_W = 25;
constexpr int MAP_H = 20;

bool IsNextToWater(int x, int y) {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < MAP_W && ny >= 0 && ny < MAP_H) {
            if (map[ny][nx] == 13) { 
                return true;
            }
        }
    }
    return false;
}