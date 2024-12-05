#include <iostream>
#include <random>
#include <windows.h>

using namespace std;

double random(double min, double max) {
    static random_device rd;  // Seed
    static mt19937 gen(rd()); // Random number generator
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

void setColor(int r, int g, int b) {
    // Convert RGB values to a 16-color attribute (Windows Console limitation)
    int color = 0;

    // Define RGB values in Windows console format (using attributes)
    if (r > 128) color |= FOREGROUND_RED;
    if (g > 128) color |= FOREGROUND_GREEN;
    if (b > 128) color |= FOREGROUND_BLUE;

    // Set the console text attribute using SetConsoleTextAttribute
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to reset the color back to default
void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 7 is the default color
}

// Function to output colored text in the console
void colorText(int r, int g, int b, const std::string& text) {
    setColor(r, g, b);  // Set color
    std::cout << text;   // Print the text
    resetColor();        // Reset to default color
}