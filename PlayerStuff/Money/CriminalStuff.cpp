//
// Created by jbrui on 17.12.2024.
//

#include "CriminalStuff.h"

using namespace std;

void prisonCharge(array<Crime*, 6> BadBoyArray, Crime CrimeCaughtFor, int totalMoney){ //5 is the amount of crimes there are that can be committed
    cout << "You've been caught for " << CrimeCaughtFor.sName << " and are being charged with the following:" << endl;
    int time = 0;
    int paidFees = 0;
    int fine = 0;

    for(int crimes = 0; crimes < 6; crimes++) {
        int ChargeCount = 0;
        while(BadBoyArray[crimes]->sTimesCommitted > 0) {
            BadBoyArray[crimes]->sTimesCommitted--;
            if(BadBoyArray[crimes]->sName == CrimeCaughtFor.sName) {
                ChargeCount++;

                if(CrimeCaughtFor.sIllegalness <= 200) {
                    fine += CrimeCaughtFor.sIllegalness * 5;
                }
                else if(CrimeCaughtFor.sIllegalness <= 700) {
                    fine += CrimeCaughtFor.sIllegalness * 5;
                    time += CrimeCaughtFor.sIllegalness * 10;
                }
                else if(BadBoyArray[crimes]->sIllegalness == 1000) {
                    cout << "You were charged with " << BadBoyArray[crimes]->sName << endl;
                    gameOver(1);
                }

                BadBoyArray[crimes]->sTimesCommitted--;
                CrimeCaughtFor.sName = "0";
                continue;
            }

            if(random(0.0,1.0) < BadBoyArray[crimes]->fWitnessability){

                ChargeCount++;

                if(BadBoyArray[crimes]->sIllegalness <= 200) {
                    fine += static_cast<int>(BadBoyArray[crimes]->sIllegalness * random(1.0, 5.0));
                }
                else if(BadBoyArray[crimes]->sIllegalness <= 700) {
                    fine += static_cast<int>(BadBoyArray[crimes]->sIllegalness * random(1.0, 5.0));
                    time += static_cast<int>(BadBoyArray[crimes]->sIllegalness * random(2.5,10.0));

                }
                else if(BadBoyArray[crimes]->sIllegalness == 1000) {
                    cout << "You were charged with " << BadBoyArray[crimes]->sName << endl;
                    gameOver(1);
                }
                else {
                    time += static_cast<int>(BadBoyArray[crimes]->sIllegalness * random(5.0,15.0));

                }
            }
        }
        if(ChargeCount != 0) {
            cout << "- "<< ChargeCount << " counts of "<<BadBoyArray[crimes]->sName << endl;
        }

    }
    if(time > 0) {
        cout << "You've been sentenced to " << time << " days in prison." << endl;


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
        if(paidFees > totalMoney) {
            paidFees = totalMoney;
            fine -= paidFees;
        }
        if(paidFees >= fine){
            paidFees = fine;
            fine = 0;
        }else if(paidFees < fine){
            fine -= paidFees;
        }

        time += static_cast<int>(floor(fine / 100));
        totalMoney -= paidFees;
        cout << totalMoney << endl;
        if(time > 0) {
            cout << "You paid " << paidFees << "$ and will spend " << time << " days in Prison";
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
    }
}
