//
// Created by jbrui on 17.12.2024.
//

#include "CriminalStuff.h"

using namespace std;

void prisonCharge(player& thePlayer, crime crimeCaughtFor){ //5 is the amount of crimes there are that can be committed EDIT THIS
    cout << "You've been caught for " << crimeCaughtFor.sName << " and are being charged with the following:" << endl;
    int time = 0;
    int paidFees = 0;
    int fine = 0;
    int chargeCount = 0;

    for (int crimes = 0; crimes < thePlayer.vCrimes.size(); crimes++) {
        if (thePlayer.vCrimes[crimes].first.sName == crimeCaughtFor.sName) {
            if(crimeCaughtFor.sIllegalness <= 200) {
                fine += crimeCaughtFor.sIllegalness * 5;
            }
            else if(crimeCaughtFor.sIllegalness <= 700) {
                fine += crimeCaughtFor.sIllegalness * 5;
                time += crimeCaughtFor.sIllegalness * 10;
            }
            else if(crimeCaughtFor.sIllegalness == 1000) {
                cout << "You were charged with " << crimeCaughtFor.sName << endl;
                gameOver(1);
                return;
            }
            thePlayer.vCrimes[crimes].second--; //If caught and a crime isn't added then get rid of this line
            break;
        }
    }

    for (int crimes = 0; crimes < thePlayer.vCrimes.size(); crimes++) {
        chargeCount = 0;
        while (thePlayer.vCrimes[crimes].second > 0) {
            thePlayer.vCrimes[crimes].second--;

            if(random(0.0,1.0) < thePlayer.vCrimes[crimes].first.fWitnessability){
                chargeCount++;

                if(thePlayer.vCrimes[crimes].first.sIllegalness <= 200) {
                    fine += static_cast<int>(thePlayer.vCrimes[crimes].first.sIllegalness * random(1.0, 5.0));
                }
                else if(thePlayer.vCrimes[crimes].first.sIllegalness <= 700) {
                    fine += static_cast<int>(thePlayer.vCrimes[crimes].first.sIllegalness * random(1.0, 5.0));
                    time += static_cast<int>(thePlayer.vCrimes[crimes].first.sIllegalness * random(2.5,10.0));

                }
                else if(thePlayer.vCrimes[crimes].first.sIllegalness == 1000) {
                    cout << "You were charged with " << thePlayer.vCrimes[crimes].first.sName << endl;
                    gameOver(1);
                }
                else {
                    time += static_cast<int>(thePlayer.vCrimes[crimes].first.sIllegalness * random(5.0,15.0));
                }
            }
        }
        if (thePlayer.vCrimes[crimes].first.sName == crimeCaughtFor.sName) {
            chargeCount++;
        }
        if (chargeCount != 0) {
            cout << "- " << chargeCount << " counts of " << thePlayer.vCrimes[crimes].first.sName << endl;
        }
    }
    if(time > 0) {
        cout << "You've been sentenced to " << thePlayer.iJailTime + time << " days in prison." << endl;
    }


    if(fine > 0) {
        if(time > 0) {
            cout << "Additionally you can pay " << fine << "$ in fines to avoid spending an additional ";
        }
        else {
            cout << "You can pay " << fine << "$ in fines to avoid spending ";
        }
        cout << static_cast<int>(floor(fine / 100)) << " days in prison." << endl;

        if(static_cast<int>(floor(fine / 100)) > 365) {
            cout << " (" << static_cast<int>(floor(fine / 100)) / 4 << " years)" << endl;
        }

        cout << "How much do you want to pay off: ";
        cin >> paidFees;

        if(paidFees > thePlayer.balance) {
            paidFees = thePlayer.balance;
        }

        if(paidFees >= fine){
            paidFees = fine;
        }

        fine -= paidFees;

        time += static_cast<int>(floor(fine / 100));
        thePlayer.balance -= paidFees;
        cout << thePlayer.balance << endl;

        if(time > 0) {
            cout << "You paid " << paidFees << "$ and will spend " << thePlayer.iJailTime + time << " days in Prison";
            if(time > 365) {
                cout << " (" << round(time/365*4) / 4 << " years)" << endl;
            }
            else {
                cout << endl;
            }
        }
        else {
            cout << "You paid " << paidFees << "$ to avoid jail time" << endl;
        }
        while (thePlayer.vCrimes.size() > 0) {
            thePlayer.vCrimes.pop_back();
        }
        thePlayer.iJailTime += time;
    }
}
