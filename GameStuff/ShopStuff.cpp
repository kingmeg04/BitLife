//
// Created by jbrui on 19.12.2024.
//e

#include "ShopStuff.h"

using namespace std;

void shop::openShop(player &player) {
    int selectedItem;
    int buyAmount;
    bool invalid = true;
    cout << "Welcome to " << this->sShopName << endl;
    for(int items = 0; items < this->vAvailableItems.size(); items++) {
        cout << "[" << items + 1 << "]" << this->vAvailableItems[items].sItemName << " for " << this->vAvailableItems[items].iPrice << "$" << endl;
    }
    cout << "What item do you want to purchase: ";
    cin >> selectedItem;
    cout << endl;
    while(invalid) {
        if(selectedItem == 0) {return;}
        selectedItem--;
        if(this->vAvailableItems[selectedItem].iPrice > player.balance || selectedItem < 0 || selectedItem > this->vAvailableItems.size()) {
            cout << "Invalid item selected or not affordable." << endl;
            cout << "You can try again or exit the shop by typing 0: " << endl;
            cin >> selectedItem;
        }
        else {invalid = false;}
    }

    invalid = true;
    cout << "How many times would you like to buy " << this->vAvailableItems[selectedItem].sItemName << ":" << endl;
    cin >> buyAmount;
    while(invalid) {
        if(buyAmount == 0) {return;}
        if(this->vAvailableItems[selectedItem].iPrice * buyAmount >= player.balance || this->vAvailableItems[selectedItem].iPrice * buyAmount <= 0) {
            cout << "Invalid amount selected or not affordable." << endl;
            cout << "You can try again or exit the shop by typing 0: " << endl;
            cin >> buyAmount;
        }
        else {
            invalid = false;
            for(int items = 0; items < player.vItems.size(); items++) {
                if(this->vAvailableItems[selectedItem].sItemName == player.vItems[items].first.sItemName) {
                    player.vItems[items].second += buyAmount;
                    player.balance -= this->vAvailableItems[selectedItem].iPrice * buyAmount;
                    return;
                }
            }
            player.vItems.push_back({this->vAvailableItems[selectedItem], buyAmount});
            player.balance -= this->vAvailableItems[selectedItem].iPrice * buyAmount;
        }
    }
}
