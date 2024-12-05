#include <iostream>
#include "WorkLife.cpp"


using namespace std;



int main() {


    Crime pickpocket = {100, 0.05, "pickpocketing"};
    Crime shoplift = {200, 0.2, "shoplifting"};
    Crime assault = {500, 0.9, "assault"};
    Crime rape = {750, 0.95, "rape"};
    Crime murder = {900, 0.5, "murder"};
    Crime explosiveDiarrheaInPublicSpace = {50, 0.99, "explosive diarrhea in public space"};

    array<int, 2> x = prisonTime({pickpocket, shoplift, assault, rape, murder, explosiveDiarrheaInPublicSpace}, murder);

    pickpocket.sTimesCommitted = 0;
    shoplift.sTimesCommitted = 0;
    assault.sTimesCommitted = 0;
    rape.sTimesCommitted = 0;
    murder.sTimesCommitted = 0;
    explosiveDiarrheaInPublicSpace.sTimesCommitted = 0;

    //array<Crime, 6> BadBoyArray = {pickpocket, shoplift, assault, rape, murder, explosiveDiarrheaInPublicSpace};
    //Crime BadBoyArray[] = {pickpocket, shoplift, assault, rape, murder, explosiveDiarrheaInPublicSpace};



    return 0;
}
