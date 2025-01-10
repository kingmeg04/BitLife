#include "UI/UIManager.h"
#include "UniversalStuff/TimeStuff.h"
using namespace std;

int main() {
    bool running;
    int maxActions;

    while (true) {
        string input;

        int actions = 0;


        bool playerKnown = false;
        bool renewActions = false;
        UIManager uiManager;

        int startDate = round(random(0,3600000));
        TimeManager timeManager({startDate});

        running = uiManager.start();


        while (running) {
            if (renewActions) {
                actions = 0;
                if (timeManager.iDay - startDate >= 9000) {
                    actions = 10;
                }
                else if (timeManager.iDay - startDate >= 6480) {
                    actions = 7;
                }
                else if (timeManager.iDay - startDate >= 4320) {
                    actions = 5;
                }
                else {
                    actions = 3;
                }
                if (uiManager.pCurrentPlayer != nullptr && timeManager.iDay - startDate >= 2160) {
                    actions += ceil(uiManager.pCurrentPlayer->mentalHealth / 20);
                }

                maxActions = actions;
                renewActions = false;
            }

            if (uiManager.pCurrentPlayer != nullptr && !playerKnown) {
                playerKnown = true;
            }

            //clear screen
            system("cls");

            // Display sidebar
            cout << "==== MAIN MENU ====\n";
            for (int i = 0; i <= 2; i++) {
                if (i == uiManager.currentSidebarSelection) {
                    cout << "> " << uiManager.sidebarOptions[i] << "\n";
                } else {
                    cout << "  " << uiManager.sidebarOptions[i] << "\n";
                }
            }

            if (uiManager.pCurrentPlayer != nullptr) {
                cout << "==== GAME MENU ====\n";
                if (3 == uiManager.currentSidebarSelection) {
                    cout << "> " << uiManager.sidebarOptions[3] << "\n";
                } else {
                    cout << "  " << uiManager.sidebarOptions[3] << "\n";
                }

                if (timeManager.iDay - startDate >= 2160) {
                    if (4 == uiManager.currentSidebarSelection) {
                        cout << "> " << uiManager.sidebarOptions[4] << "\n";
                    } else {
                        cout << "  " << uiManager.sidebarOptions[4] << "\n";
                    }
                }

                if (timeManager.iDay - startDate >= 4320) {
                    for (int i = 5; i <= 6; i++) {
                        if (i == uiManager.currentSidebarSelection) {
                            cout << "> " << uiManager.sidebarOptions[i] << "\n";
                        } else {
                            cout << "  " << uiManager.sidebarOptions[i] << "\n";
                        }
                    }
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
                        uiManager.currentSidebarSelection = 6;
                    }
                    else if (timeManager.iDay - startDate >= 2160) {
                        uiManager.currentSidebarSelection = 4;
                    }
                    else {uiManager.currentSidebarSelection = 3;}
                }
            } else if (key == 80) { // Arrow down
                uiManager.currentSidebarSelection = (uiManager.currentSidebarSelection + 1);// % uiManager.sidebarOptions.size();
                if (uiManager.currentSidebarSelection > 2 && uiManager.pCurrentPlayer == nullptr) {
                    uiManager.currentSidebarSelection = 0;
                }
                else if (uiManager.currentSidebarSelection > 6 && timeManager.iDay - startDate >= 4320) {
                    uiManager.currentSidebarSelection = 0;
                }
                else if (uiManager.currentSidebarSelection > 4 && timeManager.iDay - startDate >= 2160 && timeManager.iDay - startDate < 4320) {
                    uiManager.currentSidebarSelection = 0;
                }
                else if (uiManager.currentSidebarSelection > 3 && timeManager.iDay - startDate < 2160){
                    uiManager.currentSidebarSelection = 0;
                }

            } else if (key == 13) { // Enter
                if (uiManager.currentSidebarSelection >= 3 && uiManager.currentSidebarSelection <= 6) {
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
                        renewActions = true;
                    break;
                    case 1: // Load Game
                        uiManager.loadGame();
                    break;
                    case 2: // Shop
                        uiManager.quitGame();
                        running = false;

                    break;
                    case 3: // jobs
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
                        }
                        else if (input == "W" || input == "w") {
                            timeManager.advanceOneTime(2);
                        }
                        else{timeManager.advanceOneTime(1);}
                        renewActions = true; //wherever advance time is used renew actions has to be set to new
                    break;
                    case 4:
                        uiManager.shopMenu(actions);
                    break;
                    case 5: // Crimes
                        uiManager.jobsMenu(actions);
                    break;
                    case 6: // Quit
                        uiManager.crimesMenu(actions);
                    break;
                    default:
                        cout << "Invalid selection!" << endl;
                }
                SkipSwitch:
            }
        }
    }

    return 0;
}

