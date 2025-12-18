//Moovment.cpp
#include "raylib.h"
#include "globals.h"

void HandleMovement() {
	//oben
	if (IsKeyPressed(KEY_W)) {
		if (spielerY > 0 && tiles[map[spielerY - 1][spielerX]].begangbar) {
			spielerY--;
		}
	}
	//rechts
	if (IsKeyPressed(KEY_D)) {
		if (spielerX < 24 && tiles[map[spielerY][spielerX + 1]].begangbar) {
			spielerX++;
		}
	}
	//links
	if (IsKeyPressed(KEY_A)) {
		if (spielerX > 0 && tiles[map[spielerY][spielerX - 1]].begangbar) {
			spielerX--;
		}
	}
	//unten
	if (IsKeyPressed(KEY_S)) {
		if (spielerY < 19 && tiles[map[spielerY + 1][spielerX]].begangbar) {
			spielerY++;
		}
	}
}
	
