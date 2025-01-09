//
// Created by kingm on 07/01/2025.
//

#include "RandomEventStuff.h"

using namespace std;

void randomEventSelector(player &thePlayer, int currentDay) {
    vector<double> weights = {20,};
    vector<int> options = {1,2,3,4};
    int chosenElement = get<int>(randomElement(vector<int>{1,2,3,4,5}, vector<double>{20,20,5,}));
    switch (chosenElement) {
        case 1:
            dating(thePlayer);
            break;
        case 2:
            prank(thePlayer);
            break;
        case 3:
            policeInvestigation(thePlayer);
            break;
        case 4:
            winRandomGiveaway(thePlayer);
            break;
    }
}
//
void dating(player &thePlayer) {
    string option;

    if (random(0,1) > 0.5) {
        cout << "Do you want to ask someone out on a date(Y/N): ";
        cin >> option;
        cout << endl;
        if (option != "Y" && option != "y") {
            return;
        }
        else{
            if (random(0,1) > 0.25) {
                cout << "They said yes." << endl;
                for (int checker = 0; checker < thePlayer.vItems.size(); checker++) {
                    if (thePlayer.vItems[checker].first.sItemName == "partner") {
                        thePlayer.vItems[checker].second++;
                        cout << "You now have " << thePlayer.vItems[checker].second << " partners." << endl;
                        return;
                    }
                }
                cout << "You now have a partner." << endl;
                thePlayer.vItems.push_back({{"partner", 0, true, 5}, 1});
            }
            else {
                cout << "You were rejected." << endl;
                thePlayer.mentalHealth -= floor(round(random(0,15)));
            }
        }
    }
    else {
        cout << "Someone asked you out on a date." << endl;
        cout << "How do you respond (Y/N): " << endl;
        cin >> option;
        cout << endl;
        if (option != "Y"||option != "y") {
            return;
        }
        else {
            for (int checker = 0; checker < thePlayer.vItems.size(); checker++) {
                if (thePlayer.vItems[checker].first.sItemName == "partner") {
                    thePlayer.vItems[checker].second++;
                    cout << "You now have " << thePlayer.vItems[checker].second << " partners." << endl;
                    return;
                }
            }
            cout << "You now have a partner." << endl;
            thePlayer.vItems.push_back({{"partner", 0, true, 5}, 1});
        }
    }
}

void prank(player &thePlayer) {
    string option;
    int payCut;

    cout << "Do you want to pull a prank on somebody from work (Y/N): ";
    cin >> option;
    cout << endl;
    if (option != "Y" && option != "y") {
        return;
    }
    else {
        if (random(0,1) > 0.25) {
            cout << "You successfully pulled the prank." << endl;
            thePlayer.mentalHealth += floor(round(random(0,5)));
            return;
        }
        else {
            cout << "You were caught in the act." << endl;
            int payCut = ceil(random(thePlayer.jCurrentJob.sSalary/100, thePlayer.jCurrentJob.sSalary/75));
            thePlayer.jCurrentJob.sSalary -= payCut;
            if (thePlayer.jCurrentJob.sName != "jobless" && thePlayer.jCurrentJob.sName != "homeless" && thePlayer.jCurrentJob.sName != "child") {
                if (thePlayer.jCurrentJob.sSalary <= 0) {
                    cout << "You were fired from your position as ";
                    if (thePlayer.jCurrentJob.bIsAdmin) {
                        cout << "admin";
                    }
                    cout << thePlayer.jCurrentJob.sName << " and are now workless" << endl;
                    thePlayer.jCurrentJob = {static_cast<short>(round(random(100, 400))), static_cast<short>(round(random(0, 50))), "workless"};
                    return;
                }
            }
            else {
                thePlayer.sCriminalReputation += floor(random(0,5));
            }

        }
    }
}

void policeInvestigation(player &thePlayer) {
    string option;
    unsigned short reward;

    cout << "You witnessed a crime and now the police are asking you about the investigation." << endl;
    cout << "Will you tell the police who did it (Y/N): ";
    cin >> option;
    cout << endl;
    if (option != "Y" && option != "y") {
        thePlayer.sCriminalReputation += floor(random(10, 20));
        if (thePlayer.sCriminalReputation >= 50) {
            reward = ceil(random(100,2500));
            cout << "The homies respect your decision and give you a reward of " << reward << "$ for your action." << endl;
        }
    }
    else {
        thePlayer.sCriminalReputation += floor(random(0,10));
        cout << "The police thanks you for your honesty" << endl;
        if (thePlayer.sCriminalReputation >= 50) {
            cout << "The homies feel betrayed and beat you in an alley." << endl;
            thePlayer.playerHealth -= floor(random(5,25));
            if (thePlayer.playerHealth <= 0) {
                //deathEvent() cause is beaten to death
            }
        }
    }
}

void winRandomGiveaway(player &thePlayer) {
    unsigned short reward;
    int item;

    cout << "You won a random Giveaway!!!" << endl;
    if (random(0,1) > 0.5) {
        reward = ceil(random(20, 5000));
        cout << "You've received " << reward << "$!" << endl;

    }
    else {
        reward = get<int>(randomElement(vector<int>{1,2,3},vector<double>{20, 10, 2}));
        switch (reward) {
            case 1:
                cout << "You won a phone!" << endl;
                for (int checker = 0; checker < thePlayer.vItems.size(); checker++) {
                    if (thePlayer.vItems[checker].first.sItemName == "phone") {
                        thePlayer.vItems[checker].second++;
                        return;
                    }
                }
                thePlayer.vItems.push_back({{"phone", 0, true, 1}, 1});
                return;

            case 2:
                cout << "You won a VR-headset!" << endl;
                item = checkForItem(thePlayer, "VR-headset");
                if (item >= 0) {
                    thePlayer.vItems[item].second++;
                    return;
                }

                thePlayer.vItems.push_back({{"VR-headset", 0, true, 3}, 1});
                return;
            case 3:
                cout << "You won a car!" << endl;
                item = checkForItem(thePlayer, "car");
                if (item >= 0) {
                    thePlayer.vItems[item].second++;
                    return;
                }

                thePlayer.vItems.push_back({{"car", 0, true, 1}, 1});


        }
    }
}