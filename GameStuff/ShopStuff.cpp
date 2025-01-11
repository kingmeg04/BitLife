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
        cout << "[" << i + 1 << "] " << vAvailableItems[i]->sItemName << " - " << vAvailableItems[i]->iPrice << "$" << endl;
    }

    cout << "What item do you want to purchase: ";
    cin >> selectedItem;
    cout << endl;

    while(true) {
        if(selectedItem == 0) {return;}
        selectedItem--;
        if(this->vAvailableItems[selectedItem]->iPrice > player.balance || selectedItem < 0 || selectedItem > this->vAvailableItems.size()) {
            cout << "Invalid item selected or not affordable." << endl;
            cout << "You can try again or exit the shop by typing 0: " << endl;
            cin >> selectedItem;

        }
        else {break;}
    }

    cout << "How many times would you like to buy " << this->vAvailableItems[selectedItem]->sItemName << ":" << endl;
    cin >> buyAmount;
    while(true) {
        if(buyAmount == 0) {return;}
        if(this->vAvailableItems[selectedItem]->iPrice * buyAmount >= player.balance || this->vAvailableItems[selectedItem]->iPrice * buyAmount <= 0) {
            cout << "Invalid amount selected or not affordable." << endl;
            cout << "You can try again or exit the shop by typing 0: " << endl;
            cin >> buyAmount;
        }
        else {
            int items = checkForItem(player, vAvailableItems[selectedItem]->sItemName);
            if (items >= 0) {
                player.vItems[items].second += buyAmount;
                player.balance -= this->vAvailableItems[selectedItem]->iPrice * buyAmount;
                cout << "You now own " << player.vItems[items].second;
            }



            player.vItems.push_back({this->vAvailableItems[selectedItem], buyAmount});
            player.balance -= this->vAvailableItems[selectedItem]->iPrice * buyAmount;
            cout << " " << vAvailableItems[selectedItem]->sItemName << endl;
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
        cout << "[" << i + 1 << "] " << player.vItems[i].first->sItemName << " " << player.vItems[i].second << endl;
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
            cout << "Invalid amount of " << player.vItems[selectedItem].first->sItemName << " to sell, try again or type 0 to exit:";
            cin >> sellAmount;
            cout << endl;
        }
        else{break;}
    }

    cout << "You received " << sellAmount * player.vItems[selectedItem].first->iPrice << "$" << endl;

}

int checkForItem(player thePlayer, std::string itemName) {
    for (int i = 0; i < thePlayer.vItems.size(); i++) {
        if (thePlayer.vItems[i].first->sItemName == itemName) {
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


/**
 * 
 * @param posCases 1 = convenience store | 2 = car dealership | 3 = hardware store | 4 = pawn shop
 * @return 
 */
shop generateShop(vector<unsigned short> posCases) {
    shop generatedShop = {"", {}};
    unsigned short itemsInShop;



    int switchVar;
    vector<shared_ptr<item>> possibleItems = {
        make_shared<consumable>(2, 0, "small water", static_cast<short>(random(1, 3))), // drinks
        make_shared<consumable>(5, 0, "large water", static_cast<short>(random(2, 5))),
        make_shared<consumable>(2, 0, "energy drink", static_cast<short>(random(2, 5)), false, 5),
        make_shared<consumable>(3, 0, "soda", static_cast<short>(random(2, 5)), false, 3),

        make_shared<consumable>(0, 3, "sandwich", static_cast<short>(random(2, 5))), // food
        make_shared<consumable>(-3, 5, "noodles", static_cast<short>(random(2, 5))),
        make_shared<consumable>(0, 5, "hamburger", static_cast<short>(random(3, 7))),
        make_shared<consumable>(1, 3, "ice cream", static_cast<short>(random(4, 10)), false, 3),

        make_shared<car>(2,"used car", static_cast<short>(random(2000, 8000)), true, -3), // cars
        make_shared<car>(5,"sturdy car", static_cast<short>(random(10000, 20000)), true, 0),
        make_shared<car>(8,"good car", static_cast<short>(random(20000, 35000)), true, 0),
        make_shared<car>(15,"sports car", static_cast<short>(random(50000, 200000)), true, 3),
        make_shared<car>(7,"vintage car", static_cast<short>(random(50000, 200000)), true, 7),
        make_shared<car>(15,"exotic car", static_cast<short>(random(1000000, 10000000)), true, 10)

    };

    auto generateItems = [&generatedShop, &possibleItems](int start, int end) {
        int itemsInShop = generatedShop.vAvailableItems.size();
        while (itemsInShop == generatedShop.vAvailableItems.size()) {
            for (int i = start; i <= end; i++) {  // Loop between start and end
                if (random(0, 1) > 0.5) {
                    generatedShop.vAvailableItems.push_back(possibleItems[i]);
                }
            }
        }
    };

    while (true) {
        // Generate a random value for switchVar
        switchVar = get<int>(randomElement(vector<int>{1, 2}, vector<int>{25, 5}));

        // Check if switchVar matches any value in posCases
        for (int i : posCases) {
            if (switchVar == i) {
                goto switchComplete;
            }
        }
    }

    switchComplete:
    switch (switchVar) {
        case 1:
            generatedShop.sShopName = generateName() + "'s Convenience Store";

            generateItems(0, 3);
            generateItems(4, 7);

        break;
        case 2:
            generatedShop.sShopName = generateName() + "'s Car Dealership";

            generateItems(8, 13);

        break;
    }

    return generatedShop;
}
