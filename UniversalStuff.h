#ifndef UNIVERSAL_STUFF_H
#define UNIVERSAL_STUFF_H

#include <algorithm>
#include <iostream>
#include <windows.h>
#include "Player.h"
#include <random>

// Declarations only
double random(double, double);
std::vector<double> chanceDistribution(std::vector<double> weights);
Job randomElement(const std::vector<Job>& elements, const std::vector<double>& weights);
void randomEvent(player& player);
void setColor(int, int, int, int, int, int);
void resetColor();
std::string colorText(int, int, int, int, int, int, const std::string&);
void gameOver(int);

#endif  // UNIVERSAL_STUFF_H