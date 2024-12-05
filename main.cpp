#include <iostream>
#include <string>
#include "WorkLife.cpp"


using namespace std;



int main() {
    SetConsoleOutputCP( 65001 );
    //player stuff
    int totalMoney; //the players amount of money

    //criminal stuff
    int paidFees; //temporary value for paying off crime fees

    Crime pickpocket = {100, 0.05, "pickpocketing", 100};
    Crime shoplift = {200, 0.2, "shoplifting"};
    Crime assault = {500, 0.9, "assault"};
    Crime rape = {750, 0.95, "rape"};
    Crime murder = {900, 0.5, "murder"};
    Crime explosiveDiarrheaInPublicSpace = {50, 0.99, "explosive diarrhea in public space"};

    //caught for a crime (here: murder)
    array<int, 2> prisonCharges = prisonCharge({pickpocket, shoplift, assault, rape, murder, explosiveDiarrheaInPublicSpace}, murder);

    pickpocket.sTimesCommitted = 0;
    shoplift.sTimesCommitted = 0;
    assault.sTimesCommitted = 0;
    rape.sTimesCommitted = 0;
    murder.sTimesCommitted = 0;
    explosiveDiarrheaInPublicSpace.sTimesCommitted = 0;

    if(prisonCharges[0] > 0) {
        cout << "How much do you want to pay off: ";
        cin >> paidFees;
        if(paidFees > totalMoney) {
            paidFees = totalMoney;
        }
        if(paidFees >= prisonCharges[0]){
            paidFees = prisonCharges[0];
            prisonCharges[0] = 0;
        }else if(paidFees < prisonCharges[0]){
            prisonCharges[0] -= paidFees;
        }

        prisonCharges[1] = static_cast<int>(floor(prisonCharges[0] / 100));
        totalMoney -= paidFees;
    }
    //end of being caught for a crime

    class Job teacher(false, 1200, 200);

    gameOver(1);




    return 0;
}
