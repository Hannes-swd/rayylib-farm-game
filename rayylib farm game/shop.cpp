// shop.cpp
#include "raylib.h"
#include "globals.h"
#include "Textures.h"
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

bool shopoffen = false;
int ausgewaehltesShopItem = -1;
int shopSeite = 0; // 0 = Verkaufen, 1 = Kaufen
float shopScrollY = 0;
float maxShopScroll = 0;
bool shopKannScrollen = false;

// Shop-Item-Struktur
struct ShopItem {
    int itemID;
    int menge;
    int preis;
    string beschreibung;
    bool istVerkauf;  // true = Verkauf, false = Kauf
};

vector<ShopItem> shopItems;

string GetItemName(int id) {
    switch (id) {
    case ITEM_hacke: return "Hacke";
    case ITEM_spitzhacke: return "Spitzhacke";
    case ITEM_Stein: return "Stein";
    case ITEM_Karrotte: return "Karotte";
    case ITEM_Erdbaere: return "Erdbeere";
    case ITEM_BaumSepling: return "Baumsetzling";
    case ITEM_HolzItem: return "Holz";
    case ITEM_AxtItem: return "Axt";
    default: return "Unbekannt";
    }
}

Texture2D* GetItemTexture(int id) {
    switch (id) {
    case ITEM_hacke: return &HackeItem;
    case ITEM_spitzhacke: return &spitzhackeItem;
    case ITEM_Stein: return &steinItem;
    case ITEM_Karrotte: return &KarotteItem;
    case ITEM_Erdbaere: return &ErdbaereItem;
    case ITEM_BaumSepling: return &BaumSeplingItem;
    case ITEM_HolzItem: return &HolzItem;
    case ITEM_AxtItem: return &AxtItem;
    default: return nullptr;
    }
}

// Forward-Declarations
void DrawShopUI();
void HandleShopInput();

void InitShop() {
    // VERKAUFEN - Items die der Spieler verkaufen kann
    shopItems.push_back({ ITEM_Karrotte, 1, 5, "Karotte verkaufen", true });
    shopItems.push_back({ ITEM_Erdbaere, 1, 5, "Erdbeere verkaufen", true });
    shopItems.push_back({ ITEM_HolzItem, 1, 3, "Holz verkaufen", true });

    // KAUFEN - Items die der Spieler kaufen kann
    shopItems.push_back({ ITEM_Karrotte, 1, 10, "Karotte kaufen", false });
    shopItems.push_back({ ITEM_Erdbaere, 1, 10, "Erdbeere kaufen", false });
    shopItems.push_back({ ITEM_Stein, 5, 20, "5x Stein kaufen", false });
    shopItems.push_back({ ITEM_BaumSepling, 1, 25, "Baumsetzling kaufen", false });
}

void openShop() {
    if (shopoffen) {
        if (IsKeyPressed(KEY_E)) {
            shopoffen = false;
            ausgewaehltesShopItem = -1;
            return;
        }

        HandleShopInput();
        DrawShopUI();
    }
}

