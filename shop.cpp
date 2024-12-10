//
// Created by leona on 09.12.2024.
//

#include "shop.h"
#include "Player.h"

using namespace std;

// Konstruktor: Shop-Artikel initialisieren
Shop::Shop() {
    items.emplace_back("Prostitution", 100, 100, 10);         // Mental Health max, Hunger 10% hungriger
    items.emplace_back("McDonalds Medium Menu", 15, 0, -25);  // Hunger 25% weniger hungrig
    items.emplace_back("Gym Membership", 50, 10, 5);         // Mental Health leicht besser, Hunger 5% hungriger
    items.emplace_back("Therapy Session", 200, 50, 0);        // Mental Health stark besser
}

void Shop::openShop(player& player) {
    while (true) {
        cout << "\nWelcome to the Shop! Your Balance:" << player.balance << "$" << endl;
        cout << "Your saturation: " << player.saturation << "%, Your Mental Health: " << player.mentalHealth << "%" << endl;
        cout << "Available items:" << endl;

        for (size_t i = 0; i < items.size(); i++) {
            cout << "[" << i + 1 << "] " << items[i].name
                 << " - " << items[i].price << "$"
                 << " (Mental Health: " << items[i].mentalHealthChange
                 << ", Hunger: " << items[i].hungerChange << "%)" << endl;
        }
        cout << "0. Exit Shop" << endl;

        int choice;
        cout << "Select an item to purchase (0 to exit): ";
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting shop..." << endl;
            break;
        }

        if (choice < 1 || choice > static_cast<int>(items.size())) {
            cout << "Invalid choice. Please try again:" << endl;
            continue;
        }

        int itemIndex = choice - 1;
        if (player.balance >= items[itemIndex].price) {
            player.balance -= items[itemIndex].price;
            player.mentalHealth += items[itemIndex].mentalHealthChange;
            player.saturation += items[itemIndex].hungerChange;

            // Begrenzung der Werte
            if (player.mentalHealth > 100) player.mentalHealth = 100;
            if (player.mentalHealth < 0) player.mentalHealth = 0;
            if (player.saturation > 100) player.saturation = 100;
            if (player.saturation < 0) player.saturation = 0;

            cout << "You bought " << items[itemIndex].name
                 << " for " << items[itemIndex].price << "$." << endl;
            cout << "Your new balance is: " << player.balance << "$" << endl;
            cout << "Your saturation: " << player.saturation << "%, Your Mental Health: " << player.mentalHealth << "%" << endl;
        } else {
            cout << "You don't have enough money to buy this item." << endl;
        }
    }
}

