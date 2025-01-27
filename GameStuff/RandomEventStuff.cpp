//
// Created by kingm on 07/01/2025.
//

#include "RandomEventStuff.h"

using namespace std;
int currentItem;

int randomEventSelector(player &thePlayer, int currentDay) {

    int dateChance;
    int prankChance;
    int investigationChance;
    int giveawayChance;
    int NDChance;
    int donationChance;
    int adminChance;
    int bananaChance;
    int crimeChance;
    int EDIPSChance;
    int CinSCChance;

    if (thePlayer.iJailTime <= 0) {
        dateChance = 50;
        if (checkForItem(thePlayer, "partner") >= 0) {
            dateChance = 5;
        }
        prankChance = 5 * thePlayer.sCriminalReputation / 2;
        investigationChance = 25;
        giveawayChance = 5;
        NDChance = 5;
        donationChance = thePlayer.balance/1000;
        if (donationChance > 250) {
            donationChance = 250;
        }
        adminChance = 1;
        bananaChance = 10;
        crimeChance = thePlayer.sCriminalReputation * 5;
        EDIPSChance = 1;
        CinSCChance = 10;


    }
    else {
        dateChance = 0;
        prankChance = 0;
        investigationChance = 250;
        giveawayChance = 0;
        NDChance = 25;
        donationChance = thePlayer.balance/1000;
        if (donationChance > 250) {
            donationChance = 50;
        }
        adminChance = 1;
        bananaChance = 25;
        crimeChance = 0;
        EDIPSChance = 1;
        CinSCChance = 0;
    }

    int chosenEvent = get<int>(randomElement(vector<int>{1,2,3,4,5,6,7,8,9,10,11}, vector<int>{dateChance, prankChance, investigationChance, giveawayChance, NDChance, donationChance, adminChance, bananaChance, crimeChance, EDIPSChance, CinSCChance}));
    switch (chosenEvent) {
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
        case 5:
            naturalDisaster(thePlayer);
        break;
        case 6:
            makeDonation(thePlayer);
        break;
        case 7:
            becomeAdmin(thePlayer);
        break;
        case 8:
            slipOnBananaPeal(thePlayer);
        break;
        case 9:
            askedToCommitCrime(thePlayer);
        break;
        case 10:
            explosiveDiarrheaInPublicSpace(thePlayer);
        break;
        case 11:
            getCaughtInStripclubByMedia(thePlayer);
        break;
    }
    return chosenEvent;
}

