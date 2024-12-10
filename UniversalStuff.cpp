#include <algorithm>
#include <iostream>
#include <windows.h>
#include <random>
#include "Player.h"
#pragma execution_character_set("utf-8")

using namespace std;



double random(double min, double max) {
    static random_device rd;  // Seed
    static mt19937 gen(rd()); // Random number generator
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

Job randomElement(const vector<Job>& elements, const std::vector<double>& weights) {
    // Ensure the weights and elements are the same size
    if (elements.size() != weights.size()) {
        throw std::invalid_argument("Elements and weights must have the same size.");
    }

    // Random number generator
    random_device rd;
    mt19937 gen(rd());

    // Create a discrete distribution based on the weights
    discrete_distribution<> dist(weights.begin(), weights.end());

    // Select and return a random element based on the distribution
    return elements[dist(gen)];
}

vector<double> chanceDistribution(vector<double> weights) {
    int sum = 0;
    for(int i = 0; i < weights.size(); i++) {
        sum += weights[i];
    }
    for(int i = 0; i < weights.size(); i++) {
        weights[i] /= sum;
    }

    return weights;
}

void randomEvent(player& player) {

    int iTempVar;

    int event = static_cast<int>(std::round(random(0,4))); // Zufälliges Ereignis auswählen


    switch (event) {
        case 0:
            cout << "You found 50$ on the street!" << endl;
        player.balance += 50;
        break;
        case 1:
            cout << "You got sick and paid 100$ for medical bills." << endl;
        player.balance -= 100;
        player.mentalHealth -= 10;
        break;
        case 2:
            iTempVar = static_cast<int>(round(random(player.currentJob.sSalary, player.currentJob.sSalary*4)));
        cout << "You got a bonus at work: " << iTempVar << endl;
        player.balance += iTempVar;
        break;
        case 3:
            cout << "You lost your wallet and 50$!" << endl;
        player.balance -= 50;
        break;
    }

    // Begrenzung der Werte
    if (player.mentalHealth > 100) player.mentalHealth = 100;
    if (player.mentalHealth < 0) player.mentalHealth = 0;
    if (player.saturation > 100) player.saturation = 100;
    if (player.saturation < 0) player.saturation = 0;

    // Aktuellen Zustand ausgeben
    cout << "Your current balance: " << player.balance << "$" << endl;
    cout << "Your current mental health: " << player.mentalHealth << "%" << endl;
    cout << "Your current saturation: " << player.saturation << "%" << endl;
}

// Set console text and background color
void setColor(int rT, int gT, int bT, int rB, int gB, int bB) {
    int textColor = 0;
    int backgroundColor = 0;

    // Map RGB values to Windows console colors (16-color limitation)
    if (rT > 128) textColor |= FOREGROUND_RED;
    if (gT > 128) textColor |= FOREGROUND_GREEN;
    if (bT > 128) textColor |= FOREGROUND_BLUE;
    if (rT + gT + bT > 384) textColor |= FOREGROUND_INTENSITY; // Brighten text

    if (rB > 128) backgroundColor |= BACKGROUND_RED;
    if (gB > 128) backgroundColor |= BACKGROUND_GREEN;
    if (bB > 128) backgroundColor |= BACKGROUND_BLUE;
    if (rB + gB + bB > 384) backgroundColor |= BACKGROUND_INTENSITY; // Brighten background

    // Set the console text attribute
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor | backgroundColor);
}

// Reset the console color to default
void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Default color
}

// Create a colored text as a string
string colorText(int rT, int gT, int bT, int rB, int gB, int bB, const string& text) {
    setColor(rT, gT, bT, rB, gB, bB);  // Set the desired colors
    return text;                      // Return the text (colors applied in console)
}

void gameOver(int Reason) {
    switch (Reason) {
        case 1:
            setColor(102, 173, 172,0,0,0);
            cout << R"(
      ╲│    ===================================     ==================================╲   │╱
   │╱  │    ███████╗ █████╗ ███╗   ███╗███████╗      ██████╗ ██╗   ██╗███████╗██████╗  │  ╱   ╱
    ╲   ╲ ╱ ██╔════╝██╔══██╗████╗ ████║██╔════╝     ██╔═══██╗██║   ██║██╔════╝██╔══██╗  ╲│   │
     │   │  ██║ ███╗███████║██╔████╔██║█████╗       ██║   ██║██║   ██║█████╗  ██████╔╝    ╲ ╱
      ╲ ╱   ██║ ╚██║██╔══██║██║╚██╔╝██║██╔══╝       ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗ │╱  │
       │╱   ███████║██║  ██║██║ ╚═╝ ██║███████╗     ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║  ╲ ╱
        ╲   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝      ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝   │
         │  ===================================     ==================================    ╲
            )"
                 << endl;
        cout << "                                     ◈ Electric chair Death ◈" << endl;



            resetColor();  // Reset the color after output
            break;
    }
}


