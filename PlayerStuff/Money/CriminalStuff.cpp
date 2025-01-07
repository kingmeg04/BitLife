#include "CriminalStuff.h"
#include "../../GameStuff/GameOverStuff.h" // Header für gameOver()
#include <iostream>
#include <cmath>

using namespace std;

void prisonCharge(array<Crime, 6>& BadBoyArray, const Crime& CrimeCaughtFor, int totalMoney) {
    cout << "You've been caught for " << CrimeCaughtFor.sName << " and are being charged with the following:" << endl;
    int time = 0;
    int paidFees = 0;
    int fine = 0;

    for (int crimes = 0; crimes < 6; crimes++) {
        int ChargeCount = 0;
        while (BadBoyArray[crimes].sTimesCommitted > 0) {
            BadBoyArray[crimes].sTimesCommitted--;
            if (BadBoyArray[crimes].sName == CrimeCaughtFor.sName) {
                ChargeCount++;

                if (CrimeCaughtFor.sIllegalness <= 200) {
                    fine += CrimeCaughtFor.sIllegalness * 5;
                } else if (CrimeCaughtFor.sIllegalness <= 700) {
                    fine += CrimeCaughtFor.sIllegalness * 5;
                    time += CrimeCaughtFor.sIllegalness * 10;
                } else if (BadBoyArray[crimes].sIllegalness == 1000) {
                    cout << "You were charged with " << BadBoyArray[crimes].sName << endl;
                    gameOver(1); // Korrekte Verwendung von gameOver
                }

                BadBoyArray[crimes].sTimesCommitted--;
                continue;
            }

            ChargeCount++;
            if (BadBoyArray[crimes].sIllegalness <= 200) {
                fine += static_cast<int>(BadBoyArray[crimes].sIllegalness * 5);
            } else if (BadBoyArray[crimes].sIllegalness <= 700) {
                fine += static_cast<int>(BadBoyArray[crimes].sIllegalness * 5);
                time += static_cast<int>(BadBoyArray[crimes].sIllegalness * 10);
            } else {
                time += static_cast<int>(BadBoyArray[crimes].sIllegalness * 15);
            }
        }
        if (ChargeCount != 0) {
            cout << "- " << ChargeCount << " counts of " << BadBoyArray[crimes].sName << endl;
        }
    }

    if (time > 0) {
        cout << "You've been sentenced to " << time << " days in prison." << endl;
    }

    if (fine > 0) {
        cout << "You can pay " << fine << "$ in fines to avoid jail time.\n";
        cout << "How much do you want to pay off: ";
        cin >> paidFees;

        if (paidFees > totalMoney) {
            paidFees = totalMoney;
        }

        fine -= paidFees;
        time += fine / 100;

        cout << "You paid " << paidFees << "$ and will spend " << time << " days in prison." << endl;
    }
}
