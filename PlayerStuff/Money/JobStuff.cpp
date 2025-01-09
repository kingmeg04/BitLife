//
// Created by jbrui on 17.12.2024.
//

#include "JobStuff.h"

using namespace std;

vector<double> jobWeights = {150, 150, 100, 50, 5, 25, 100, 10, 25, 10, 15, 10, 1};



vector<job> getJobVector(){
    return {
        job(static_cast<short>(round(random(50, 750))), static_cast<short>(round(random(0, 250))), "farmer"),
        job(static_cast<short>(round(random(50, 750))), static_cast<short>(round(random(0, 250))), "fisher"),
        job(static_cast<short>(round(random(100, 200))), static_cast<short>(round(random(250, 500))), "cashier"),
        job(static_cast<short>(round(random(200, 1200))), static_cast<short>(round(random(400, 600))), "teacher"),
        job(static_cast<short>(round(random(500, 2000))), static_cast<short>(round(random(100, 300))), "cool teacher"),
        job(static_cast<short>(round(random(1000, 3000))), static_cast<short>(round(random(250, 750))), "professor"),
        job(static_cast<short>(round(random(75, 350))), static_cast<short>(round(random(0, 150))), "janitor"),
        job(static_cast<short>(round(random(0, 100))), static_cast<short>(round(random(250, 1000))), "homeless"),
        job(static_cast<short>(round(random(0, 0))), static_cast<short>(round(random(100, 500))), "jobless"),
        job(static_cast<short>(round(random(100, 400))), static_cast<short>(round(random(0, 50))), "workless"),
        job(static_cast<short>(round(random(500, 3000))), static_cast<short>(round(random(300, 700))), "mayor"),
        job(static_cast<short>(round(random(2000, 5000))), static_cast<short>(round(random(500, 800))), "politician"),
        job(static_cast<short>(round(random(5000, 10000))), static_cast<short>(round(random(700, 1000))), "prime Minister")
    };
}

job getRandomJob() {
    return get<job>(randomElement(getJobVector(), chanceDistribution(jobWeights)));
}

job changeJob(job currentJob, int posOptions) {
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