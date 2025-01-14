//
// Created by jbrui on 17.12.2024.
//

#include "CriminalStuff.h"

using namespace std;

void prisonCharge(player& thePlayer, crime crimeCaughtFor) {
    cout << "You've been caught for " << crimeCaughtFor.sName << " and are being charged with the following:" << endl;
    int time = 0, fine = 0, paidFees = 0;

    const int LOW_ILLEGALNESS = 200;
    const int MEDIUM_ILLEGALNESS = 700;
    const int MAX_ILLEGALNESS = 1000;
    const int FINE_TO_TIME_RATIO = 100;

    for (int crimes = 0; crimes < thePlayer.vCrimes.size(); crimes++) {
        if (thePlayer.vCrimes[crimes].first.sName == crimeCaughtFor.sName) {
            if (crimeCaughtFor.sIllegalness <= LOW_ILLEGALNESS) {
                fine += crimeCaughtFor.sIllegalness * 5;
            } else if (crimeCaughtFor.sIllegalness <= MEDIUM_ILLEGALNESS) {
                fine += crimeCaughtFor.sIllegalness * 5;
                time += crimeCaughtFor.sIllegalness * 10;
            } else if (crimeCaughtFor.sIllegalness == MAX_ILLEGALNESS) {
                cout << "You were charged with " << crimeCaughtFor.sName << endl;
                gameOver(1);
                return;
            }
            thePlayer.vCrimes[crimes].second--;
            break;
        }
    }

    for (int crimes = 0; crimes < thePlayer.vCrimes.size(); crimes++) {
        int chargeCount = 0;
        while (thePlayer.vCrimes[crimes].second > 0) {
            thePlayer.vCrimes[crimes].second--;
            if (random(0.0, 1.0) < thePlayer.vCrimes[crimes].first.fWitnessability) {
                chargeCount++;
                fine += static_cast<int>(thePlayer.vCrimes[crimes].first.sIllegalness * random(1.0, 5.0));
                if (thePlayer.vCrimes[crimes].first.sIllegalness > MEDIUM_ILLEGALNESS) {
                    time += static_cast<int>(thePlayer.vCrimes[crimes].first.sIllegalness * random(2.5, 10.0));
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
