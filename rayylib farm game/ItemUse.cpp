//ItemUse.cpp

#include "raylib.h"
#include "globals.h"
#include "Textures.h"
#include <cstdlib>


void inventarMangage()
{
	float wheel = GetMouseWheelMove();
    if (wheel > 0) {
        AktuellesItem--;
        if (AktuellesItem < 1) AktuellesItem = 3; // wrap nach oben
    }
    else if (wheel < 0) {
        AktuellesItem++;
        if (AktuellesItem > 3) AktuellesItem = 1; // wrap nach unten
    }
}


