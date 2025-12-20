#include "raylib.h"
#include "globals.h"
#include "Textures.h"
#include <cstdlib>

void openinventar()
{
    if (IsKeyPressed(KEY_E)) {
        inventaroffen = !inventaroffen;
    }

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    const int cols = INVENTAR_COLS;
    const int rows = INVENTAR_ROWS;

    float invHeight = sh * 0.6f;
    float padding = invHeight * 0.08f;
    float slotSize = (invHeight - padding * 2) / rows;
    float slotSpacing = slotSize * 0.15f;
    float hotbarGap = slotSize * 0.4f;

    float slotsWidth = cols * slotSize + (cols - 1) * slotSpacing;
    float slotsHeight = rows * slotSize + (rows - 1) * slotSpacing + hotbarGap;
    float invWidth = slotsWidth + padding * 2;
    invHeight = slotsHeight + padding * 2;

    float invX = sw / 2.0f - invWidth / 2.0f;
    float invY = sh / 2.0f - invHeight / 2.0f;

    // Hotbar oder Inventar?
    if (inventaroffen) {
        // Hintergrund
        DrawRectangle(invX, invY, invWidth, invHeight, LIGHTGRAY);
        DrawRectangleLinesEx({ invX, invY, invWidth, invHeight }, 4, DARKGRAY);

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                int slotIndex = y * cols + x;
                float extraGap = (y == rows - 1) ? hotbarGap : 0;
                float sx = invX + padding + x * (slotSize + slotSpacing);
                float sy = invY + padding + y * (slotSize + slotSpacing) + extraGap;

                // Slot-Hintergrund
                DrawTexturePro(
                    InventarSlot,
                    { 0,0,(float)InventarSlot.width,(float)InventarSlot.height },
                    { sx, sy, slotSize, slotSize },
                    { 0,0 }, 0, WHITE
                );

                // Item zeichnen
                int itemID = inventar[slotIndex];
                if (itemID > 0) {
                    Texture2D itemTex = { 0 };
                    switch (itemID) {
                    case ITEM_hacke: itemTex = HackeItem; break;
                    case ITEM_spitzhacke: itemTex = spitzhackeItem; break;
                    case ITEM_Stein: itemTex = steinItem; break;
					case ITEM_Karrotte: itemTex = KarotteItem; break;
                    }
                    DrawTexturePro(itemTex,
                        { 0,0,(float)itemTex.width,(float)itemTex.height },
                        { sx,sy,slotSize,slotSize },
                        { 0,0 }, 0, WHITE);

                    // Menge anzeigen
                    if (inventarMenge[slotIndex] > 1) {
                        // Hintergrund für bessere Lesbarkeit
                        DrawRectangle(sx + slotSize - 25, sy + slotSize - 25, 25, 25, Fade(WHITE, 0.7f));

                        const char* countText = TextFormat("%d", inventarMenge[slotIndex]);
                        int textWidth = MeasureText(countText, 20);
                        DrawText(countText,
                            sx + slotSize - textWidth - 5,
                            sy + slotSize - 22,
                            20, BLACK);
                    }
                }

                // Drag & Drop 
                Vector2 mouse = GetMousePosition();
                Rectangle slotRect = { sx, sy, slotSize, slotSize };

                if (CheckCollisionPointRec(mouse, slotRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (inventar[slotIndex] > 0) {
                        dragSlot = slotIndex;
                        isDragging = true;
                    }
                }

                // Drop-Logik
                if (isDragging && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (CheckCollisionPointRec(mouse, slotRect) && dragSlot >= 0 && dragSlot != slotIndex) {
                        // Items tauschen
                        int tmpID = inventar[slotIndex];
                        int tmpAmount = inventarMenge[slotIndex];

                        inventar[slotIndex] = inventar[dragSlot];
                        inventarMenge[slotIndex] = inventarMenge[dragSlot];

                        inventar[dragSlot] = tmpID;
                        inventarMenge[dragSlot] = tmpAmount;

                        dragSlot = -1;
                        isDragging = false;
                    }
                }
            }
        }

        
        if (isDragging && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            Rectangle invRect = { invX, invY, invWidth, invHeight };
            Vector2 mouse = GetMousePosition();

            if (!CheckCollisionPointRec(mouse, invRect)) {
                dragSlot = -1;
                isDragging = false;
            }
        }

        // Ziehen 
        if (isDragging && dragSlot >= 0) {
            int itemID = inventar[dragSlot];
            if (itemID > 0) {
                Texture2D itemTex = { 0 };
                switch (itemID) {
                case ITEM_hacke: itemTex = HackeItem; break;
                case ITEM_spitzhacke: itemTex = spitzhackeItem; break;
                case ITEM_Stein: itemTex = steinItem; break;
				case ITEM_Karrotte: itemTex = KarotteItem; break;
                }
                Vector2 mouse = GetMousePosition();
                DrawTexturePro(itemTex,
                    { 0,0,(float)itemTex.width,(float)itemTex.height },
                    { mouse.x - slotSize / 2, mouse.y - slotSize / 2, slotSize, slotSize },
                    { 0,0 }, 0, WHITE);

                if (inventarMenge[dragSlot] > 1) {
                    DrawText(TextFormat("%d", inventarMenge[dragSlot]),
                        mouse.x + 10,
                        mouse.y + 10,
                        20, BLACK);
                }
            }
        }
    }
    else {
        // Hotbar
        const int sidebarSlots = 5;
        float paddingX = 20.0f;
        float paddingY = 20.0f;
        float slotSize = GetScreenHeight() * 0.08f;
        float spacing = slotSize * 0.1f;

        // HotbarSlots berechnen 
        int hotbarStartIndex = INVENTAR_SLOTS - sidebarSlots;

        for (int i = 0; i < sidebarSlots; i++) {
            int slotIndex = hotbarStartIndex + i;
            float sx = paddingX;
            float sy = GetScreenHeight() - paddingY - slotSize - i * (slotSize + spacing);

            // Aktuellen Slot markieren
            bool isCurrentSlot = (AktuellerSlot == i + 1);

            DrawTexturePro(
                isCurrentSlot ? AusgewaelterSlot : InventarSlot,
                { 0,0,(float)AusgewaelterSlot.width,(float)AusgewaelterSlot.height },
                { sx,sy,slotSize,slotSize },
                { 0,0 }, 0, WHITE
            );

            int itemID = inventar[slotIndex];
            if (itemID > 0) {
                Texture2D itemTex = { 0 };
                switch (itemID) {
                case ITEM_hacke: itemTex = HackeItem; break;
                case ITEM_spitzhacke: itemTex = spitzhackeItem; break;
                case ITEM_Stein: itemTex = steinItem; break;
				case ITEM_Karrotte: itemTex = KarotteItem; break;
                }
                DrawTexturePro(itemTex,
                    { 0,0,(float)itemTex.width,(float)itemTex.height },
                    { sx,sy,slotSize,slotSize },
                    { 0,0 }, 0, WHITE);

                // Menge anzeigen
                if (inventarMenge[slotIndex] > 1) {

                    DrawRectangle(sx + slotSize - 25, sy + slotSize - 25, 25, 25, Fade(WHITE, 0.7f));

                    const char* countText = TextFormat("%d", inventarMenge[slotIndex]);
                    int textWidth = MeasureText(countText, 20);
                    DrawText(countText,
                        sx + slotSize - textWidth - 5,
                        sy + slotSize - 22,
                        20, BLACK);
                }
            }
        }
    }
}