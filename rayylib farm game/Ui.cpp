//Ui.cpp

#include "raylib.h"
#include "globals.h"
#include "Textures.h"

void DrawUI()
{
	//leben anzeigen
	DrawTexturePro(
		HerzIcon,
		{ 0,0,(float)HerzIcon.width,(float)HerzIcon.height },
		{ 10.0f,10.0f,64.0f,64.0f },
		{ 0,0 },
		0,
		WHITE
	);
	DrawText(TextFormat("%d", spielerLeben), 80, 30, 50, BLACK);

	//geld anzeigen
	DrawTexturePro(
		GeldIcon,
		{ 0,0,(float)GeldIcon.width,(float)GeldIcon.height },
		{ 10.0f,80.0f,64.0f,64.0f },
		{ 0,0 },
		0,
		WHITE
	);
	DrawText(TextFormat("%d", Geld), 80, 100, 50, BLACK);
	
}

