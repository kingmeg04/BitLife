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

        int actions = 0;
        unsigned short randomEventChance = 0;

        bool playerKnown = false;
        bool newDay = false;
        UIManager uiManager;

        int startDate = round(random(0,3600000));
        TimeManager timeManager({startDate});

        running = uiManager.start();

        auto printSidebarOptions = [&](int from, int to) {
            for (int i = from; i <= to; i++) {
                if (i == uiManager.currentSidebarSelection) {
                    cout << "> " << uiManager.sidebarOptions[i] << "\n";
                } else {
                    cout << "  " << uiManager.sidebarOptions[i] << "\n";
                }
            }
        };

        auto daySkipper = [&](int daysSkipped) { // Doesn't work for some reason
            if (randomEventChance > 100) {
                randomEventChance = 100;
            }
            for (int i = 0; i < daysSkipped; i++){
                randomEventChance++;
                if (timeManager.iDay - startDate >= 4320) {
                    while (true) {
                        if (random(0, 1) > randomEventChance/100) {
                            break;
                        }
                        cout << randomEventChance << "------------------------------------------------\n";
                        randomEventChance -= 3;
                        randomEventSelector(*uiManager.pCurrentPlayer, timeManager.iDay - startDate);
                        pauseMenu();
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
                        if (itemSelect != -1) {
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
                        if (itemSelect != -1) {
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
            }
        };

        // Example usage:
        printSidebarOptions(0, 2);


        while (running) {
            if (newDay) {

                uiManager.updatePlayerStatesOnNewDay();

                actions = 0;

                if (uiManager.pCurrentPlayer != nullptr && uiManager.pCurrentPlayer->vItems.size() == 0) {
                    uiManager.pCurrentPlayer->vItems.push_back(make_pair(make_shared<car>(5, "used car", 1000, true), 1));
                    uiManager.pCurrentPlayer->vItems.push_back(make_pair(make_shared<consumable>(5, 5, "small water", 1000), 1));
                    uiManager.pCurrentPlayer->vCrimes.push_back({{500, 0.5, "shitting"},3});
                }
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
                cout << "Date: " << timeManager.getDate()[0] << "/" << timeManager.getDate()[1] << "/" << timeManager.getDate()[2] << endl;
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
                            //save game
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

                                }
                                else if (2160 - (timeManager.iDay - startDate) >= 30) {
                                    timeManager.advanceOneTime(3);
                                }
                                else if (2160 - (timeManager.iDay - startDate) > 0){
                                    timeManager.advanceOneTime(1);
                                }
                                else{break;}
                            }
                        }
                        else if (input == "Y" || input == "y" && timeManager.iDay - startDate < 4320) {
                            timeManager.advanceOneTime(4);
                        }
                        else if (input == "M" || input == "m") {
                            timeManager.advanceOneTime(3);
                            if (timeManager.iDay - startDate < 4320) {
                                break;
                            }
                            daySkipper(30);
                        }
                        else if (input == "W" || input == "w") {
                            timeManager.advanceOneTime(2);
                            if (timeManager.iDay - startDate < 4320) {
                                break;
                            }
                            daySkipper(7);
                        }
                        else {
                            timeManager.advanceOneTime(1);
                            if (timeManager.iDay - startDate < 4320) {
                                break;
                            }
                            daySkipper(1);
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

