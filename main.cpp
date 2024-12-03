#include <iostream>
#include "Classes1.h"

using namespace std;

void AddCrime(Crime crime) {
    crime.sTimesCommitted++;
}



int prisonTime(array<Crime, 6> BadBoyArray){ //5 is the amount of crimes there are that can be committed
    int time = 1;
    for(int crimes = 0; crimes <= std::size(BadBoyArray); crimes++){

    }
    return time;
}

int main(){

    Crime pickpocket = {1, 0.05};
    Crime shoplift = {1, 0.2};
    Crime assault = {1, 0.9};
    Crime rape = {1, 0.95};
    Crime murder = {1, 0.5};
    Crime explosiveDiarrheaInPublicSpace = {1, 0.99};

    array<Crime, 6> BadBoyArray = {pickpocket, shoplift, assault, rape, murder, explosiveDiarrheaInPublicSpace};
    //Crime BadBoyArray[] = {pickpocket, shoplift, assault, rape, murder, explosiveDiarrheaInPublicSpace};



    return 0;
}
