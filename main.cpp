#include <iostream>
#include <string>
#include "WorkLife.cpp"


using namespace std;



int main() {
    SetConsoleOutputCP(65001);
    int counter1 = 0;
    for(int i = 0; i < 100; i++) {
        Job x = getJob();
        cout << x.sName << endl;
    }
    //player stuff
    int totalMoney = 0; //the players amount of money

    //criminal stuff
    int paidFees; //temporary value for paying off crime fees

    Crime pickpocket = {100, 0.05, "pickpocketing"};
    Crime shoplift = {200, 0.2, "shoplifting"};
    Crime assault = {500, 0.9, "assault"};
    Crime rape = {750, 0.95, "rape"};
    Crime murder = {900, 0.5, "murder"};
    Crime explosiveDiarrheaInPublicSpace = {50, 0.99, "explosive diarrhea in public space"};
    //If there's any crime that gives the death penalty, It should be used as the first input into anything relating to crime

    //caught for a crime (here: assault)
    array<int, 2> prisonCharges = prisonCharge({pickpocket, shoplift, assault, rape, murder, explosiveDiarrheaInPublicSpace}, assault);

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

        prisonCharges[1] += static_cast<int>(floor(prisonCharges[0] / 100));
        totalMoney -= paidFees;
        cout << totalMoney << endl;
        if(prisonCharges[1] > 0) {
            cout << "You paid " << paidFees << "$ and will spend " << prisonCharges[1] << " days in Prison";
            if(prisonCharges[1] > 365) {
                cout << " (" << round(prisonCharges[1]/365*4) / 4 << " years)" << endl;
            }
            else {
                cout << endl;
            }
        }
        else {
            cout << "You paid " << paidFees << "$ to avoid jail time" << endl;
        }
    }
    //end of being caught for a crime



    gameOver(1);




    return 0;
}