void DrawShopUI() {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    // Fenster-Größe
    float shopWidth = sw * 0.85f;
    float shopHeight = sh * 0.9f;
    float shopX = sw / 2.0f - shopWidth / 2.0f;
    float shopY = sh / 2.0f - shopHeight / 2.0f;

    // Hintergrund mit Gradient-Effekt
    DrawRectangle(shopX, shopY, shopWidth, shopHeight, Color{ 40, 40, 60, 255 });
    DrawRectangleLinesEx({ shopX, shopY, shopWidth, shopHeight }, 4, Color{ 100, 150, 200, 255 });

    // Titel
    DrawText("SHOP", shopX + 30, shopY + 25, 40, Color{ 100, 200, 255, 255 });

    // Geld anzeigen
    float geldIconSize = 24.0f;
    float geldTextX = shopX + shopWidth - 250;

    // Zeichne das Geld-Icon
    if (GeldIcon.id != 0) {
        DrawTexturePro(
            GeldIcon,
            { 0, 0, (float)GeldIcon.width, (float)GeldIcon.height },
            { geldTextX, shopY + 25, geldIconSize, geldIconSize },
            { 0, 0 }, 0, WHITE
        );
    }

    // Zeichne den Geldbetrag rechts neben dem Icon
    DrawText(
        TextFormat("%d", Geld),
        geldTextX + geldIconSize + 10, // Etwas Abstand zum Icon
        shopY + 25,
        28,
        Color{ 255, 215, 0, 255 }
    );


    // Tab-Buttons
    float tabY = shopY + 80;
    float tab1X = shopX + 30;
    float tab2X = shopX + 280;
    float tabWidth = 200;
    float tabHeight = 40;

    // Verkaufen Tab
    Color tab1Color = (shopSeite == 0) ? Color{ 80, 120, 200, 255 } : Color{ 60, 60, 80, 255 };
    DrawRectangle(tab1X, tabY, tabWidth, tabHeight, tab1Color);
    DrawRectangleLinesEx({ tab1X, tabY, tabWidth, tabHeight }, 2, Color{ 100, 150, 200, 255 });
    DrawText("VERKAUFEN", tab1X + 30, tabY + 7, 20, WHITE);

    // Kaufen Tab
    Color tab2Color = (shopSeite == 1) ? Color{ 80, 120, 200, 255 } : Color{ 60, 60, 80, 255 };
    DrawRectangle(tab2X, tabY, tabWidth, tabHeight, tab2Color);
    DrawRectangleLinesEx({ tab2X, tabY, tabWidth, tabHeight }, 2, Color{ 100, 150, 200, 255 });
    DrawText("KAUFEN", tab2X + 50, tabY + 7, 20, WHITE);

    // Content-Bereich
    float contentY = tabY + 60;
    float contentHeight = shopHeight - 160;
    float listWidth = shopWidth - 60;

    // Item-Größe
    float itemHeight = 120;
    float itemSpacing = 15;

    // Berechne Scroll-Größe
    int visibleItemCount = 0;
    for (size_t i = 0; i < shopItems.size(); i++) {
        if ((shopSeite == 0 && shopItems[i].istVerkauf) ||
            (shopSeite == 1 && !shopItems[i].istVerkauf)) {
            visibleItemCount++;
        }
    }

    float totalContentHeight = visibleItemCount * (itemHeight + itemSpacing);
    shopKannScrollen = totalContentHeight > contentHeight;
    maxShopScroll = totalContentHeight - contentHeight;
    if (maxShopScroll < 0) maxShopScroll = 0;

    // Scrolling mit Mausrad
    if (shopKannScrollen && CheckCollisionPointRec(GetMousePosition(),
        { shopX + 30, contentY, listWidth, contentHeight })) {
        float wheel = GetMouseWheelMove();
        shopScrollY -= wheel * 30;

        if (shopScrollY < 0) shopScrollY = 0;
        if (shopScrollY > maxShopScroll) shopScrollY = maxShopScroll;
    }

    // Zeichne Items
    BeginScissorMode((int)(shopX + 30), (int)contentY, (int)listWidth, (int)contentHeight);

    int itemIndex = 0;
    for (size_t i = 0; i < shopItems.size(); i++) {
        // Zeige nur Items der aktuellen Seite
        if ((shopSeite == 0 && !shopItems[i].istVerkauf) ||
            (shopSeite == 1 && shopItems[i].istVerkauf)) {
            continue;
        }

        float itemY = contentY + itemIndex * (itemHeight + itemSpacing) - shopScrollY;
        itemIndex++;

        // Prüfe, ob Item im sichtbaren Bereich
        if (itemY + itemHeight < contentY || itemY > contentY + contentHeight) {
            continue;
        }

        ShopItem& item = shopItems[i];

        // Hintergrund (mit Highlight wenn ausgewählt)
        Color bgColor = (ausgewaehltesShopItem == (int)i) ? Color{ 80, 120, 200, 255 } : Color{ 50, 50, 70, 255 };
        DrawRectangle(shopX + 30, itemY, listWidth, itemHeight, bgColor);
        DrawRectangleLinesEx({ shopX + 30, itemY, listWidth, itemHeight }, 2, Color{ 100, 150, 200, 255 });

        float padding = 15;
        float iconSize = 80;
        float leftX = shopX + 30 + padding;

        // LINKE SEITE - WAS MAN GIBT
        Texture2D* texLeft = GetItemTexture(item.itemID);
        if (texLeft && texLeft->id != 0) {
            DrawTexturePro(*texLeft,
                { 0, 0, (float)texLeft->width, (float)texLeft->height },
                { leftX, itemY + padding, iconSize, iconSize },
                { 0, 0 }, 0, WHITE);
        }

        // Menge daneben (links unten)
        DrawText(TextFormat("x%d", item.menge),
            leftX + iconSize + 10, itemY + padding + 55, 18, WHITE);

        // Item-Name (links oben)
        DrawText(GetItemName(item.itemID).c_str(),
            leftX, itemY + padding + iconSize + 5, 14, Color{ 200, 200, 200, 255 });

        // Verfügbarkeitsprüfung (links)
        if (shopSeite == 0) {  // VERKAUFEN
            int besitzMenge = GetItemCount(item.itemID);
            if (besitzMenge == 0) {
                DrawRectangle(shopX + 30, itemY, listWidth, itemHeight, Color{ 255, 0, 0, 80 });
            }
        }

        // MITTE - PFEIL
        float midX = shopX + 30 + listWidth / 2.0f;
        DrawText("=>", midX - 20, itemY + 40, 40, Color{ 100, 200, 255, 255 });

        // RECHTE SEITE - WAS MAN BEKOMMT
        float rightX = midX + 40;
        Texture2D* texRight = nullptr;
        int rightItemID = 0;
        int rightMenge = 0;

        if (shopSeite == 0) {  // VERKAUFEN - bekommt Gold
            texRight = &GeldIcon;  // Direkt die Textur verwenden
            rightMenge = item.preis;
        }
        else {  // KAUFEN - gibt Gold
            texRight = &GeldIcon;  // Direkt die Textur verwenden
            rightMenge = item.preis;
        }

        // Zeichne Gold-Icon (nutze eine Textur)
        if (texRight && texRight->id != 0) {
            DrawTexturePro(*texRight,
                { 0, 0, (float)texRight->width, (float)texRight->height },
                { rightX, itemY + padding, iconSize, iconSize },
                { 0, 0 }, 0, WHITE);
        }

        // Menge daneben (rechts unten)
        string mengeText = (shopSeite == 0) ? TextFormat("+%d", rightMenge) : TextFormat("-%d", rightMenge);
        Color mengeColor = (shopSeite == 0) ? Color{ 100, 255, 100, 255 } : Color{ 255, 100, 100, 255 };
        DrawText(mengeText.c_str(), rightX + iconSize + 10, itemY + padding + 55, 18, mengeColor);

        // Gold Status (rechts)
        if (shopSeite == 1) {  // KAUFEN
            if (Geld < item.preis) {
                DrawRectangle(shopX + 30, itemY, listWidth, itemHeight, Color{ 255, 0, 0, 80 });
            }
        }
    }

    EndScissorMode();

    // Scrollbar
    if (shopKannScrollen) {
        float scrollbarWidth = 12;
        float scrollbarX = shopX + shopWidth - 30;
        float thumbHeight = contentHeight * (contentHeight / (contentHeight + maxShopScroll));
        float thumbY = contentY + (shopScrollY / maxShopScroll) * (contentHeight - thumbHeight);

        DrawRectangle(scrollbarX, contentY, scrollbarWidth, contentHeight, Color{ 60, 60, 80, 255 });
        DrawRectangle(scrollbarX, thumbY, scrollbarWidth, thumbHeight, Color{ 100, 150, 200, 255 });
        DrawRectangleLinesEx({ scrollbarX, thumbY, scrollbarWidth, thumbHeight }, 1, Color{ 150, 200, 255, 255 });
    }

    // Steuerungshinweise unten
    DrawText("Klick: Auswahlen | ENTER: Transaktion | E: Schließen",
        shopX + 30, shopY + shopHeight - 40, 16, Color{ 150, 150, 150, 255 });
}

