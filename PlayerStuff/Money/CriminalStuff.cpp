//
// Created by jbrui on 17.12.2024.
//

#include "CriminalStuff.h"

using namespace std;

vector<crime> getCrimeVector() {
    vector<crime> crimesVector = {
        crime{20, 0.5, "shoplifting"},
        crime{40, 0.25, "fraud"},
        crime{70, 0.8, "arson"},
        crime{80, 0.75, "robbery"},
        crime{5, 0.05, "pickpocketing"},
        crime{50, 0.6, "burglary"},
        crime{100, 0.1, "murder"}
    };

    return crimesVector;
}

void prisonCharge(player& thePlayer, crime crimeCaughtFor) {
    cout << "You've been caught for " << crimeCaughtFor.sName << " and are being charged with the following:" << endl;
    int time = 0, fine = 0, paidFees = 0;

    const int LOW_ILLEGALNESS = 20;
    const int MEDIUM_ILLEGALNESS = 50;
    const int MAX_ILLEGALNESS = 100;
    const int FINE_TO_TIME_RATIO = 100;

    for (int crimes = 0; crimes < thePlayer.vCrimes.size(); crimes++) {
        if (thePlayer.vCrimes[crimes].first.sName == crimeCaughtFor.sName) {
            if (crimeCaughtFor.sIllegalness <= LOW_ILLEGALNESS) {
                fine += crimeCaughtFor.sIllegalness * 50;
            } else if (crimeCaughtFor.sIllegalness <= MEDIUM_ILLEGALNESS) {
                fine += crimeCaughtFor.sIllegalness * 50;
                time += crimeCaughtFor.sIllegalness * 100;
            } else if (crimeCaughtFor.sIllegalness == MAX_ILLEGALNESS) {
                cout << "You received the death penalty for " << thePlayer.vCrimes[crimes].first.sName << " and were electrocuted to death" << endl;
                thePlayer.playerHealth -= 1000;
                gameOver(1);
                return;
            }
            thePlayer.vCrimes[crimes].second--;
            break;
        }
    }

    for (int crimes = 0; crimes < thePlayer.vCrimes.size(); crimes++) {
        int chargeCount = 0;
        if (crimeCaughtFor.sName == thePlayer.vCrimes[crimes].first.sName) {
            chargeCount = 1;
        }
        while (thePlayer.vCrimes[crimes].second > 0) {
            thePlayer.vCrimes[crimes].second--;
            if (random(0.0, 1.0) < thePlayer.vCrimes[crimes].first.fWitnessability) {
                if (thePlayer.vCrimes[crimes].first.sIllegalness >= MAX_ILLEGALNESS) {
                    cout << "You received the death penalty for " << thePlayer.vCrimes[crimes].first.sName << " and were electrocuted to death" << endl;
                    gameOver(1);
                    thePlayer.playerHealth -= 1000;
                    return;
                }
                chargeCount++;
                fine += static_cast<int>(thePlayer.vCrimes[crimes].first.sIllegalness * 10 * random(1.0, 5.0));
                if (thePlayer.vCrimes[crimes].first.sIllegalness >= MEDIUM_ILLEGALNESS) {
                    time += static_cast<int>(thePlayer.vCrimes[crimes].first.sIllegalness * 10 * random(2.5, 10.0));
                }
            }
        }
        if (chargeCount > 0) {
            cout << "- " << chargeCount << " counts of " << thePlayer.vCrimes[crimes].first.sName << endl;
        }
    }

    if (time > 0) {
        cout << "You've been sentenced to " << thePlayer.iJailTime + time << " days in prison." << endl;
    }

    if (fine > 0) {
        cout << "You can pay " << fine << "$ to avoid spending " << fine / FINE_TO_TIME_RATIO << " days in prison." << endl;
        cout << "How much do you want to pay off: ";
        cin >> paidFees;

        if (paidFees > fine) paidFees = fine;
        if (paidFees > thePlayer.balance) paidFees = thePlayer.balance;

        fine -= paidFees;
        thePlayer.balance -= paidFees;
        time += fine / FINE_TO_TIME_RATIO;

        if (time > 0) {
            cout << "You paid " << paidFees << "$ and will spend " << time << " days in prison." << endl;
        } else {
            cout << "You paid " << paidFees << "$ to avoid jail time." << endl;
        }
    }

    thePlayer.vCrimes.clear();
    thePlayer.iJailTime += time;
}
