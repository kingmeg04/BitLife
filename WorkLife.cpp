#include <iostream>
#include <random>
#include "Classes1.h"
#include "UniversalStuff.cpp"

using namespace std;

vector<Job> jobs = {
    Job(static_cast<short>(round(random(50, 750))), static_cast<short>(round(random(0, 250))), "farmer"),
    Job(static_cast<short>(round(random(50, 750))), static_cast<short>(round(random(0, 250))), "fisher"),
    Job(static_cast<short>(round(random(100, 200))), static_cast<short>(round(random(250, 500))), "cashier"),
    Job(static_cast<short>(round(random(200, 1200))), static_cast<short>(round(random(400, 750))), "teacher"),
    Job(static_cast<short>(round(random(500, 2000))), static_cast<short>(round(random(100, 300))), "cool teacher"),
    Job(static_cast<short>(round(random(1000, 3000))), static_cast<short>(round(random(250, 750))), "professor"),
    Job(static_cast<short>(round(random(75, 350))), static_cast<short>(round(random(0, 150))), "janitor"),
    Job(static_cast<short>(round(random(0, 100))), static_cast<short>(round(random(250, 1000))), "homeless"),
    Job(static_cast<short>(round(random(0, 0))), static_cast<short>(round(random(100, 500))), "jobless"),
    Job(static_cast<short>(round(random(250, 1000))), static_cast<short>(round(random(0, 50))), "workless"),
};

vector<double> weights = {150, 150, 100, 50, 5, 25, 100, 10, 25, 10}; // values between 1 - 1000 for how probable it is to get a certain job

//Working stuff
class Job getJob() {

    vector<double> jobChances = chanceDistribution(weights);

    return randomElement(jobs, jobChances);
}

class Job changeJob(Job currentJob, int posOptions) {
    vector<Job> opportunities;
    int chosenOption;

    cout << "You've been offered the following job opportunities:" << endl;

    for(int i = 0; i < posOptions; i++) {
        opportunities.push_back(getJob());
        for(int j = 0; j < opportunities.size()-1; j++) {
            if(opportunities[j].sName == opportunities[opportunities.size() - 1].sName) {
                opportunities.pop_back();
                chosenOption = 1;
                i--;
                break;
            }
        }
        if(chosenOption == 1) {
            chosenOption = 0;
            continue;
        }
        else {
            cout << "[" << i + 1 << "] " << opportunities[i].sName << " (" << opportunities[i].sSalary << "$ / week)" <<endl;
        }
    }

    chosenOption = 0;

    cout << "Which Job would you like to choose (just the number): ";
    cin >> chosenOption;


    while(chosenOption <= 0 || chosenOption > posOptions) {
        cout << endl;
        cout << "The input was invalid, please choose a number that is displayed: ";
        cin >> chosenOption;

    }



    return opportunities[chosenOption - 1];
}


//Criminal stuff
void AddCrime(Crime crime){
    crime.sTimesCommitted++;
}

array<int, 2> prisonCharge(array<Crime, 6> BadBoyArray, Crime CrimeCaughtFor){ //5 is the amount of crimes there are that can be committed
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
                else if(BadBoyArray[crimes].sIllegalness == 1000) {
                    cout << "You were charged with " << BadBoyArray[crimes].sName << endl;
                    gameOver(1);
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
                else if(BadBoyArray[crimes].sIllegalness == 1000) {
                    cout << "You were charged with " << BadBoyArray[crimes].sName << endl;
                    gameOver(1);
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
