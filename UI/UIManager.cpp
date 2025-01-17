#include "UIManager.h"


using namespace std;
namespace fs = filesystem;

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

array<int,2> UIManager::loadGame() {
    this->vShops.clear();
    int dataPos = 0;
    string tempData;
    array<int,2> returnArr;
    fstream saveFile;
    vector<fs::path> filePaths;
    int input;

    // Get the AppData\Local folder path
    char appDataPath[MAX_PATH];
    if (SHGetFolderPath(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, appDataPath) != S_OK) {
        cerr << "Failed to get AppData path." << endl;
        return array<int,2>{-1,-1};
    }

    // Define the target folder path in AppData
    string folderPath = string(appDataPath) + "\\TheRealBitLife";

    // Ensure the folder exists
    try {
        if (!fs::exists(folderPath)) {
            fs::create_directories(folderPath);
        }
    } catch (const exception& e) {
        cerr << "Failed to create folder: " << e.what() << endl;
        return array<int,2>{-1,-1};
    }

    // Iterate through files in the folder
    try {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                filePaths.push_back(entry.path());
            }
        }
    } catch (const exception& e) {
        cerr << "Error accessing folder: " << e.what() << endl;
        return array<int,2>{-1,-1};
    }

    // Display the files
    for (size_t file = 0; file < filePaths.size(); ++file) {
        string filename = filePaths[file].filename().string(); // Extract filename from path
        cout << "[" << file + 1 << "] " << filename.substr(0, filename.length() - 4) << endl; // Remove extension
    }

    cout << "Which save do you want to open: ";
    cin >> input;
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        input = -1;
    }
    cout << endl;


    while (true) {
        if (input == 0) {
            return array<int,2>{-1,-1};
        }
        input--;

        if (input < 0 || input >= filePaths.size()) {
            cout << "Invalid input, try again or enter 0 to exit: ";
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                input = -1;
            }
            cout << endl;
            continue;
        }
        break;
    }
    saveFile.open(filePaths[input], ios::in);
    if (!saveFile.is_open()) {
        cerr << "Failed to open the selected file." << endl;
        return array<int,2>{-1,-1};
    }

    string data = string((istreambuf_iterator<char>(saveFile)), istreambuf_iterator<char>());

    fs::path filePath = filePaths[input];
    string filenameWithoutExtension = filePath.stem().string();
    pCurrentPlayer = new player(filenameWithoutExtension,job(0, 0, "child"));
    int iterator = 0;

    for (iterator = 1; iterator <= 9; iterator++) { // player stats
        while (data[dataPos] != '\n') {
            tempData.push_back(data[dataPos]);
            dataPos++;
        }
        switch (iterator) {
            case 1: returnArr[0] = stoi(tempData); break;
            case 2: returnArr[1] = stoi(tempData); break;
            case 3: this->pCurrentPlayer->playerHealth = static_cast<short>(stoi(tempData)); break;
            case 4: this->pCurrentPlayer->saturation = static_cast<short>(stoi(tempData)); break;
            case 5: this->pCurrentPlayer->hydration = static_cast<short>(stoi(tempData)); break;
            case 6: this->pCurrentPlayer->mentalHealth = static_cast<short>(stoi(tempData)); break;
            case 7: this->pCurrentPlayer->sCriminalReputation = static_cast<short>(stoi(tempData)); break;
            case 8: this->pCurrentPlayer->balance = stoi(tempData); break;
            case 9: this->pCurrentPlayer->iJailTime = stoi(tempData); break;
            default: break;
        }
        tempData.clear();
        dataPos++;
    }
    dataPos++;


    for (iterator = 1; iterator <= 4; iterator++) {
        while (data[dataPos] != '|' && data[dataPos] != '\n') {
            tempData.push_back(data[dataPos]);
            dataPos++;
        }
        switch (iterator) {
            case 1: this->pCurrentPlayer->jCurrentJob.sName = tempData; break;
            case 2: this->pCurrentPlayer->jCurrentJob.sMentalInstability = static_cast<short>(stoi(tempData)); break;
            case 3: this->pCurrentPlayer->jCurrentJob.sSalary = static_cast<short>(stoi(tempData)); break;
            case 4: this->pCurrentPlayer->jCurrentJob.bIsAdmin = static_cast<bool>(stoi(tempData)); break;
            default: break;
        }
        tempData.clear();
        dataPos++;
    }

    while (data[dataPos] != '\\' && dataPos < data.size()) { // loads items in player's inventory
        tempData.push_back(data[dataPos]);
        if (stoi(tempData) == 0) {
            tempData.clear();
            shared_ptr<item> loadingItem = make_shared<item>("", 0);
            dataPos+=2;

            for (iterator = 1; iterator <= 4; iterator++) {
                while (data[dataPos] != '|' && data[dataPos] != '\n') {
                    tempData.push_back(data[dataPos]);
                    dataPos++;
                }
                switch (iterator) {
                    case 1: loadingItem->sItemName = tempData; break;
                    case 2: loadingItem->iPrice = stoi(tempData); break;
                    case 3: loadingItem->bIsReusable = static_cast<bool>(stoi(tempData)); break;
                    case 4: loadingItem->iMentalInfluence = stoi(tempData); break;
                }
                tempData.clear();
                dataPos++;
            }
            loadingItem = make_shared<item>(loadingItem->sItemName, loadingItem->iPrice,loadingItem->bIsReusable, loadingItem->iMentalInfluence);
            while (data[dataPos] != '\n') {
                tempData.push_back(data[dataPos]);
                dataPos++;
            }
            this->pCurrentPlayer->vItems.push_back({loadingItem, stoi(tempData)});
        }
        else if (stoi(tempData) == 1) {
            tempData.clear();
            shared_ptr<consumable> loadingItem = make_shared<consumable>(0, 0);
            dataPos+=2;

            for (iterator = 1; iterator <= 6; iterator++) {
                while (data[dataPos] != '|' && data[dataPos] != '\n') {
                    tempData.push_back(data[dataPos]);
                    dataPos++;
                }

                switch (iterator) {
                    case 1: loadingItem->iSaturationInfluence = stoi(tempData); break;
                    case 2: loadingItem->iHydrationInfluence = stoi(tempData); break;
                    case 3: loadingItem->sItemName = tempData; break;
                    case 4: loadingItem->iPrice = stoi(tempData); break;
                    case 5: loadingItem->bIsReusable = static_cast<bool>(stoi(tempData)); break;
                    case 6: loadingItem->iMentalInfluence = stoi(tempData); break;
                    default: break;
                }
                tempData.clear();
                dataPos++;
            }
            loadingItem = make_shared<consumable>(loadingItem->iHydrationInfluence, loadingItem->iSaturationInfluence, loadingItem->sItemName, loadingItem->iPrice,loadingItem->bIsReusable, loadingItem->iMentalInfluence);
            while (data[dataPos] != '\n') {
                tempData.push_back(data[dataPos]);
                dataPos++;
            }
            this->pCurrentPlayer->vItems.push_back({loadingItem, stoi(tempData)});
        }
        else if (stoi(tempData) == 2) {
            tempData.clear();
            shared_ptr<car> loadingItem = make_shared<car>(0);
            dataPos+=2;

            for (iterator = 1; iterator <= 5; iterator++) {
                while (data[dataPos] != '|' && data[dataPos] != '\n') {
                    tempData.push_back(data[dataPos]);
                    dataPos++;
                }
                switch (iterator) {
                    case 1: loadingItem->iActionsGained = stoi(tempData); break;
                    case 2: loadingItem->sItemName = tempData; break;
                    case 3: loadingItem->iPrice = stoi(tempData); break;
                    case 4: loadingItem->bIsReusable = static_cast<bool>(stoi(tempData)); break;
                    case 5: loadingItem->iMentalInfluence = stoi(tempData); break;
                    default: break;
                }
                tempData.clear();
                dataPos++;
            }
            loadingItem = make_shared<car>(loadingItem->iActionsGained, loadingItem->sItemName, loadingItem->iPrice,loadingItem->bIsReusable, loadingItem->iMentalInfluence);
            while (data[dataPos] != '\n') {
                tempData.push_back(data[dataPos]);
                dataPos++;
            }
            this->pCurrentPlayer->vItems.push_back({loadingItem, stoi(tempData)});
        }
        tempData.clear();
        dataPos++;
    }

    dataPos += 6;
    tempData.clear();
    while (data[dataPos] != '\\' && dataPos < data.size()) {// loading crimes
        crime loadingCrime = {0,0,""};
        for (iterator = 1; iterator <= 3; iterator++) {
            while (data[dataPos] != '|' && data[dataPos] != '\n') {
                tempData.push_back(data[dataPos]);
                dataPos++;
            }
            switch (iterator) {
                case 1: loadingCrime.sName = tempData; break;
                case 2: loadingCrime.fWitnessability = stof(tempData); break;
                case 3: loadingCrime.sIllegalness = static_cast<short> (stoi(tempData)); break;
                default: break;
            }
            tempData.clear();
            dataPos++;
        }
        while (data[dataPos] != '\n') {
            tempData.push_back(data[dataPos]);
            dataPos++;
        }
        this->pCurrentPlayer->vCrimes.push_back({loadingCrime, stoi(tempData)});
        tempData.clear();
        dataPos++;
    }

    dataPos += 6;
    tempData.clear();
    while (data[dataPos] != '\\' && dataPos < data.size()) {// loading crimes
        job loadingJob = {0,0,""};
        for (iterator = 1; iterator <= 4; iterator++) {
            while (data[dataPos] != '|' && data[dataPos] != '\n') {
                tempData.push_back(data[dataPos]);
                dataPos++;
            }
            switch (iterator) {
                case 1: loadingJob.sName = tempData; break;
                case 2: loadingJob.sMentalInstability = static_cast<short>(stoi(tempData)); break;
                case 3: loadingJob.sSalary = static_cast<short>(stoi(tempData)); break;
                case 4: loadingJob.bIsAdmin = static_cast<bool> (stoi(tempData)); break;
                default: break;
            }
            tempData.clear();
            dataPos++;
        }
        this->pCurrentPlayer->vPrevJobs.push_back(loadingJob);
        tempData.clear();
        dataPos++;
    }

    dataPos += 6;
    tempData.clear();
    while (dataPos < data.size()) {
        cout << dataPos << endl;
        shop loadingShop = {"",0,{}};
        while (data[dataPos] != '|' && data[dataPos] != '\n') {
            tempData.push_back(data[dataPos]);
            dataPos++;
        }
        loadingShop.sShopName = tempData;
        tempData.clear();
        dataPos++;
        while (data[dataPos] != '|' && data[dataPos] != '\n') {
            tempData.push_back(data[dataPos]);
            dataPos++;
        }
        loadingShop.usDistance = static_cast<unsigned short>(stoi(tempData));
        tempData.clear();
        dataPos++;
        while (data[dataPos] != '\\' && dataPos < data.size()) { // loads items in a shop
            cout << dataPos << "shit\n";

            tempData.push_back(data[dataPos]);
            cout << "|" << tempData << dataPos << data[dataPos--] << data[dataPos++] << "|" << endl;
            if (stoi(tempData) == 0) {
                tempData.clear();
                shared_ptr<item> loadingItem = make_shared<item>("", 0);
                dataPos+=2;

                for (iterator = 1; iterator <= 4; iterator++) {
                    while (data[dataPos] != '|' && data[dataPos] != '\n') {
                        tempData.push_back(data[dataPos]);
                        dataPos++;
                    }
                    switch (iterator) {
                        case 1: loadingItem->sItemName = tempData; break;
                        case 2: loadingItem->iPrice = stoi(tempData); break;
                        case 3: loadingItem->bIsReusable = static_cast<bool>(stoi(tempData)); break;
                        case 4: loadingItem->iMentalInfluence = stoi(tempData); break;
                    }
                    tempData.clear();
                    dataPos++;
                }
                loadingItem = make_shared<item>(loadingItem->sItemName, loadingItem->iPrice,loadingItem->bIsReusable, loadingItem->iMentalInfluence);
                loadingShop.vAvailableItems.push_back(loadingItem);
            }
            else if (stoi(tempData) == 1) {
                tempData.clear();
                shared_ptr<consumable> loadingItem = make_shared<consumable>(0, 0);
                dataPos+=2;

                for (iterator = 1; iterator <= 6; iterator++) {
                    while (data[dataPos] != '|' && data[dataPos] != '\n') {
                        tempData.push_back(data[dataPos]);
                        dataPos++;
                    }

                    switch (iterator) {
                        case 1: loadingItem->iSaturationInfluence = stoi(tempData); break;
                        case 2: loadingItem->iHydrationInfluence = stoi(tempData); break;
                        case 3: loadingItem->sItemName = tempData; break;
                        case 4: loadingItem->iPrice = stoi(tempData); break;
                        case 5: loadingItem->bIsReusable = static_cast<bool>(stoi(tempData)); break;
                        case 6: loadingItem->iMentalInfluence = stoi(tempData); break;
                        default: break;
                    }
                    tempData.clear();
                    dataPos++;
                }
                loadingItem = make_shared<consumable>(loadingItem->iHydrationInfluence, loadingItem->iSaturationInfluence, loadingItem->sItemName, loadingItem->iPrice,loadingItem->bIsReusable, loadingItem->iMentalInfluence);
                loadingShop.vAvailableItems.push_back(loadingItem);
            }
            else if (stoi(tempData) == 2) {
                tempData.clear();
                shared_ptr<car> loadingItem = make_shared<car>(0);
                dataPos+=2;

                for (iterator = 1; iterator <= 5; iterator++) {
                    while (data[dataPos] != '|' && data[dataPos] != '\n') {
                        tempData.push_back(data[dataPos]);
                        dataPos++;
                    }
                    switch (iterator) {
                        case 1: loadingItem->iActionsGained = stoi(tempData); break;
                        case 2: loadingItem->sItemName = tempData; break;
                        case 3: loadingItem->iPrice = stoi(tempData); break;
                        case 4: loadingItem->bIsReusable = static_cast<bool>(stoi(tempData)); break;
                        case 5: loadingItem->iMentalInfluence = stoi(tempData); break;
                        default: break;
                    }
                    tempData.clear();
                    dataPos++;
                }
                loadingItem = make_shared<car>(loadingItem->iActionsGained, loadingItem->sItemName, loadingItem->iPrice,loadingItem->bIsReusable, loadingItem->iMentalInfluence);
                loadingShop.vAvailableItems.push_back(loadingItem);
            }
            tempData.clear();
        }
        dataPos += 6;
        this->vShops.push_back(loadingShop);
    }

    return returnArr;
}

