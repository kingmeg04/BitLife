#include "GameStuff/RandomEventStuff.h"
#include "UI/UIManager.h"
#include "UniversalStuff/TimeStuff.h"
#include "UniversalStuff/NamingStuff.h"
using namespace std;

int main() {
    bool running;
    int maxActions;
    string data;
    array<int,2> temp;



    while (true) {
        string input;
        int numInput;
        unsigned short prevPayDay = 0;
        short jobCountdown = 0;
        int prefSItem = -1;
        int prefHItem = -1;

        int actions = 0;
        unsigned short randomEventChance = 50;

        bool playerKnown = false;
        bool newDay = false;
        UIManager uiManager;

        int startDate = round(random(0,3600000));
        TimeManager timeManager({startDate});

        running = uiManager.start();

        auto printSidebarOptions = [&](int from, int to) { // variables are passed by reference (used for uiManager for access to the player
            for (int i = from; i <= to; i++) {
                if (i == uiManager.currentSidebarSelection) {
                    cout << "> " << uiManager.sidebarOptions[i] << "\n";
                } else {
                    cout << "  " << uiManager.sidebarOptions[i] << "\n";
                }
            }
        };

        auto daySkipper = [&](int daysSkipped) { // maybe improve simulation to include action points
            randomEventChance += daysSkipped;
            if (randomEventChance > 80 || daysSkipped >= 80) {
                randomEventChance = 80;
            }
            // cap at 75 so player doesn't have to waste time by spamming through random events
            for (int i = 0; i < daysSkipped; i++){
                uiManager.updatePlayerStatesOnNewDay();

                if (timeManager.iDay - startDate >= 4320) {

                    if (random(0.5, 1) < randomEventChance/100.0) {
                        for (int temp1 = 0; temp1 < random(1,randomEventChance/20); temp1++) {
                            randomEventChance -= 3;
                            randomEventSelector(*uiManager.pCurrentPlayer, timeManager.iDay - startDate);
                            pauseMenu();
                        }
                    }
                }


                if (timeManager.iDay - startDate <= 6480) {
                    int itemSelect;
                    itemSelect = checkForItem(*uiManager.pCurrentPlayer, "hamburger");
                    if (itemSelect != -1) {
                        uiManager.pCurrentPlayer->vItems[itemSelect].second += 3;
                    }
                    else {
                        uiManager.pCurrentPlayer->vItems.push_back(make_pair(make_shared<consumable>(0, 5, "hamburger", 5), 3));
                    }
                    itemSelect = checkForItem(*uiManager.pCurrentPlayer, "large water");
                    if (itemSelect != -1) {
                        uiManager.pCurrentPlayer->vItems[itemSelect].second += 2;
                    }
                    else {
                        uiManager.pCurrentPlayer->vItems.push_back(make_pair(make_shared<consumable>(10, 0, "large water", 3), 2));
                    }

                    while (uiManager.pCurrentPlayer->saturation <= 95) {
                        itemSelect = checkForItem(*uiManager.pCurrentPlayer, "hamburger");
                        if (itemSelect == -1) {
                            break;
                        }
                        if (uiManager.pCurrentPlayer->vItems[itemSelect].second <= 0) {
                            uiManager.pCurrentPlayer->vItems.erase(uiManager.pCurrentPlayer->vItems.begin() + itemSelect);
                            break;
                        }
                        uiManager.pCurrentPlayer->vItems[itemSelect].second--;
                        uiManager.pCurrentPlayer->saturation += 5;
                    }

                    while (uiManager.pCurrentPlayer->hydration <= 90) {
                        itemSelect = checkForItem(*uiManager.pCurrentPlayer, "large water");
                        if (itemSelect == -1) {
                            break;
                        }
                        if (uiManager.pCurrentPlayer->vItems[itemSelect].second <= 0) {
                            uiManager.pCurrentPlayer->vItems.erase(uiManager.pCurrentPlayer->vItems.begin() + itemSelect);
                            break;
                        }
                        uiManager.pCurrentPlayer->vItems[itemSelect].second--;
                        uiManager.pCurrentPlayer->hydration += 10;
                    }
                }
                else if (uiManager.sFavShop.sShopName == "filler") {
                    cout << "Select your preferred store to visit, when skipping time:" << endl;
                    for (int temp1 = 0; temp1 < uiManager.vShops.size(); temp1++) {
                        cout << "[" << temp1 + 1 << "] " << uiManager.vShops[temp1].sShopName << endl;
                    }

                    cin >> numInput;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        input = -1;
                    }
                    cout << endl;

                    while (true) {

                        numInput--;
                        if (numInput >= 0 && numInput < uiManager.vShops.size()) {
                            break;
                        }
                        cout << "Invalid input, try again";
                        cin >> numInput;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            input = -1;
                        }
                        cout << endl;
                    }
                    uiManager.sFavShop = uiManager.vShops[numInput];
                }

                if (timeManager.iDay - startDate >= 6480) {
                    int itemSelect;

                    if (prefSItem <= -1) { //set the preferred saturation item using favorite shop
                        setPrefSItem:
                        prefSItem = 0;
                        itemSelect = 0; // used as a temporary variable
                        for (int findPrefSItem = 0; findPrefSItem < uiManager.sFavShop.vAvailableItems.size(); findPrefSItem++) {
                            if (shared_ptr<consumable> foodItem1 = static_pointer_cast<consumable>(uiManager.sFavShop.vAvailableItems[findPrefSItem])){
                                if (shared_ptr<consumable> fooditem2 = static_pointer_cast<consumable>(uiManager.sFavShop.vAvailableItems[prefSItem])) {
                                    if (foodItem1->itemType == 1 && fooditem2->itemType == 1){
                                        itemSelect = 1;
                                        if (foodItem1->iSaturationInfluence/foodItem1->iPrice > fooditem2->iSaturationInfluence/fooditem2->iPrice) {
                                            prefSItem = findPrefSItem;

                                        }
                                    }
                                }
                            }
                        }
                        if (itemSelect == 0) {
                            cout << "You need to choose a different preferred store, because the one you chose doesn't have any consumables" << endl;
                            for (int temp1 = 0; temp1 < uiManager.vShops.size(); temp1++) {
                                cout << "[" << temp1 << "] " << uiManager.vShops[temp1].sShopName << endl;
                            }

                            cin >> numInput;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                input = -1;
                            }
                            cout << endl;

                            while (true) {
                                numInput = numInput - 1;
                                if (numInput >= 0 && numInput < uiManager.vShops.size()) {
                                    break;
                                }
                                cout << "Invalid Input, try again";
                                cin >> numInput;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    input = -1;
                                }
                                cout << endl;
                            }
                            uiManager.sFavShop = uiManager.vShops[numInput];
                            goto setPrefSItem;
                        }
                    }

                    if (prefHItem <= -1) { //set the preferred drinking item using favorite shop
                        prefHItem = 0;
                        itemSelect = 0; // used as a temporary variable
                        for (int findPrefHItem = 0; findPrefHItem < uiManager.sFavShop.vAvailableItems.size(); findPrefHItem++) {
                            if (shared_ptr<consumable> drinkItem1 = static_pointer_cast<consumable>(uiManager.sFavShop.vAvailableItems[findPrefHItem])){
                                if (shared_ptr<consumable> drinkitem2 = static_pointer_cast<consumable>(uiManager.sFavShop.vAvailableItems[prefHItem])) {
                                    if (drinkItem1->itemType == 1 && drinkitem2->itemType == 1){
                                        itemSelect = 1;
                                        if (drinkItem1->iHydrationInfluence/drinkItem1->iPrice > drinkitem2->iHydrationInfluence/drinkitem2->iPrice) {
                                            prefHItem = findPrefHItem;
                                        }
                                    }
                                }
                            }
                        }

                        if (itemSelect == 0) {
                            cout << "You need to choose a different preferred store, because the one you chose doesn't have any consumables" << endl;
                            for (int temp1 = 0; temp1 < uiManager.vShops.size(); temp1++) {
                                cout << "[" << temp1 << "] " << uiManager.vShops[temp1].sShopName << endl;
                            }
                            cin >> numInput;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                input = -1;
                            }
                            cout << endl;

                            while (true) {
                                numInput = numInput - 1;
                                if (numInput >= 0 && numInput < uiManager.vShops.size()) {
                                    break;
                                }
                                cout << "Invalid Input, try again";
                                cin >> numInput;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    input = -1;
                                }
                                cout << endl;
                            }
                            uiManager.sFavShop = uiManager.vShops[numInput];
                            goto setPrefSItem;
                        }
                    }

                    for (int foodItemCheck = 0; foodItemCheck < uiManager.pCurrentPlayer->vItems.size(); foodItemCheck++) { // check if the player has any food item in his inventory and eat it
                        if (shared_ptr<consumable> foodItem = static_pointer_cast<consumable>(uiManager.pCurrentPlayer->vItems[foodItemCheck].first)) {
                            if (foodItem->itemType == 1 && foodItem->iSaturationInfluence > 0) {
                                if (uiManager.pCurrentPlayer->saturation < 100) {
                                    uiManager.pCurrentPlayer->saturation += foodItem->iSaturationInfluence;
                                    uiManager.pCurrentPlayer->vItems[foodItemCheck].second--;
                                    if (uiManager.pCurrentPlayer->vItems[foodItemCheck].second <= 0) {
                                        uiManager.pCurrentPlayer->vItems.erase(uiManager.pCurrentPlayer->vItems.begin() + foodItemCheck);
                                    }
                                }
                            }
                        }
                    }
                    for (int drinkItemCheck = 0; drinkItemCheck < uiManager.pCurrentPlayer->vItems.size(); drinkItemCheck++) { // check if the player has any food item in his inventory and eat it
                        if (shared_ptr<consumable> drinkItem = static_pointer_cast<consumable>(uiManager.pCurrentPlayer->vItems[drinkItemCheck].first)) {
                            if (drinkItem->itemType == 1 && drinkItem->iHydrationInfluence > 0) {
                                if (uiManager.pCurrentPlayer->hydration < 100) {
                                    uiManager.pCurrentPlayer->hydration += drinkItem->iHydrationInfluence;
                                    uiManager.pCurrentPlayer->vItems[drinkItemCheck].second--;
                                    if (uiManager.pCurrentPlayer->vItems[drinkItemCheck].second <= 0) {
                                        uiManager.pCurrentPlayer->vItems.erase(uiManager.pCurrentPlayer->vItems.begin() + drinkItemCheck);
                                    }
                                }
                            }
                        }
                    }

                    while (uiManager.pCurrentPlayer->balance >= uiManager.sFavShop.vAvailableItems[prefSItem]->iPrice && uiManager.pCurrentPlayer->saturation < 100) {
                        uiManager.pCurrentPlayer->balance -= uiManager.sFavShop.vAvailableItems[prefSItem]->iPrice;
                        uiManager.pCurrentPlayer->saturation += static_pointer_cast<consumable>(uiManager.sFavShop.vAvailableItems[prefSItem])->iSaturationInfluence;
                    }

                    while (uiManager.pCurrentPlayer->balance >= uiManager.sFavShop.vAvailableItems[prefHItem]->iPrice && uiManager.pCurrentPlayer->hydration < 100) {
                        uiManager.pCurrentPlayer->balance -= uiManager.sFavShop.vAvailableItems[prefHItem]->iPrice;
                        uiManager.pCurrentPlayer->hydration += static_pointer_cast<consumable>(uiManager.sFavShop.vAvailableItems[prefHItem])->iHydrationInfluence;
                    }

                }
                if (uiManager.pCurrentPlayer->jCurrentJob.sName != "child") {
                    if (daysSkipped >= 7) {
                        uiManager.pCurrentPlayer->balance += daysSkipped/7 * uiManager.pCurrentPlayer->jCurrentJob.sSalary;
                        prevPayDay = timeManager.iDay;
                    }
                }
            }
            newDay = true;
        };


        printSidebarOptions(0, 2);


        while (running) {
            if (newDay) {

                if (uiManager.pCurrentPlayer->jCurrentJob.sName != "child") {
                    prevPayDay = timeManager.iDay;
                }
                if (timeManager.iDay - prevPayDay >= 7) { // getting paid
                    prevPayDay = timeManager.iDay;
                    while (prevPayDay % 7 != 5) {
                        prevPayDay--;
                    }

                    if (uiManager.pCurrentPlayer->jCurrentJob.sName == "workless") {
                        if (jobCountdown <= 0) {
                            for (int prevJob = 0; prevJob < uiManager.pCurrentPlayer->vPrevJobs.size(); prevJob++) {
                                if (uiManager.pCurrentPlayer->vPrevJobs[prevJob].sName == uiManager.pCurrentPlayer->jCurrentJob.sName) {
                                    uiManager.pCurrentPlayer->vPrevJobs.erase(uiManager.pCurrentPlayer->vPrevJobs.begin() + prevJob);
                                    break;
                                }
                            }
                            uiManager.pCurrentPlayer->vPrevJobs.push_back(uiManager.pCurrentPlayer->jCurrentJob);
                            uiManager.pCurrentPlayer->jCurrentJob = getJobVector()[7];

                            uiManager.pCurrentPlayer->jCurrentJob.sName = "workless";
                            cout << "You don't have any more benefits and are now homeless." << endl;
                        }
                        else {
                            uiManager.pCurrentPlayer->balance += uiManager.pCurrentPlayer->jCurrentJob.sSalary;
                            cout << "You won't have any benefits in " << jobCountdown << " weeks." << endl;
                        }
                    }
                    else if (timeManager.iDay - prevPayDay < 6480) {
                        uiManager.pCurrentPlayer->balance += round(uiManager.pCurrentPlayer->jCurrentJob.sSalary / 10);
                        cout << "You received: " << round(uiManager.pCurrentPlayer->jCurrentJob.sSalary/10) << "$ on pay day.";
                    }
                    else if (uiManager.fTimesWorkedThisWeek >= 4.5 || uiManager.pCurrentPlayer->jCurrentJob.bIsAdmin) {
                        uiManager.pCurrentPlayer->balance += uiManager.pCurrentPlayer->jCurrentJob.sSalary;
                        cout << "You received: " << uiManager.pCurrentPlayer->jCurrentJob.sSalary << "$ on pay day.";
                    }
                    else if (uiManager.fTimesWorkedThisWeek >= 2) {
                        cout << "You didn't receive any pay because you didn't work enough this week" << endl;
                    }
                    else {
                        for (int prevJob = 0; prevJob < uiManager.pCurrentPlayer->vPrevJobs.size(); prevJob++) {
                            if (uiManager.pCurrentPlayer->vPrevJobs[prevJob].sName == uiManager.pCurrentPlayer->jCurrentJob.sName) {
                                uiManager.pCurrentPlayer->vPrevJobs.erase(uiManager.pCurrentPlayer->vPrevJobs.begin() + prevJob);
                                break;
                            }
                        }
                        uiManager.pCurrentPlayer->vPrevJobs.push_back(uiManager.pCurrentPlayer->jCurrentJob);
                        uiManager.pCurrentPlayer->jCurrentJob = getJobVector()[9];

                        jobCountdown = round(random(4, 20));
                        cout << "You didn't work enough this week so your boss fired you." << endl;
                        cout << "You have " << jobCountdown << " weeks to find a new job." << endl;
                    }
                    pauseMenu();
                }
                actions = 0;

                /*if (uiManager.pCurrentPlayer != nullptr && uiManager.pCurrentPlayer->vItems.size() == 0) {
                    uiManager.pCurrentPlayer->vItems.push_back(make_pair(make_shared<car>(5, "used car", 1000, true), 1));
                    uiManager.pCurrentPlayer->vItems.push_back(make_pair(make_shared<consumable>(5, 5, "small water", 1000), 1));
                    uiManager.pCurrentPlayer->vCrimes.push_back({{500, 0.5, "shitting"},3});
                }*/ // only for testing
                if (uiManager.vShops.size() <= 0 && timeManager.iDay - startDate >= 2160) {
                    uiManager.vShops.push_back(generateShop({1}, 1)); // guarantee to generate at least one convenience store

                    for (int i = 0; i < round(random(0,5)); i++) {
                        uiManager.vShops.push_back(generateShop({1},7));
                    }
                }

                if (timeManager.iDay - startDate >= 9000) {
                    actions = 10;
                }
                /*else if (timeManager.iDay - startDate >= 6480) {
                    actions = 10;
                }*/
                else if (timeManager.iDay - startDate >= 4320) {
                    actions = 8;
                }
                else {
                    actions = 6;
                }
                if (uiManager.pCurrentPlayer != nullptr && timeManager.iDay - startDate >= 2160) {
                    actions += ceil(uiManager.pCurrentPlayer->mentalHealth / 20);
                }

                for (int i = 0; i < uiManager.pCurrentPlayer->vItems.size(); i++) {
                    if (shared_ptr<car> carItem = static_pointer_cast<car>(uiManager.pCurrentPlayer->vItems[i].first)) {
                        if (carItem->itemType == 2) {
                            actions += carItem->iActionsGained;
                        }

                    }
                }

                maxActions = actions;
                uiManager.saveGame(startDate, timeManager.iDay);
                newDay = false;

            }

            if (uiManager.pCurrentPlayer != nullptr && !playerKnown) {
                playerKnown = true;
            }

            //clear screen
            system("cls");

            // Display sidebar
            cout << "==== MAIN MENU ====\n";

            printSidebarOptions(0, 2);

            if (uiManager.pCurrentPlayer != nullptr) {
                cout << "==== GAME MENU ====\n";
                printSidebarOptions(3, 4);

                if (timeManager.iDay - startDate >= 2160) {
                    printSidebarOptions(5,5);
                }

                if (timeManager.iDay - startDate >= 4320) {
                    printSidebarOptions(6,7);
                }
            }
            cout << "===================\n";

            if (uiManager.pCurrentPlayer != nullptr) {
                cout << "Date: " << timeManager.getDate()[0] << "/" << timeManager.getDate()[1] << "/" << timeManager.getDate()[2] << " - ";
                switch (timeManager.iDay % 7) {
                    case 0: cout << "Monday"; break;
                    case 1: cout << "Tuesday"; break;
                    case 2: cout << "Wednesday"; break;
                    case 3: cout << "Thursday"; break;
                    case 4: cout << "Friday"; break;
                    case 5: cout << "Saturday"; break;
                    case 6: cout << "Sunday"; break;
                }
                cout << endl;
                cout << "------------------\n";
                cout << "Name: " << uiManager.pCurrentPlayer->sPlayerName << endl;
                cout << "Age: " << floor((timeManager.iDay - startDate)/360) << endl;
                cout << "Health: " << uiManager.pCurrentPlayer->playerHealth << endl;
                cout << "Saturation: " << uiManager.pCurrentPlayer->saturation << endl;
                cout << "Hydration: " << uiManager.pCurrentPlayer->hydration << endl;
                if (timeManager.iDay - startDate >= 2160) {
                    cout << "Mental stability: " << uiManager.pCurrentPlayer->mentalHealth << endl;
                }
                cout << "Money: " << uiManager.pCurrentPlayer->balance << "$" << endl;
                cout << "------------------\n";
                cout << "Actions: " << actions << "/" << maxActions << endl;
            }

            if (timeManager.iDay - startDate >= 6480 && uiManager.sFavShop.sShopName == "filler") {
                cout << "Note: You'll need to set your favorite shop this round" << endl;
            }

            // Handle input
            char key = _getch();
            if (key == 72) { // Arrow up
                uiManager.currentSidebarSelection = uiManager.currentSidebarSelection - 1; // + uiManager.sidebarOptions.size()) % uiManager.sidebarOptions.size();
                if (uiManager.currentSidebarSelection < 0) {
                    if (uiManager.pCurrentPlayer == nullptr) {
                        uiManager.currentSidebarSelection = 2;
                    }
                    else if (timeManager.iDay - startDate >= 4320) {
                        uiManager.currentSidebarSelection = 7;
                    }
                    else if (timeManager.iDay - startDate >= 2160) {
                        uiManager.currentSidebarSelection = 5;
                    }
                    else {uiManager.currentSidebarSelection = 4;}
                }
            } else if (key == 80) { // Arrow down
                uiManager.currentSidebarSelection = (uiManager.currentSidebarSelection + 1);// % uiManager.sidebarOptions.size();
                if (uiManager.currentSidebarSelection > 2 && uiManager.pCurrentPlayer == nullptr) {
                    uiManager.currentSidebarSelection = 0;
                }
                else if (uiManager.currentSidebarSelection > 7 && timeManager.iDay - startDate >= 4320) {
                    uiManager.currentSidebarSelection = 0;
                }
                else if (uiManager.currentSidebarSelection > 5 && timeManager.iDay - startDate >= 2160 && timeManager.iDay - startDate < 4320) {
                    uiManager.currentSidebarSelection = 0;
                }
                else if (uiManager.currentSidebarSelection > 4 && timeManager.iDay - startDate < 2160){
                    uiManager.currentSidebarSelection = 0;
                }

            } else if (key == 13) { // Enter
                if (uiManager.currentSidebarSelection >= 5 && uiManager.currentSidebarSelection <= 7) {
                    if (actions <= 0) {
                        cout << "You don't have enough remaining actions!" << endl;
                        pauseMenu();
                        goto SkipSwitch;
                    }
                }
                switch (uiManager.currentSidebarSelection) {
                    case 0: // New Game
                        if (uiManager.pCurrentPlayer != nullptr) {
                            running = false;
                            uiManager.saveGame(startDate, timeManager.iDay);
                            uiManager.pCurrentPlayer == nullptr;
                            break;
                        }
                        uiManager.newGame();
                        newDay = true;
                    break;
                    case 1: // Load Game
                        temp = uiManager.loadGame();
                        timeManager.iDay = temp[0];
                        startDate = temp[1];
                        newDay = true;
                        prefSItem = -1;
                        prefHItem = -1;
                        pauseMenu();
                    break;
                    case 2: // Shop
                        uiManager.quitGame();
                        running = false;

                    break;
                    case 3: // timeskip
                        newDay = true; //wherever advance time is used renew actions has to be set to new
                        cout << "How much time do you want to skip? (D/W/M";
                        if (timeManager.iDay - startDate < 4320) {
                            cout << "/Y";
                        }
                        if (timeManager.iDay - startDate < 2160) {
                            cout << "/Y6";
                        }
                        cout << ")" << endl;
                        cin >> input;
                        cout << endl;
                        if ((input == "Y6" || input == "y6" || input == "6") && timeManager.iDay - startDate < 2160) {
                            while (true) {
                                if (2160 - (timeManager.iDay - startDate) >= 360) {
                                    timeManager.advanceOneTime(4);
                                    daySkipper(360);
                                }
                                else if (2160 - (timeManager.iDay - startDate) >= 30) {
                                    timeManager.advanceOneTime(3);
                                    daySkipper(30);
                                }

                                else if (2160 - (timeManager.iDay - startDate) > 0){
                                    timeManager.advanceOneTime(1);
                                    daySkipper(1);
                                }
                                else{break;}
                            }
                        }
                        else if (input == "Y" || input == "y" && timeManager.iDay - startDate < 4320) {
                            timeManager.advanceOneTime(4);
                            daySkipper(360);
                        }
                        else if (input == "M" || input == "m") {
                            timeManager.advanceOneTime(3);
                            daySkipper(30);
                            if (timeManager.iDay - startDate < 4320) {
                                break;
                            }

                        }
                        else if (input == "W" || input == "w") {
                            timeManager.advanceOneTime(2);
                            daySkipper(7);
                            if (timeManager.iDay - startDate < 4320) {
                                break;
                            }

                        }
                        else {
                            timeManager.advanceOneTime(1);
                            daySkipper(1);
                            if (timeManager.iDay - startDate < 4320) {
                                break;
                            }
                        }


                    break;
                    case 4: // Inventory
                        uiManager.inventory(actions);
                    break;
                    case 5: // Shop
                        uiManager.shopMenu(actions);
                    break;
                    case 6: // Jobs
                        uiManager.jobsMenu(actions);
                    break;
                    case 7: // Crimes
                        uiManager.crimesMenu(actions);
                    default:
                        cout << "Invalid selection!" << endl;
                }
                SkipSwitch:
            }
        }
    }

    return 0;
}

