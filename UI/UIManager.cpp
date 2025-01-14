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
    pCurrentPlayer = new player(playerName,job(0, 0, "child"));
    pCurrentPlayer->balance = 10000;
    cout << "New game started successfully!" << endl;
    pauseMenu();
}

void UIManager::loadGame() {
    fstream newFile;
    newFile.open("UIManager.txt", ios::in);
    cout << "Load Game is not implemented yet.\n";
    pauseMenu();
}

void UIManager::inventory(int &actions) {
    int input;

    cout << "Your belongings: " << endl;
    for (int currentItem = 0; currentItem < this->pCurrentPlayer->vItems.size(); currentItem++) {
        cout << "[" << currentItem + 1 << "] " << this->pCurrentPlayer->vItems[currentItem].first->sItemName << " " << this->pCurrentPlayer->vItems[currentItem].second << "x" << endl;
    }
    getInput:
    cout << "Which item do you want to use (0 to exit): ";
    cin >> input;

    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        input = -1;
    }

    cout << endl;
    while (true) {

        if (input == 0) {
            return;
        }
        input--;
        if (input < 0 || input >= this->pCurrentPlayer->vItems.size()) {
            cout << "Invalid input, try again or enter 0 to exit: ";
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                input = -1;
            }
            cout << endl;
            continue;
        }
        if (shared_ptr<consumable> consumableItem = static_pointer_cast<consumable>(this->pCurrentPlayer->vItems[input].first)) {
            if (consumableItem->itemType != 1){
                cout << "This item isn't consumable, try again or type 0 to exit: ";
                cin >> input;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    input = -1;
                }
                cout << endl;
                continue;
            }
            if (this->pCurrentPlayer->vItems[input].second > 0) {
                this->pCurrentPlayer->saturation += consumableItem->iSaturationInfluence;
                this->pCurrentPlayer->hydration += consumableItem->iHydrationInfluence;
                this->pCurrentPlayer->mentalHealth += consumableItem->iMentalInfluence;

                if (this->pCurrentPlayer->saturation > 100) {
                    this->pCurrentPlayer->saturation = 100;
                }
                if (this->pCurrentPlayer->hydration > 100) {
                    this->pCurrentPlayer->hydration = 100;
                }
                if (this->pCurrentPlayer->mentalHealth > 100) {
                    this->pCurrentPlayer->mentalHealth = 100;
                }

                if (!consumableItem->bIsReusable) {
                    this->pCurrentPlayer->vItems[input].second--;
                    if (this->pCurrentPlayer->vItems[input].second < 0) {
                        this->pCurrentPlayer->vItems.erase(this->pCurrentPlayer->vItems.begin() + input); // delete element at position of input
                    }
                }
            }
            else {
                cout << "You don't own enough " << consumableItem->sItemName << " to perform this action" << endl;
                cout << "Try again or type 0 to exit: ";
                cin >> input;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    input = -1;
                }
                cout << endl;
            }
            break;
        }
    }

    pauseMenu();
}

void UIManager::shopMenu(int &actions) {
    int input;

    for (int shownShop = 0; shownShop < this->vShops.size(); shownShop++) {
        cout << "[" << shownShop + 1 << "] " << this->vShops[shownShop].sShopName << " | Distance: " << this->vShops[shownShop].usDistance << endl;
    }
    cout << "Which shop do you want to visit: ";
    cin >> input;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        input = -1;
    }
    cout << endl;

    while (true) {

        if (input == 0) {
            return;
        }
        input--;
        if (input >= 0 && input < this->vShops.size()) {
            if (this->vShops[input].usDistance > actions) {
                cout << "You don't have enough actions left to visit this shop. " << endl;
                cout << "Try again or type 0 to exit: ";
                cin >> input;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    input = -1;
                }
                cout << endl;
                continue;
            }
            actions -= this->vShops[input].usDistance;
            break;
        }

        cout << "The input was invalid, try again or 0 to exit: ";
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            input = -1;
        }
        cout << endl;
    }

    this->vShops[input].openShop(*this->pCurrentPlayer);

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

void UIManager::updatePlayerStatesOnNewDay() {
    if (this->pCurrentPlayer->playerHealth > 100) {
        this->pCurrentPlayer->playerHealth = 100;
    }
    else if (this->pCurrentPlayer->playerHealth < 0) {
        //death() cause: died
    }
    if (this->pCurrentPlayer->saturation > 100) {
        this->pCurrentPlayer->saturation = 100;
    }

    this->pCurrentPlayer->saturation -= round(random(10,20)); //saturation decrease because new day

    if (this->pCurrentPlayer->saturation < 0) {
        this->pCurrentPlayer->saturation = 0;
        this->pCurrentPlayer->playerHealth -= round(random(1,5));
    }

    if (this->pCurrentPlayer->hydration > 100) {
        this->pCurrentPlayer->hydration = 100;
    }

    this->pCurrentPlayer->hydration -= round(random(20,30)); // hydration decrease because new day

    if (this->pCurrentPlayer->hydration < 0) {
        this->pCurrentPlayer->hydration = 0;
        this->pCurrentPlayer->playerHealth -= round(random(1,10));
    }

    if (this->pCurrentPlayer->mentalHealth > 100) {
        this->pCurrentPlayer->mentalHealth = 100;
    }

    this->pCurrentPlayer->mentalHealth -= this->pCurrentPlayer->jCurrentJob.sMentalInstability / 10;

    if (this->pCurrentPlayer->mentalHealth < 0) {
        this->pCurrentPlayer->mentalHealth = 0;
    }

    if (this->pCurrentPlayer->sCriminalReputation > 100) {
        this->pCurrentPlayer->sCriminalReputation = 100;
    }

    else if (this->pCurrentPlayer->sCriminalReputation < 0){
        this->pCurrentPlayer->sCriminalReputation = 0;
    }
}