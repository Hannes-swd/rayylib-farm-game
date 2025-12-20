//ItemUse.cpp

#include "raylib.h"
#include "globals.h"
#include "Textures.h"

void inventarMangage()
{
    if (IsKeyPressed(KEY_T)) {
        if (AktuellesItem == 1) {
            AktuellesItem = 2;
        }
        else if (AktuellesItem == 2) {
            AktuellesItem = 3;
		}
        else if (AktuellesItem == 3)
        {
            AktuellesItem = 1;
        }
    }
}