//
// Created by leona on 09.12.2024.
//

#ifndef SHOP_H
#define SHOP_H


#include <iostream>
#include <string>
#include <vector>
#include "Player.h"


// ShopItem-Klasse definiert Artikel im Shop
class ShopItem {
public:
    std::string name;
    int price;
    int mentalHealthChange;
    int hungerChange;

    ShopItem(std::string itemName, int itemPrice, int mentalChange, int hungerChange)
        : name(itemName), price(itemPrice), mentalHealthChange(mentalChange), hungerChange(hungerChange) {}
};

// Shop-Klasse verwaltet den Einkauf
class Shop {
    std::vector<ShopItem> items;

public:
    Shop();
    void openShop(player& player);
};

#endif // SHOP_H
