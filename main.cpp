#include <iostream>
#include "WorkLife.cpp"


using namespace std;



int main() {

    Crime pickpocket = {100, 0.05, "pickpocketing"};
    Crime shoplift = {200, 0.2, "shoplifting"};
    Crime assault = {500, 0.9, "assault"};
    Crime rape = {750, 0.95, "rape"};
    Crime murder = {900, 0.5, "murder", 10};
    Crime explosiveDiarrheaInPublicSpace = {50, 0.99, "explosive diarrhea in public space", 1000};

    //caught for a crime (here: murder)
    array<int, 2> x = prisonTime({pickpocket, shoplift, assault, rape, murder, explosiveDiarrheaInPublicSpace}, murder);

    pickpocket.sTimesCommitted = 0;
    shoplift.sTimesCommitted = 0;
    assault.sTimesCommitted = 0;
    rape.sTimesCommitted = 0;
    murder.sTimesCommitted = 0;
    explosiveDiarrheaInPublicSpace.sTimesCommitted = 0;
    //end of being caught for a crime





    return 0;
}
