//
// Created by leona on 09.12.2024.
//

#include "shop.h"

// Konstruktor: Shop-Artikel initialisieren
Shop::Shop() {
    items.emplace_back("Prostitution", 100, 100, 10);         // Mental Health max, Hunger 10% hungriger
    items.emplace_back("McDonalds Medium Menu", 15, 0, -25);  // Hunger 25% weniger hungrig
    items.emplace_back("Gym Membership", 50, 10, 5);         // Mental Health leicht besser, Hunger 5% hungriger
    items.emplace_back("Therapy Session", 200, 50, 0);        // Mental Health stark besser
}

void Shop::openShop(int& balance, int& hunger, int& mentalHealth) {
    while (true) {
        cout << "\nWelcome to the Shop! Your Balance:" << balance << "$" << endl;
        cout << "Your Hunger: " << hunger << "%, Your Mental Health: " << mentalHealth << "%" << endl;
        cout << "Available items:" << endl;

        for (size_t i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << setw(25) << items[i].name
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
        if (balance >= items[itemIndex].price) {
            balance -= items[itemIndex].price;
            mentalHealth += items[itemIndex].mentalHealthChange;
            hunger += items[itemIndex].hungerChange;

            // Begrenzung der Werte
            if (mentalHealth > 100) mentalHealth = 100;
            if (mentalHealth < 0) mentalHealth = 0;
            if (hunger > 100) hunger = 100;
            if (hunger < 0) hunger = 0;

            cout << "You bought " << items[itemIndex].name
                 << " for " << items[itemIndex].price << "$." << endl;
            cout << "Your new balance is: " << balance << "$" << endl;
            cout << "Your Hunger: " << hunger << "%, Your Mental Health: " << mentalHealth << "%" << endl;
        } else {
            cout << "You don't have enough money to buy this item." << endl;
        }
    }
}