void dating(player &thePlayer) {
    string option;

    if (random(0,1) > 0.5) {
        cout << "Do you want to ask someone out on a date(Y/N): ";
        cin >> option;
        cout << endl;
        if (option == "Y" && option == "y") {
            if (random(0,1) > 0.25) {
                cout << "They said yes." << endl;
                currentItem = checkForItem(thePlayer, "partner");
                if (currentItem >= 0) {
                    thePlayer.vItems[currentItem].second++;
                    cout << "You now have " << thePlayer.vItems[currentItem].second << " partners." << endl;
                    return;
                }
                cout << "You now have a partner." << endl;
                thePlayer.vItems.push_back(make_pair(make_shared<item>("partner", 0, true, 5), 1));
            }
            else {
                cout << "You were rejected." << endl;
                thePlayer.mentalHealth -= floor(round(random(0,15)));
            }
        }
        else{
            return;
        }
    }
    else {
        cout << "Someone asked you out on a date." << endl;
        cout << "How do you respond (Y/N): " << endl;
        cin >> option;
        cout << endl;
        if (option == "Y" || option == "y") {
            currentItem = checkForItem(thePlayer, "partner");
            if (currentItem >= 0) {
                thePlayer.vItems[currentItem].second++;
                cout << "You now have " << thePlayer.vItems[currentItem].second << " partners." << endl;
                return;
            }
            cout << "You now have a partner." << endl;
            thePlayer.vItems.push_back(make_pair(make_shared<item>("partner", 0, true, 5), 1));

        }
        else {
            cout << "You rejected them." << endl;
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
            int payCut = ceil(random(thePlayer.jCurrentJob.sSalary / 100, thePlayer.jCurrentJob.sSalary / 75));
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
                thePlayer.sCriminalReputation += floor(random(0, 5));
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

        if (thePlayer.sCriminalReputation >= 50) {
            thePlayer.sCriminalReputation += floor(random(0, 5));
            reward = ceil(random(100,2500));
            cout << "The homies respect your decision and give you a reward of " << reward << "$ for your action." << endl;
            return;
        }
        thePlayer.sCriminalReputation += floor(random(10, 20));
    }
    else {
        thePlayer.sCriminalReputation += floor(random(0, 5));
        cout << "The police thanks you for your honesty" << endl;
        if (thePlayer.sCriminalReputation >= 50) {
            cout << "The homies feel betrayed and beat you up." << endl;
            thePlayer.playerHealth -= floor(random(5,25));
            if (thePlayer.playerHealth <= 0) {
                // deathEvent() cause: is beaten to death
            }
        }
    }
}

void winRandomGiveaway(player &thePlayer) {
    unsigned short reward;

    cout << "You won a random Giveaway!!!" << endl;
    if (random(0,1) > 0.5) {
        reward = ceil(random(20, 5000));
        cout << "You've received " << reward << "$!" << endl;
        thePlayer.balance += reward;
    }
    else {
        reward = get<int>(randomElement(vector<int>{1,2,3},vector<int>{20, 10, 2}));
        switch (reward) {
            case 1:
                cout << "You won a phone!" << endl;
                currentItem = checkForItem(thePlayer, "phone");
                if (currentItem >= 0) {
                    thePlayer.vItems[currentItem].second++;
                    cout << "You now have " << thePlayer.vItems[currentItem].second << " phones." << endl;
                    return;
                }
                thePlayer.vItems.push_back(make_pair(make_shared<item>("phone", 1000, true, 2), 1));
                return;

            case 2:
                cout << "You won a VR-headset!" << endl;
                currentItem = checkForItem(thePlayer, "VR-headset");
                if (currentItem >= 0) {
                    thePlayer.vItems[currentItem].second++;
                    cout << "You now have " << thePlayer.vItems[currentItem].second << " VR-headsets." << endl;
                    return;
                }

                thePlayer.vItems.push_back(make_pair(make_shared<item>("VR-headset", 1500, true, 5), 1));
                return;
            case 3:
                cout << "You won a sports car!" << endl;
                currentItem = checkForItem(thePlayer, "sports car");
                if (currentItem >= 0) {
                    thePlayer.vItems[currentItem].second++;
                    cout << "You now have " << thePlayer.vItems[currentItem].second << "sport cars." << endl;
                    return;
                }

                thePlayer.vItems.push_back(make_pair(make_shared<item>("sports car", 100000, true, 3), 1));
        }
    }
}

void naturalDisaster(player &thePlayer) {
    string input;
    cout << "There was a natural disaster!" << endl;
    if (thePlayer.iJailTime > 0) {
        cout << "There was a natural disaster!" << endl;
        cout << "Do you want to use the chance to escape (Y/N):";
        cin >> input;
        cout << endl;
        if (input == "Y" || input == "y") {
            if (round(random(0,5) > 4)){
                cout << "You escaped successfully and are free!" << endl;
                thePlayer.iJailTime = 0;
                thePlayer.vCrimes.push_back({{5, 0.2, "escpaping prison"}, 5});
            }
            else {
                cout << "You were caught by a warden and now need to spend an additional 100 days in prison" << endl;
                thePlayer.iJailTime += 100;
            }
        }
        else {
            cout << "You didn't escape and were rewarded with a reduction of your sentance by 50 days." << endl;
            thePlayer.iJailTime -= 50;
            thePlayer.mentalHealth += 10;
        }
    }
    else {
        for (int currentItem = 0; currentItem < thePlayer.vItems.size(); currentItem++) {
            if (shared_ptr<house> savingItem = static_pointer_cast<house>(thePlayer.vItems[currentItem].first)) {
                if (savingItem->itemType == 3) {
                    if (random(1,1000) > savingItem->iStrength) {
                        cout << "Your house got destroyed!" << endl;
                        thePlayer.vItems[currentItem].second--;
                    }
                }
            }
        }
    }
};

void makeDonation(player &thePlayer) {
    string strAnswer;
    cout << "Do you want to do a donation (Y/N)" << endl;
    cin >> strAnswer;
    if (strAnswer == "Y" || strAnswer == "y") {
        getIDonation:
        int iDonation;
        cout << "How much do you want to donate?" << endl;
        cin >> iDonation;
        if (cin.fail() || iDonation < 1) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input, try again" << endl;
            goto getIDonation;
        }

        cout << "Thanks for donating" << iDonation << endl;
        thePlayer.balance -= iDonation;

        if (thePlayer.iJailTime <= 0) {
            cout << "As a reward for donating your time will be reduced by " << iDonation/500 << " days." << endl;
        }
    }
    else {
        cout << "You are very selfish and lost 5 Mental Health." << endl;
        thePlayer.balance -= 5;
    }
};

