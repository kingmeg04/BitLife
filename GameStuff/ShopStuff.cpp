//
// Created by jbrui on 19.12.2024.
//

#include "ShopStuff.h"
#include <iostream>

using namespace std;

void shop::openShop(player& player) {
    cout << "Welcome to " << sShopName << "!\n";
    cout << "Available items:\n";
    for (int i = 0; i < vAvailableItems.size(); i++) {
        cout << i + 1 << ". " << vAvailableItems[i].sItemName << " - $" << vAvailableItems[i].iPrice << "\n";
    }
    cout << "Enter the number of the item you want to buy: ";
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= vAvailableItems.size()) {
        item selectedItem = vAvailableItems[choice - 1];
        if (player.balance >= selectedItem.iPrice) {
            player.balance -= selectedItem.iPrice;
            player.vItems.emplace_back(selectedItem, 1);
            cout << "You bought " << selectedItem.sItemName << "!\n";
        } else {
            cout << "Not enough money!\n";
        }
    } else {
        cout << "Invalid choice!\n";
    }
}
