#include "UIManager.h"
#include <iostream>
#include <conio.h> // For _getch()
#include <thread>
#include <chrono>

using namespace std;

void pauseMenu(const string& message = "Press any key to continue...") {
    cout << endl << message << endl;
    _getch(); // Wait for any key press
}

void UIManager::start() {
    bool running = true;

    while (running) {
        // Clear screen
        system("cls");

        // Display sidebar
        cout << "==== MAIN MENU ====\n";
        for (size_t i = 0; i < sidebarOptions.size(); i++) {
            if (i == currentSidebarSelection) {
                cout << "> " << sidebarOptions[i] << "\n";
            } else {
                cout << "  " << sidebarOptions[i] << "\n";
            }
        }
        cout << "===================\n";

        // Handle input
        char key = _getch();
        if (key == 72) { // Arrow up
            currentSidebarSelection = (currentSidebarSelection - 1 + sidebarOptions.size()) % sidebarOptions.size();
        } else if (key == 80) { // Arrow down
            currentSidebarSelection = (currentSidebarSelection + 1) % sidebarOptions.size();
        } else if (key == 13) { // Enter
            switch (currentSidebarSelection) {
                case 0: // New Game
                    newGame();
                    break;
                case 1: // Load Game
                    loadGame();
                    break;
                case 2: // Shop
                    shopMenu();
                    break;
                case 3: // Jobs
                    jobsMenu();
                    break;
                case 4: // Crimes
                    crimesMenu();
                    break;
                case 5: // Quit
                    quitGame();
                    running = false;
                    break;
                default:
                    cout << "Invalid selection!" << endl;
            }
        }
    }
}

void UIManager::newGame() {
    cout << "Starting a new game...\n";
    currentPlayer = new player(job(500, 50, "Unemployed"));
    cout << "New game started successfully!" << endl;
    pauseMenu();
}

void UIManager::loadGame() {
    cout << "Load Game is not implemented yet.\n";
    pauseMenu();
}

void UIManager::shopMenu() {
    if (!currentPlayer) {
        cout << "Start a new game first!\n";
        pauseMenu();
        return;
    }

    shop gameShop("General Store", {
        item("Bread", 10, 0, 20),
        item("Medicine", 50, 30, 0),
        item("Energy Drink", 20, -10, 15)
    });

    gameShop.openShop(*currentPlayer);
    pauseMenu();
}

void UIManager::jobsMenu() {
    if (!currentPlayer) {
        cout << "Start a new game first!\n";
        pauseMenu();
        return;
    }

    cout << "Current job: " << currentPlayer->jCurrentJob.sName
         << " (" << currentPlayer->jCurrentJob.sSalary << "$ per week)\n";

    job newJob = getRandomJob();
    currentPlayer->newJob(newJob);

    cout << "New job acquired: " << newJob.sName
         << " with a salary of " << newJob.sSalary << "$ per week.\n";
    pauseMenu();
}

void UIManager::crimesMenu() {
    if (!currentPlayer) {
        cout << "Start a new game first!\n";
        pauseMenu();
        return;
    }

    array<Crime, 6> crimesArray = {
        Crime{50, 0.2, "Shoplifting", 0},
        Crime{200, 0.5, "Fraud", 0},
        Crime{700, 0.8, "Arson", 0},
        Crime{1000, 0.9, "Robbery", 0},
        Crime{50, 0.3, "Pickpocketing", 0},
        Crime{500, 0.6, "Burglary", 0}
    };

    cout << "Attempting a crime..." << endl;
    prisonCharge(crimesArray, crimesArray[0], 1000);
    pauseMenu();
}

void UIManager::quitGame() {
    cout << "Quitting game...\n";
    pauseMenu("Press any key to exit...");
    exit(0);
}
