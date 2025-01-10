#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <conio.h> // For _getch()
#include <thread>
#include <chrono>
#include "../PlayerStuff/PlayerStuff.h"


class player;

class UIManager {
public:

    std::vector<std::string> sidebarOptions = {"New Game", "Load Game", "Quit", "Timeskip", "Shop", "Jobs", "Crimes"}; //

    int currentSidebarSelection = 0; // Aktuelle Menüauswahl
    player *pCurrentPlayer = nullptr;

    void setPlayer(player& player) {
        this->pCurrentPlayer = &player;
    }

    void newGame();
    void loadGame();
    void shopMenu(int &actions);
    void jobsMenu(int &actions);
    void crimesMenu(int &actions);
    void quitGame();

    bool start(); // called to start the programm
};

void pauseMenu(const std::string& message = "Press any key to continue...");
#endif //UIMANAGER_H
