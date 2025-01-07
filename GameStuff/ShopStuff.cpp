//
// Created by jbrui on 19.12.2024.
//

#include "ShopStuff.h"

using namespace std;

void shop::openShop(player &player) {
    int selectedItem;
    int buyAmount;


    cout << "Welcome to " << this->sShopName << endl;
    for(int items = 0; items < this->vAvailableItems.size(); items++) {
        cout << "[" << items + 1 << "]" << this->vAvailableItems[items].sItemName << " for " << this->vAvailableItems[items].iPrice << "$" << endl;
    }

    cout << "What item do you want to purchase: ";
    cin >> selectedItem;
    cout << endl;

    while(true) {
        if(selectedItem == 0) {return;}
        selectedItem--;
        if(this->vAvailableItems[selectedItem].iPrice > player.balance || selectedItem < 0 || selectedItem > this->vAvailableItems.size()) {
            cout << "Invalid item selected or not affordable." << endl;
            cout << "You can try again or exit the shop by typing 0: " << endl;
            cin >> selectedItem;

        }
        else {break;}
    }

    cout << "How many times would you like to buy " << this->vAvailableItems[selectedItem].sItemName << ":" << endl;
    cin >> buyAmount;
    while(true) {
        if(buyAmount == 0) {return;}
        if(this->vAvailableItems[selectedItem].iPrice * buyAmount >= player.balance || this->vAvailableItems[selectedItem].iPrice * buyAmount <= 0) {
            cout << "Invalid amount selected or not affordable." << endl;
            cout << "You can try again or exit the shop by typing 0: " << endl;
            cin >> buyAmount;
        }
        else {
            for(int items = 0; items < player.vItems.size(); items++) {
                if(this->vAvailableItems[selectedItem].sItemName == player.vItems[items].first.sItemName) {
                    player.vItems[items].second += buyAmount;
                    player.balance -= this->vAvailableItems[selectedItem].iPrice * buyAmount;
                    cout << "You now own " << player.vItems[items].second;
                    break;
                }
            }
            player.vItems.push_back({this->vAvailableItems[selectedItem], buyAmount});
            player.balance -= this->vAvailableItems[selectedItem].iPrice * buyAmount;
            cout << " " << vAvailableItems[selectedItem].sItemName << endl;
            cout << "Your balance is now " << player.balance << endl;
            return;
        }
    }
}

void shop::sellItem(player &player) {
    int sellAmount;
    int selectedItem;
    bool invalid = true;

    cout << "Your inventory: " << endl;
    for (int i = 0; i < player.vItems.size(); i++) {
        cout << "[" << i + 1 << "] " << player.vItems[i].first.sItemName << " " << player.vItems[i].second << endl;
    }

    cout << "What item would you like to sell: ";
    cin >> selectedItem;
    cout << endl;

    while (true) {
        if (selectedItem == 0) {
            return;
        }

        selectedItem--;

        if (selectedItem >= player.vItems.size()) {
            cout << "Invalid item selection, try again or type 0 to exit: ";
            cin >> selectedItem;
            cout << endl;
        }
        else{break;}
    }

    cout << "How many do you want to sell: ";
    cin >> sellAmount;
    cout << endl;

    while (true) {
        if(sellAmount == 0) {
            return;
        }

        if (sellAmount > player.vItems[selectedItem].second) {
            cout << "Invalid amount of " << player.vItems[selectedItem].first.sItemName << " to sell, try again or type 0 to exit:";
            cin >> sellAmount;
            cout << endl;
        }
        else{break;}
    }

    for (int item = 0; item < this->vAvailableItems.size(); item++) {
        if (this->vAvailableItems[item].sItemName == player.vItems[selectedItem].first.sItemName) {
            cout << "You received " << sellAmount * player.vItems[selectedItem].first.iPrice << "$" << endl;

            return;
        }
    }
}
