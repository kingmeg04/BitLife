#include <iostream>
#include <random>
#include "Classes1.h"
#include "UniversalStuff.cpp"

using namespace std;


void AddCrime(Crime crime) {
    crime.sTimesCommitted++;
}

array<int, 2> prisonTime(array<Crime, 6> BadBoyArray, Crime CrimeCaugtFor){ //5 is the amount of crimes there are that can be committed
    cout << "You've been charged with:" << endl;
    int time = 0;
    int fine = 0;

    for(int crimes = 0; crimes < 6; crimes++) {
        int ChargeCount = 0;
        BadBoyArray[crimes].sTimesCommitted;
        while(BadBoyArray[crimes].sTimesCommitted > 0) {
            BadBoyArray[crimes].sTimesCommitted--;


            if(random(0.0,1.0) < BadBoyArray[crimes].fWitnessability){
                if(BadBoyArray[crimes].sName == CrimeCaugtFor.sName) {
                    ChargeCount++;

                    if(CrimeCaugtFor.sIllegalness <= 200) {
                        fine += CrimeCaugtFor.sIllegalness * 5;
                    }
                    else if(CrimeCaugtFor.sIllegalness <= 700) {
                        fine += CrimeCaugtFor.sIllegalness * 5;
                        time += CrimeCaugtFor.sIllegalness * 10;
                    }
                    else {
                        time += CrimeCaugtFor.sIllegalness * 20;
                    }

                    BadBoyArray[crimes].sTimesCommitted--;
                    CrimeCaugtFor.sName = "0";
                    continue;

                }
                ChargeCount++;

                if(BadBoyArray[crimes].sIllegalness <= 200) {
                    fine += static_cast<int>(BadBoyArray[crimes].sIllegalness * random(1.0, 5.0));
                }
                else if(BadBoyArray[crimes].sIllegalness <= 700) {
                    fine += static_cast<int>(BadBoyArray[crimes].sIllegalness * random(1.0, 5.0));
                    time += static_cast<int>(BadBoyArray[crimes].sIllegalness * random(2.5,10.0));

                }
                else {
                    time += static_cast<int>(BadBoyArray[crimes].sIllegalness * random(5.0,20.0));

                }
            }
        }
        if(ChargeCount != 0) {
            cout << "- "<< ChargeCount << " counts of "<<BadBoyArray[crimes].sName << endl;
        }

    }
    if(fine > 0 && time <= 0) {
        cout << "You can pay up to " << fine <<"$ to avoid spending " << static_cast<int>(floor(fine / 100)) << " days in prison." << endl;
    }
    else if(fine > 0 && time > 0) {
        cout << "You've been sentenced to " << time << " days in prison." << endl;
        cout << "Additionally you can pay up to " << fine << "$ to avoid spending an additional" << static_cast<int>(floor(fine / 100)) << " days in prison." << endl;
    }
    else if(fine <= 0 && time > 0) {
        cout << "You've been sentenced to " << time << " days in prison." << endl;
    }

    return {fine, time};
}