void becomeAdmin(player &thePlayer) {
    int iAddition;
    iAddition = round(random(100,5000));
    thePlayer.jCurrentJob.bIsAdmin = true;
    thePlayer.jCurrentJob.sSalary += iAddition;
    cout << "Congratulations to your promotion!, you now make" << iAddition << "$ more" << endl;
};

void slipOnBananaPeal(player &thePlayer) {
    int iDamage;
    iDamage = round(random(5,20));
    cout << "You have slipped on a banana!" << endl;
    thePlayer.playerHealth -= iDamage;
    cout << "You took" << iDamage << "of damage" << endl;
}

void askedToCommitCrime(player &thePlayer) {
    cout << "Do you want to commit a crime with other people (Y/N)?" << endl;
    string iAnswer;
    cin >> iAnswer;
    cout << endl;

    bool found = false;
    if (iAnswer == "Y" || iAnswer == "y") {
        for (int crimeFinder = 0; crimeFinder < thePlayer.vCrimes.size(); crimeFinder++) {
            if ("Illegal planning" == thePlayer.vCrimes[crimeFinder].first.sName) {
                thePlayer.vCrimes[crimeFinder].second++;
                found = true;
                break;
            }
        }
        if (!found) {
            thePlayer.vCrimes.push_back({{500,0.2,"Illegal planning"}, 1});
        }
        int option = round(random(1,3));
        if (option == 1) {
            cout << "Unfortunately they didn't want to commit a crime" << endl;
            thePlayer.sCriminalReputation += round(random(5,10));
        }
        else if (option == 2) {
            cout << "Unfortunately they snitched on you for planning a robbery" << endl;
            thePlayer.sCriminalReputation += round(random(10,20));
            prisonCharge(thePlayer, {500,0.2,"Illegal planning"});
        }
        else {
            cout << "They accepted to join you on your crime" << endl;
            thePlayer.sCriminalReputation += round(random(10,30));
            cout << "You robbed a bank and gained 5000$" << endl;
            thePlayer.balance += 5000;
        }
    }
};

void explosiveDiarrheaInPublicSpace(player &thePlayer) {
    cout << "You had explosive diarrhea in public space!" << endl;
    int iFine;
    iFine = round(random(50,200));
    thePlayer.vCrimes.push_back({{100,1,"explosive diarrhea in public space"}, 1});
    prisonCharge(thePlayer, {100,1,"explosive diarrhea in public space"});
    thePlayer.balance -= iFine;
};

void getCaughtInStripclubByMedia(player &thePlayer) {
    cout << "The media caught you spending time in a strip club" << endl;
    if (thePlayer.jCurrentJob.sName == "politician" || thePlayer.jCurrentJob.sName == "mayor" || thePlayer.jCurrentJob.sName == "prime minister") {
        cout << "You lost your job as a " << thePlayer.jCurrentJob.sName << " and are now homeless." << endl;
        for (int prevJob = 0; prevJob < thePlayer.vPrevJobs.size(); prevJob++) {
            if (thePlayer.vPrevJobs[prevJob].sName == thePlayer.jCurrentJob.sName) {
                thePlayer.vPrevJobs.erase(thePlayer.vPrevJobs.begin() + prevJob);
                break;
            }
        }
        thePlayer.vPrevJobs.push_back(thePlayer.jCurrentJob);
        thePlayer.jCurrentJob = getJobVector()[7];
        thePlayer.mentalHealth -= 50;
    }
    else {
        if (checkForItem(thePlayer, "partner") != -1) {
            cout << "Your partner wasn't too happy and left you" << endl;
            thePlayer.vItems[checkForItem(thePlayer, "partner")].second--;
            if (thePlayer.vItems[checkForItem(thePlayer, "partner")].second <= 0) {
                thePlayer.vItems.erase(thePlayer.vItems.begin() + checkForItem(thePlayer, "partner"));
            }
            thePlayer.mentalHealth -= 10;
        }
        else {
            cout << "No one really cared and you had a good time." << endl;
            thePlayer.mentalHealth += 5;
        }
    }

}


