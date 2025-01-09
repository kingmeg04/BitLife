//
// Created by jbrui on 19.12.2024.
//

#include "ShopStuff.h"

using namespace std;

void shop::openShop(player& player) {
    int selectedItem;
    int buyAmount;

    cout << "Welcome to " << sShopName << "!\n";
    cout << "Available items:\n";
    for (int i = 0; i < vAvailableItems.size(); i++) {
        cout << "[" << i + 1 << "] " << vAvailableItems[i].sItemName << " - " << vAvailableItems[i].iPrice << "$" << endl;
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
            int items = checkForItem(player, vAvailableItems[selectedItem].sItemName);
            if (items >= 0) {
                player.vItems[items].second += buyAmount;
                player.balance -= this->vAvailableItems[selectedItem].iPrice * buyAmount;
                cout << "You now own " << player.vItems[items].second;
            }



            player.vItems.push_back({this->vAvailableItems[selectedItem], buyAmount});
            player.balance -= this->vAvailableItems[selectedItem].iPrice * buyAmount;
            cout << " " << vAvailableItems[selectedItem].sItemName << endl;
            cout << "Your balance is now " << player.balance << endl;
            return;
        }
    }
}
//
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

    cout << "You received " << sellAmount * player.vItems[selectedItem].first.iPrice << "$" << endl;

}

int checkForItem(player thePlayer, std::string itemName) {
    for (int i = 0; i < thePlayer.vItems.size(); i++) {
        if (thePlayer.vItems[i].first.sItemName == itemName) {
            return i;
        }
    }
    return -1;
}

int checkForItem(vector<item> itemList, std::string itemName) {
    for (int i = 0; i < itemList.size(); i++) {
        if (itemList[i].sItemName == itemName) {
            return i;
        }
    }
    return -1;

}
