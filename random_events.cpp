//
// Created by leona on 09.12.2024.
//

#include "random_events.h"

using namespace std;

void randomEvent(int& balance, int& mentalHealth, int& hunger) {
    srand(time(0)); // Initialisiere den Zufallszahlengenerator
    int event = rand() % 4; // Zufälliges Ereignis auswählen

    switch (event) {
        case 0:
            cout << "You found $50 on the street!" << endl;
        balance += 50;
        break;
        case 1:
            cout << "You got sick and paid $100 for medical bills." << endl;
        balance -= 100;
        mentalHealth -= 10;
        break;
        case 2:
            cout << "You got a bonus at work: $200!" << endl;
        balance += 200;
        break;
        case 3:
            cout << "You lost your wallet and $50!" << endl;
        balance -= 50;
        break;
    }

    // Begrenzung der Werte
    if (mentalHealth > 100) mentalHealth = 100;
    if (mentalHealth < 0) mentalHealth = 0;
    if (hunger > 100) hunger = 100;
    if (hunger < 0) hunger = 0;

    // Aktuellen Zustand ausgeben
    cout << "Your current balance: $" << balance << endl;
    cout << "Your current mental health: " << mentalHealth << "%" << endl;
    cout << "Your current hunger: " << hunger << "%" << endl;
}

