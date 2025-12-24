//Textures.cpp
#include "Textures.h"

// Map
Texture2D grassTexture = { 0 };
Texture2D stoneTexture = { 0 };
Texture2D dirtTexture = { 0 };
Texture2D shopTexture = { 0 };
Texture2D tiefeErde = { 0 };
Texture2D Wasser = { 0 };


//pflanzen
Texture2D Karotte1Texture = { 0 };
Texture2D Karotte2Texture = { 0 };
Texture2D Karotte3Texture = { 0 };

Texture2D Erdbere1Texture = { 0 };
Texture2D Erdbere2Texture = { 0 };
Texture2D Erdbere3Texture = { 0 };

Texture2D Baum1Texture = { 0 };
Texture2D Baum2Texture = { 0 };

// Spieler
Texture2D SpielerVorne = { 0 };
Texture2D SpielerHinten = { 0 };
Texture2D SpielerLinks = { 0 };
Texture2D SpielerRechts = { 0 };

// UI
Texture2D GridHover = { 0 };
Texture2D InventarSlot = { 0 };
Texture2D HerzIcon = { 0 };
Texture2D GeldIcon = { 0 };
Texture2D AusgewaelterSlot = { 0 };

//items
Texture2D HackeItem = { 0 };
Texture2D spitzhackeItem = { 0 };
Texture2D steinItem = { 0 };
Texture2D KarotteItem = { 0 };
Texture2D ErdbaereItem = { 0 };
Texture2D BaumSeplingItem = { 0 };
Texture2D HolzItem = { 0 };
Texture2D AxtItem = { 0 };
Texture2D Schaufel = { 0 };
Texture2D dirtItem = { 0 };

void LoadAllTextures()
{
    if (grassTexture.id != 0) return;

	// Map
    grassTexture = LoadTexture("resources/grass.png");
    stoneTexture = LoadTexture("resources/stone.png");
	dirtTexture = LoadTexture("resources/dirt.png");
	shopTexture = LoadTexture("resources/shop.png");
	tiefeErde = LoadTexture("resources/tiefeErde.png");
	Wasser = LoadTexture("resources/Wasser.png");

	//pflanzen
	Karotte1Texture = LoadTexture("resources/pflanzen/Karrotte1.png");
	Karotte2Texture = LoadTexture("resources/pflanzen/Karrotte2.png");
	Karotte3Texture = LoadTexture("resources/pflanzen/Karrotte3.png");
	Erdbere1Texture = LoadTexture("resources/pflanzen/Erdbere1.png");
	Erdbere2Texture = LoadTexture("resources/pflanzen/Erdbere2.png");
	Erdbere3Texture = LoadTexture("resources/pflanzen/Erdbere3.png");
	Baum1Texture = LoadTexture("resources/pflanzen/Baum1.png");
	Baum2Texture = LoadTexture("resources/pflanzen/Baum2.png");

	// Spieler
    SpielerVorne = LoadTexture("resources/spieler/Vor.png");
    SpielerHinten = LoadTexture("resources/spieler/Hinten.png");
    SpielerLinks = LoadTexture("resources/spieler/Links.png");
    SpielerRechts = LoadTexture("resources/spieler/rechts.png");

	// UI
    GridHover = LoadTexture("resources/Ui/CurserRahmen.png");
	InventarSlot = LoadTexture("resources/Ui/InventarSlot.png");
	HerzIcon = LoadTexture("resources/Ui/Hart.png");
	GeldIcon = LoadTexture("resources/Ui/Geld.png");
	AusgewaelterSlot = LoadTexture("resources/Ui/AusgewälterSlot.png");

	//items
	HackeItem = LoadTexture("resources/items/hacke.png");
	spitzhackeItem = LoadTexture("resources/items/spitzhacke.png");
	steinItem = LoadTexture("resources/items/stein.png");
	KarotteItem = LoadTexture("resources/items/KarotteItem.png");
	ErdbaereItem = LoadTexture("resources/items/ErdbaereItem.png");
	BaumSeplingItem = LoadTexture("resources/items/BaumSeplingItem.png");
	HolzItem = LoadTexture("resources/items/HolzItem.png");
	AxtItem = LoadTexture("resources/items/AxtItem.png");
	Schaufel = LoadTexture("resources/items/Schaufel.png");
	dirtItem = LoadTexture("resources/items/dirtItem.png");
}

void UnloadAllTextures()
{
    UnloadTexture(grassTexture);
    UnloadTexture(stoneTexture);
	UnloadTexture(dirtTexture);
	UnloadTexture(shopTexture);
	UnloadTexture(tiefeErde);
	UnloadTexture(Wasser);
	

	UnloadTexture(Karotte1Texture);
	UnloadTexture(Karotte2Texture);
	UnloadTexture(Karotte3Texture);
	UnloadTexture(Erdbere1Texture);
	UnloadTexture(Erdbere2Texture);
	UnloadTexture(Erdbere3Texture);
	UnloadTexture(Baum1Texture);
	UnloadTexture(Baum1Texture);

    UnloadTexture(SpielerVorne);
    UnloadTexture(SpielerHinten);
    UnloadTexture(SpielerLinks);
    UnloadTexture(SpielerRechts);

    UnloadTexture(GridHover);
	UnloadTexture(InventarSlot);
	UnloadTexture(HerzIcon);
	UnloadTexture(GeldIcon);
	UnloadTexture(AusgewaelterSlot);

	UnloadTexture(HackeItem);
	UnloadTexture(spitzhackeItem);
	UnloadTexture(steinItem);
	UnloadTexture(KarotteItem);
	UnloadTexture(ErdbaereItem);
	UnloadTexture(BaumSeplingItem);
	UnloadTexture(HolzItem);
	UnloadTexture(AxtItem);
	UnloadTexture(dirtItem);
}
