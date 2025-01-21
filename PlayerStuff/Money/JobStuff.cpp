//
// Created by jbrui on 17.12.2024.
//

#include "JobStuff.h"
#include "../../UniversalStuff/RandomStuff.h"
#include <iostream>

using namespace std;

vector<int> jobWeights = {150, 150, 100, 50, 5, 25, 100, 10, 25, 10, 15, 10, 1};



vector<job> getJobVector(){
    return {
        job(static_cast<short>(round(random(50, 750))), static_cast<short>(round(random(0, 25))), "farmer"),
        job(static_cast<short>(round(random(50, 750))), static_cast<short>(round(random(0, 25))), "fisher"),
        job(static_cast<short>(round(random(100, 200))), static_cast<short>(round(random(25, 50))), "cashier"),
        job(static_cast<short>(round(random(200, 1200))), static_cast<short>(round(random(40, 60))), "teacher"),
        job(static_cast<short>(round(random(500, 2000))), static_cast<short>(round(random(10, 30))), "cool teacher"),
        job(static_cast<short>(round(random(1000, 3000))), static_cast<short>(round(random(25, 75))), "professor"),
        job(static_cast<short>(round(random(75, 350))), static_cast<short>(round(random(0, 15))), "janitor"),
        job(static_cast<short>(round(random(0, 100))), static_cast<short>(round(random(25, 100))), "homeless"),
        job(static_cast<short>(round(random(0, 0))), static_cast<short>(round(random(10, 50))), "jobless"),
        job(static_cast<short>(round(random(100, 400))), static_cast<short>(round(random(0, 5))), "workless"),
        job(static_cast<short>(round(random(500, 3000))), static_cast<short>(round(random(30, 70))), "mayor"),
        job(static_cast<short>(round(random(2000, 5000))), static_cast<short>(round(random(50, 80))), "politician"),
        job(static_cast<short>(round(random(5000, 10000))), static_cast<short>(round(random(70, 100))), "prime Minister")
    };
}

job getRandomJob() {
    return get<job>(randomElement(getJobVector(), jobWeights));
}

job changeJob(int posOptions) {
    vector<job> opportunities;
    int chosenOption;

    cout << "You've been offered the following job opportunities:" << endl;

    for(int i = 0; i < posOptions; i++) {
        opportunities.push_back(getRandomJob());
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
