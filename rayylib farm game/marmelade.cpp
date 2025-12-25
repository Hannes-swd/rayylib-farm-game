//marmelade.cpp
#include "raylib.h"
#include "globals.h"
#include "Textures.h"
#include <string>
#include <cstdlib>


void marmelade(int id, int anzahl, int x, int y) {
	
	RemoveItem(id, 1);
	
	MarmeladeMachen = false;
	
	DrawTexturePro(
		ausrufezeichen,
		{ 0, 0, (float)ausrufezeichen.width, (float)ausrufezeichen.height },
		{ (float)y,(float)x + 25, 50, 50},
		{ 0, 0 }, 0, WHITE
	);

}