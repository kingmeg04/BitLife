#include <iostream>
#include <windows.h>
#include <random>

#pragma execution_character_set("utf-8")

using namespace std;

double random(double min, double max) {
    static random_device rd;  // Seed
    static mt19937 gen(rd()); // Random number generator
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

auto randomElement(const vector<auto>& elements, const std::vector<double>& weights) {
    // Ensure the weights and elements are the same size
    if (elements.size() != weights.size()) {
        throw std::invalid_argument("Elements and weights must have the same size.");
    }

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a discrete distribution based on the weights
    std::discrete_distribution<> dist(weights.begin(), weights.end());

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


