#include <iostream>
#include <random>
#include "Classes1.h"

std::random_device rd;  // Seed for random number generator
std::mt19937 gen(rd()); // Mersenne Twister RNG
std::uniform_real_distribution<> dis(0.0, 1.0); // Uniform distribution [0, 1)

using namespace std;


void AddCrime(Crime crime) {
    crime.sTimesCommitted++;
}

int prisonTime(array<Crime, 6> BadBoyArray){ //5 is the amount of crimes there are that can be committed
    cout << "You've been charged with:" << endl;
    int time = 1;
    for(int crimes = 0; crimes < 6; crimes++) {
        int ChargeCount = 0;
        BadBoyArray[crimes].sTimesCommitted;
        while(BadBoyArray[crimes].sTimesCommitted > 0) {
            BadBoyArray[crimes].sTimesCommitted--;

            if(dis(gen) < BadBoyArray[crimes].fWitnessability){
                time += BadBoyArray[crimes].sIllegalness;
                ChargeCount++;
            }
        }
        cout << "- "<< ChargeCount << " counts of "<<BadBoyArray[crimes].sName << endl;
    }
    cout << "You've been sentenced to " << time << " days in prison." << endl;
    return time;

}
