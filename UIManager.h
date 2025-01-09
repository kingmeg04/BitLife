#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>
#include <vector>
#include "../GameStuff/ShopStuff.h"
#include "../GameStuff/GameOverStuff.h"
#include "../PlayerStuff/Money/CriminalStuff.h"
#include "../PlayerStuff/Money/JobStuff.h"
#include "../PlayerStuff/PlayerStuff.h"
#include "../UniversalStuff/TimeStuff.h"

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
