//
// Created by leona on 09.12.2024.
//

#include "family.h"

void FamilyManager::getMarried(Family& family, int& balance) {
    if (!family.spouseName.empty()) {
        cout << "You are already married to " << family.spouseName << "!" << endl;
        return;
    }

    if (balance >= 1000) {
        family.spouseName = "Alex"; // Hier könnte man den Namen zufällig generieren
        cout << "You got married to " << family.spouseName << "!" << endl;
        balance -= 1000; // Hochzeitskosten
    } else {
        cout << "Not enough money to get married. You need $1000." << endl;
    }
}

void FamilyManager::haveChild(Family& family, int& balance) {
    if (family.spouseName.empty()) {
        cout << "You need to get married first before having children!" << endl;
        return;
    }

    if (balance >= 500) {
        string childName = "Baby " + to_string(family.children.size() + 1); // Einfacher Name
        family.children.push_back(childName);
        cout << "Congratulations! " << family.spouseName << " gave birth to " << childName << "!" << endl;
        balance -= 500; // Geburtskosten
    } else {
        cout << "Not enough money to have a child. You need $500." << endl;
    }
}

void FamilyManager::displayFamily(const Family& family) {
    cout << "\nFamily Overview:" << endl;

    if (family.spouseName.empty()) {
        cout << "You are not married." << endl;
    } else {
        cout << "Spouse: " << family.spouseName << endl;
    }

    if (family.children.empty()) {
        cout << "No children yet." << endl;
    } else {
        cout << "Children:" << endl;
        for (const auto& child : family.children) {
            cout << "- " << child << endl;
        }
    }
}
