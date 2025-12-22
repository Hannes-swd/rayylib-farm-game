// shop.h
#pragma once
#include <string>

extern bool shopoffen;
extern int ausgewaehltesShopItem;
extern int shopSeite; // 0 = Kaufen, 1 = Verkaufen

void openShop();
void UpdateVerkaufsItems();
void DrawShopItems();
void DrawShopScrollbar();
void HandleShopInput();
void InitShop();
