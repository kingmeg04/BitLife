#include <iostream>
#include <random>
#include "Classes1.h"
#include "UniversalStuff.cpp"

using namespace std;

void AddCrime(Crime crime) {
    crime.sTimesCommitted++;
}

array<int, 2> prisonTime(array<Crime, 6> BadBoyArray, Crime CrimeCaughtFor){ //5 is the amount of crimes there are that can be committed
    cout << "You've been caught for " << CrimeCaughtFor.sName << " and are being charged with the following:" << endl;
    int time = 0;
    int fine = 0;

    for(int crimes = 0; crimes < 6; crimes++) {
        int ChargeCount = 0;
        BadBoyArray[crimes].sTimesCommitted;
        while(BadBoyArray[crimes].sTimesCommitted > 0) {
            BadBoyArray[crimes].sTimesCommitted--;
            if(BadBoyArray[crimes].sName == CrimeCaughtFor.sName) {
                ChargeCount++;

                if(CrimeCaughtFor.sIllegalness <= 200) {
                    fine += CrimeCaughtFor.sIllegalness * 5;
                }
                else if(CrimeCaughtFor.sIllegalness <= 700) {
                    fine += CrimeCaughtFor.sIllegalness * 5;
                    time += CrimeCaughtFor.sIllegalness * 10;
                }
                else {
                    time += CrimeCaughtFor.sIllegalness * 15;
                }

                BadBoyArray[crimes].sTimesCommitted--;
                CrimeCaughtFor.sName = "0";
                continue;
            }

            if(random(0.0,1.0) < BadBoyArray[crimes].fWitnessability){

                ChargeCount++;

                if(BadBoyArray[crimes].sIllegalness <= 200) {
                    fine += static_cast<int>(BadBoyArray[crimes].sIllegalness * random(1.0, 5.0));
                }
                else if(BadBoyArray[crimes].sIllegalness <= 700) {
                    fine += static_cast<int>(BadBoyArray[crimes].sIllegalness * random(1.0, 5.0));
                    time += static_cast<int>(BadBoyArray[crimes].sIllegalness * random(2.5,10.0));

                }
                else {
                    time += static_cast<int>(BadBoyArray[crimes].sIllegalness * random(5.0,15.0));

                }
            }
        }
        if(ChargeCount != 0) {
            cout << "- "<< ChargeCount << " counts of "<<BadBoyArray[crimes].sName << endl;
        }

    }
    if(fine > 0 && time <= 0) {
        cout << "You can pay up to " << fine <<"$ to avoid spending " << static_cast<int>(floor(fine / 100)) << " days in prison.";
        if(static_cast<int>(floor(fine / 100)) > 365) {
            cout << " (" << round(static_cast<int>(floor(fine / 100)/365)*4) / 4 << " years)" << endl;
        }
        else {
            cout << endl;
        }
    }
    else if(fine > 0 && time > 0) {
        cout << "You've been sentenced to " << time << " days in prison.";
        if(time > 365) {
            cout << " (" << round(time/365*4) / 4 << " years)" << endl;
        }
        else {
            cout << endl;
        }
        cout << "Additionally you can pay up to " << fine << "$ to avoid spending an additional " << static_cast<int>(floor(fine / 100)) << " days in prison.";
        if(static_cast<int>(floor(fine / 100)) > 365) {
            cout << " (" << round(static_cast<int>(floor(fine / 100)/365)*4) / 4 << " years)" << endl;
        }
        else {
            cout << endl;
        }
    }
    else if(fine <= 0 && time > 0) {
        cout << "You've been sentenced to " << time << " days in prison.";
        if(time > 365) {
            cout << " (" << round(time/365*4) / 4 << " years)" << endl;
        }
        else {
            cout << endl;
        }
    }

    return {fine, time};
}
