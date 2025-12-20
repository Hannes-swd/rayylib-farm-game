#include "raylib.h"
#include "globals.h"
#include "Textures.h"
#include <cstdlib>

void inventarMangage()
{
    if (inventaroffen) return;

    float wheel = GetMouseWheelMove();
    if (wheel > 0) {
        AktuellerSlot++;
        if (AktuellerSlot > 5) AktuellerSlot = 1;
    }
    else if (wheel < 0) {
        AktuellerSlot--;
        if (AktuellerSlot < 1) AktuellerSlot = 5;
    }

    
    int hotbarIndex = INVENTAR_SLOTS - 5 + (AktuellerSlot - 1);

    if (hotbarIndex >= 0 && hotbarIndex < INVENTAR_SLOTS) {
        AktuellesItem = inventar[hotbarIndex];
    }
    else {
        AktuellesItem = 0;
    }
}