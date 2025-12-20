// MapRender.cpp
#include "raylib.h"
#include "globals.h"
#include "Moovment.h"

// Texturen als globale/statische Variablen, damit sie nicht jedes Mal geladen werden
static Texture2D grassTexture = { 0 };
static Texture2D stoneTexture = { 0 };
static Texture2D SpielerVorne = { 0 };
static Texture2D SpielerHinten = { 0 };
static Texture2D SpielerLinks = { 0 };
static Texture2D SpielerRechts = { 0 };


void LoadMapTextures() {
    // Nur einmal laden
    if (grassTexture.id == 0) {
        grassTexture = LoadTexture("resources/grass.png");
        stoneTexture = LoadTexture("resources/stone.png");
        SpielerVorne = LoadTexture("resources/spieler/Vor.png");
        SpielerHinten = LoadTexture("resources/spieler/Hinten.png");
		SpielerLinks = LoadTexture("resources/spieler/Links.png");
		SpielerRechts = LoadTexture("resources/spieler/rechts.png");

    }
}

void UnloadMapTextures() {
    UnloadTexture(grassTexture);
    UnloadTexture(stoneTexture);
    UnloadTexture(SpielerVorne);
    UnloadTexture(SpielerHinten);

    grassTexture = { 0 };
    stoneTexture = { 0 };
    SpielerVorne = { 0 };
    SpielerHinten = { 0 };
}

void DrawMap(int screenWidth, int screenHeight)
{
    // Texturen laden (nur beim ersten Aufruf)
    LoadMapTextures();

    // Map einstellungen
    int tileWidth = screenWidth / 25;
    int tileHeight = screenHeight / 20;
    int tileSize = (tileWidth < tileHeight) ? tileWidth : tileHeight;

    int offsetX = (screenWidth - (25 * tileSize)) / 2;
    int offsetY = (screenHeight - (20 * tileSize)) / 2;

    // Map zeichnen
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 25; x++)
        {
            int posX = offsetX + (x * tileSize);
            int posY = offsetY + (y * tileSize);

            if (map[y][x] == 0)
            {
                // Grass zeichnen
                DrawTexturePro(
                    grassTexture,
                    Rectangle{ 0.0f, 0.0f, (float)grassTexture.width, (float)grassTexture.height },
                    Rectangle{ (float)posX, (float)posY, (float)tileSize, (float)tileSize },
                    Vector2{ 0.0f, 0.0f },
                    0.0f,
                    WHITE
                );
            }
            else if (map[y][x] == 1)
            {
                // sein zeichnen
                DrawTexturePro(
                    stoneTexture,
                    Rectangle{ 0.0f, 0.0f, (float)stoneTexture.width, (float)stoneTexture.height },
                    Rectangle{ (float)posX, (float)posY, (float)tileSize, (float)tileSize },
                    Vector2{ 0.0f, 0.0f },
                    0.0f,
                    WHITE
                );
            }
        }
    }

    /*
        Alles Vom spieler
    */
    float playerPosX = offsetX + (spielerX * tileSize);
    float playerPosY = offsetY + (spielerY * tileSize);
    
    //hitbox
    //DrawRectangleLines(playerPosX, playerPosY, tileSize, tileSize, RED);

    if (richtung == 0) {
        DrawTexturePro(
            SpielerVorne,
            Rectangle{ 0.0f, 0.0f, (float)SpielerVorne.width, (float)SpielerVorne.height },
            Rectangle{ playerPosX, playerPosY, (float)tileSize, (float)tileSize },
            Vector2{ 0.0f, 0.0f },
            0.0f,
            WHITE
        );
    }
    else if (richtung == 1) {
        DrawTexturePro(
            SpielerHinten,
            Rectangle{ 0.0f, 0.0f, (float)SpielerHinten.width, (float)SpielerHinten.height },
            Rectangle{ playerPosX, playerPosY, (float)tileSize, (float)tileSize },
            Vector2{ 0.0f, 0.0f },
            0.0f,
            WHITE
        );
    }
    else if (richtung == 2) {
        DrawTexturePro(
            SpielerLinks,
            Rectangle{ 0.0f, 0.0f, (float)SpielerLinks.width, (float)SpielerLinks.height },
            Rectangle{ playerPosX, playerPosY, (float)tileSize, (float)tileSize },
            Vector2{ 0.0f, 0.0f },
            0.0f,
            WHITE
        );
    }
    else if (richtung == 3) {
        DrawTexturePro(
            SpielerRechts,
            Rectangle{ 0.0f, 0.0f, (float)SpielerRechts.width, (float)SpielerRechts.height },
            Rectangle{ playerPosX, playerPosY, (float)tileSize, (float)tileSize },
            Vector2{ 0.0f, 0.0f },
            0.0f,
            WHITE
        );
	}
    else if (richtung == 4) {
        DrawTexturePro(
            SpielerVorne,
            Rectangle{ 0.0f, 0.0f, (float)SpielerVorne.width, (float)SpielerVorne.height },
            Rectangle{ playerPosX, playerPosY, (float)tileSize, (float)tileSize },
            Vector2{ 0.0f, 0.0f },
            0.0f,
            WHITE
        );
	}


}