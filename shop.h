//
// Created by leona on 09.12.2024.
//

#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ShopItem-Klasse definiert Artikel im Shop
class ShopItem {
public:
    string name;
    int price;
    int mentalHealthChange;
    int hungerChange;

    ShopItem(string itemName, int itemPrice, int mentalChange, int hungerChange)
        : name(itemName), price(itemPrice), mentalHealthChange(mentalChange), hungerChange(hungerChange) {}
};

// Shop-Klasse verwaltet den Einkauf
class Shop {
    vector<ShopItem> items;

public:
    Shop();
    void openShop(int& balance, int& hunger, int& mentalHealth);
};

#endif // SHOP_H
