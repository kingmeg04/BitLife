#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h> // For _getch()
#include <thread>
#include <chrono>
#include <fstream> // Credit here goes to app on Jeremy's phone for containing an advanced c++ course which included reading and saving files
#include <filesystem>
#include <shlobj.h>

#include "../PlayerStuff/PlayerStuff.h"


class player;

class UIManager {
public:

    std::vector<shop> vShops;
    float fTimesWorkedThisWeek = 0;
    shop sFavShop = {"filler",500,{}};
    std::vector<std::string> sidebarOptions = {"New Game", "Load Game", "Quit", "Timeskip", "Inventory", "Shop", "Jobs", "Crimes"}; //

    int currentSidebarSelection = 0; // Aktuelle Menüauswahl
    player *pCurrentPlayer = nullptr;

    void setPlayer(player& player) {
        this->pCurrentPlayer = &player;
    }

    void newGame();
    std::array<int,2> loadGame();
    void inventory(int &actions);
    void shopMenu(int &actions);
    void jobsMenu(int &actions);
    void crimesMenu(int &actions);
    void quitGame();
    void updatePlayerStatesOnNewDay(); // OH NO - A TYPO. Well- it is what it is now ig...

    void saveGame(int startDate, int endDate);

    bool start(); // called to start the programm

};


void pauseMenu(const std::string& message = "Press any key to continue...");
#endif //UIMANAGER_H