void UIManager::inventory(int &actions) {
    int input;

    cout << "Your belongings: " << endl;
    for (int currentItem = 0; currentItem < this->pCurrentPlayer->vItems.size(); currentItem++) {
        cout << "[" << currentItem + 1 << "] " << this->pCurrentPlayer->vItems[currentItem].first->sItemName << '|' << this->pCurrentPlayer->vItems[currentItem].second << "x" << endl;
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

    for (int item = 0; item < this->pCurrentPlayer->vItems.size(); item++) {
        if (this->pCurrentPlayer->vItems[item].second <= 0) {
            this->pCurrentPlayer->vItems.erase(this->pCurrentPlayer->vItems.begin() + item);
        }
    }
}

void UIManager::saveGame(int startDate, int endDate) {

    string data;
    fstream saveFile;

    // Define the target folder path
    char appDataPath[MAX_PATH];
    if (SHGetFolderPath(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, appDataPath) != S_OK) {
        cerr << "Failed to get AppData path." << endl;
        return;
    }

    // Define the target folder path in AppData
    string folderPath = string(appDataPath) + "\\TheRealBitLife";

    // Ensure the folder exists
    try {
        if (!fs::exists(folderPath)) {
            fs::create_directories(folderPath);
        }
    } catch (const exception& e) {
        cerr << "Failed to create folder: " << e.what() << endl;
        return;
    }

    // Construct the full file path
    string filePath = folderPath + "\\" + this->pCurrentPlayer->sPlayerName + ".txt";

    // Saving process start
    saveFile.open(filePath, ios::out);
    if (!saveFile.is_open()) {
        cerr << "Failed to open file for saving: " << filePath << endl;
        return;
    }

    data = to_string(endDate) + '\n' // date
    + to_string(startDate) + '\n' // startDate
    + to_string(this->pCurrentPlayer->playerHealth) + '\n' // health
    + to_string(this->pCurrentPlayer->saturation) + '\n' // saturation
    + to_string(this->pCurrentPlayer->hydration) + '\n' // hydration
    + to_string(this->pCurrentPlayer->mentalHealth) + '\n' // mental health
    + to_string(this->pCurrentPlayer->sCriminalReputation) + '\n' // criminal reputation
    + to_string(this->pCurrentPlayer->balance) + '\n' // balance/money
    + to_string(this->pCurrentPlayer->iJailTime) + '\n' // jail time
    + this->pCurrentPlayer->jCurrentJob.sName + '|' // player's job's name
    + to_string(this->pCurrentPlayer->jCurrentJob.sMentalInstability) + '|' // player's job's mental instability
    + to_string(this->pCurrentPlayer->jCurrentJob.sSalary) + '|' // player's job's salary
    + to_string(this->pCurrentPlayer->jCurrentJob.bIsAdmin) + '\n'; // true if player's job is admin type


    for (int savingItems = 0; savingItems < this->pCurrentPlayer->vItems.size(); savingItems++) {
        if (shared_ptr<consumable> savingItem = static_pointer_cast<consumable>(this->pCurrentPlayer->vItems[savingItems].first)) {
            if (savingItem->itemType == 1) {
                data += to_string(savingItem->itemType) + '|'
                + to_string(savingItem->iSaturationInfluence) + '|'
                + to_string(savingItem->iHydrationInfluence) + '|'
                + savingItem->sItemName + '|'
                + to_string(savingItem->iPrice) + '|'
                + to_string(savingItem->bIsReusable) + '|'
                + to_string(savingItem->iMentalInfluence) + '|'
                ;
                data += to_string(this->pCurrentPlayer->vItems[savingItems].second) + '\n';
                continue;
                }
            }

        if (shared_ptr<car> savingItem = static_pointer_cast<car>(this->pCurrentPlayer->vItems[savingItems].first)) {
            if (savingItem->itemType == 2) {
                data += to_string(savingItem->itemType) + '|'
                + to_string(savingItem->iActionsGained) + '|'
                + savingItem->sItemName + '|'
                + to_string(savingItem->iPrice) + '|'
                + to_string(savingItem->bIsReusable) + '|'
                + to_string(savingItem->iMentalInfluence) + '|'
                ;

                data += to_string(this->pCurrentPlayer->vItems[savingItems].second) + '\n';
                continue;
            }
        }
        if (shared_ptr<item> savingItem = static_pointer_cast<item>(this->pCurrentPlayer->vItems[savingItems].first)) {
            if (savingItem->itemType == 0) {
                data += to_string(savingItem->itemType) + '|'
                + savingItem->sItemName + '|'
                + to_string(savingItem->iPrice) + '|'
                + to_string(savingItem->bIsReusable) + '|'
                + to_string(savingItem->iMentalInfluence) + '|'
                ;
                data += to_string(this->pCurrentPlayer->vItems[savingItems].second) + '\n';
                continue;
            }
        }
        throw runtime_error("Type handling error2");
    }
    data += "\\^-^/\n";
    for (int savingCrimes = 0; savingCrimes < this->pCurrentPlayer->vCrimes.size(); savingCrimes++) {
        data += this->pCurrentPlayer->vCrimes[savingCrimes].first.sName + '|'
        + to_string(this->pCurrentPlayer->vCrimes[savingCrimes].first.fWitnessability) + '|'
        + to_string(this->pCurrentPlayer->vCrimes[savingCrimes].first.sIllegalness) + '|'
        + to_string(this->pCurrentPlayer->vCrimes[savingCrimes].second) + '\n'
        ;
    }
    data += "\\^-^/\n";
    for (job savingJob : this->pCurrentPlayer->vPrevJobs) {
        data += savingJob.sName + '|'
        + to_string(savingJob.sMentalInstability) + '|'
        + to_string(savingJob.sSalary) + '|'
        + to_string(savingJob.bIsAdmin) + '\n';
    }
    data += "\\^-^/\n";
    for (shop savingShops : this->vShops) { // saving shops
        data += savingShops.sShopName + '|'
        + to_string(savingShops.usDistance) + '\n'
        ;
        for (int savingItems = 0; savingItems < savingShops.vAvailableItems.size(); savingItems++) { // all items will have itemType = 0 CURRENT PROBLEM

            if (shared_ptr<consumable> savingItem = static_pointer_cast<consumable>(savingShops.vAvailableItems[savingItems])) {
                if (savingItem->itemType == 1) {
                    data += to_string(savingItem->itemType) + '|'
                    + to_string(savingItem->iSaturationInfluence) + '|'
                    + to_string(savingItem->iHydrationInfluence) + '|'
                    + savingItem->sItemName + '|'
                    + to_string(savingItem->iPrice) + '|'
                    + to_string(savingItem->bIsReusable) + '|'
                    + to_string(savingItem->iMentalInfluence) + '\n'
                    ;
                    continue;
                }
            }

            if (shared_ptr<car> savingItem = static_pointer_cast<car>(savingShops.vAvailableItems[savingItems])) {
                if (savingItem->itemType == 2) {
                    data += to_string(savingItem->itemType) + '|'
                    + to_string(savingItem->iActionsGained) + '|'
                    + savingItem->sItemName + '|'
                    + to_string(savingItem->iPrice) + '|'
                    + to_string(savingItem->bIsReusable) + '|'
                    + to_string(savingItem->iMentalInfluence) + '\n'
                    ;
                    continue;
                }
            }

            if (shared_ptr<item> savingItem = static_pointer_cast<item>(savingShops.vAvailableItems[savingItems])) {
                if (savingItem->itemType == 0) {
                    data += to_string(savingItem->itemType) + '|'
                    + savingItem->sItemName + '|'
                    + to_string(savingItem->iPrice) + '|'
                    + to_string(savingItem->bIsReusable) + '|'
                    + to_string(savingItem->iMentalInfluence) + '\n'
                    ;
                    continue;
                }
            }
            throw runtime_error("Type handling error1");
        }
        data += "\\^-^/\n";
    }

    saveFile << data; // saving end
}