void HandleShopInput() {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    float shopWidth = sw * 0.85f;
    float shopHeight = sh * 0.9f;
    float shopX = sw / 2.0f - shopWidth / 2.0f;
    float shopY = sh / 2.0f - shopHeight / 2.0f;

    float tabY = shopY + 80;
    float tab1X = shopX + 30;
    float tab2X = shopX + 280;
    float tabWidth = 200;
    float tabHeight = 40;

    float contentY = tabY + 60;
    float contentHeight = shopHeight - 160;
    float listWidth = shopWidth - 60;

    float itemHeight = 120;
    float itemSpacing = 15;

    // Mausklick zum Tab wechseln
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, { tab1X, tabY, tabWidth, tabHeight })) {
            shopSeite = 0;  // Verkaufen
            ausgewaehltesShopItem = -1;
            shopScrollY = 0;
            return;
        }
        if (CheckCollisionPointRec(mouse, { tab2X, tabY, tabWidth, tabHeight })) {
            shopSeite = 1;  // Kaufen
            ausgewaehltesShopItem = -1;
            shopScrollY = 0;
            return;
        }

        // Mausklick zum Item auswählen
        if (CheckCollisionPointRec(mouse, { shopX + 30, contentY, listWidth, contentHeight })) {
            int itemIndex = 0;
            for (size_t i = 0; i < shopItems.size(); i++) {
                // Filtere nach aktueller Seite
                if ((shopSeite == 0 && !shopItems[i].istVerkauf) ||
                    (shopSeite == 1 && shopItems[i].istVerkauf)) {
                    continue;
                }

                float itemY = contentY + itemIndex * (itemHeight + itemSpacing) - shopScrollY;
                itemIndex++;

                Rectangle itemRect = { shopX + 30, itemY, listWidth, itemHeight };

                if (CheckCollisionPointRec(mouse, itemRect)) {
                    ausgewaehltesShopItem = (int)i;
                    break;
                }
            }
        }
    }

    // Enter zum Transaktion ausführen
    if (IsKeyPressed(KEY_ENTER) && ausgewaehltesShopItem >= 0 &&
        ausgewaehltesShopItem < (int)shopItems.size()) {

        ShopItem& item = shopItems[ausgewaehltesShopItem];

        if (shopSeite == 0) {  // VERKAUFEN
            int besitzMenge = GetItemCount(item.itemID);
            if (besitzMenge >= item.menge) {
                RemoveItem(item.itemID, item.menge);
                Geld += item.preis;
            }
        }
        else {  // KAUFEN
            if (Geld >= item.preis) {
                Geld -= item.preis;
                AddItem(item.itemID, item.menge);
            }
        }
    }
}