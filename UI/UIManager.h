#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>
#include <vector>
#include "../PlayerStuff/PlayerStuff.h"


class player;

class UIManager {

private:
    std::vector<std::string> sidebarOptions = {"New Game", "Load Game", "Shop", "Jobs", "Crimes", "Quit"};
    int currentSidebarSelection = 0; // Aktuelle Menüauswahl
    player* currentPlayer = nullptr;

    void newGame();
    void loadGame();
    void shopMenu();
    void jobsMenu();
    void crimesMenu();
    void quitGame();

public:
    void start(); // Startet das Hauptmenü
};

#endif //UIMANAGER_H
