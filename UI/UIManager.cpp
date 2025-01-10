#include "UIManager.h"


using namespace std;

void pauseMenu(const string& message ) {
    cout << endl << message << endl;
    _getch(); // Wait for any key press
}

bool UIManager::start() {
    return true;
}

void UIManager::newGame() {
    string playerName;
    cout << "Starting a new game...\n";
    cout << "Please enter your charachter's name: ";
    cin >> playerName;
    cout << endl;
    pCurrentPlayer = new player(playerName,job(0, 50, "child"));
    cout << "New game started successfully!" << endl;
    pauseMenu();
}

void UIManager::loadGame() {
    cout << "Load Game is not implemented yet.\n";
    pauseMenu();
}

void UIManager::shopMenu(int &actions) {


    shop gameShop("General Store", {
        item("Bread", 10, 0, 20),
        item("Medicine", 50, 30, 0),
        item("Energy Drink", 20, -10, 15)
    });

    gameShop.openShop(*pCurrentPlayer);
    pauseMenu();
}

void UIManager::jobsMenu(int &actions) {


    cout << "Current job: " << pCurrentPlayer->jCurrentJob.sName
         << " (" << pCurrentPlayer->jCurrentJob.sSalary << "$ per week)\n";

    job newJob = getRandomJob();
    pCurrentPlayer->newJob(newJob);

    cout << "New job acquired: " << newJob.sName
         << " with a salary of " << newJob.sSalary << "$ per week.\n";
    pauseMenu();
}

void UIManager::crimesMenu(int &actions) {

    array<crime, 6> crimesArray = {
        crime{50, 0.2, "Shoplifting"},
        crime{200, 0.5, "Fraud"},
        crime{700, 0.8, "Arson"},
        crime{1000, 0.9, "Robbery"},
        crime{50, 0.3, "Pickpocketing"},
        crime{500, 0.6, "Burglary"}
    };

    cout << "Attempting a crime..." << endl;
    pCurrentPlayer->vCrimes.push_back({crimesArray[0],1});
    prisonCharge(*pCurrentPlayer, crimesArray[0]);
    pauseMenu();
}

void UIManager::quitGame() {
    cout << "Quitting game...\n";
    pauseMenu("Press any key to exit...");
    exit(0);
}
