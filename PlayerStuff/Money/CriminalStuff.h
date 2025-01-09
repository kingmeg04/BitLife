#ifndef CRIMINALSTUFF_H
#define CRIMINALSTUFF_H


#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <variant>
#include "../PlayerStuff.h"
#include "../../UniversalStuff/RandomStuff.h"
#include "../../GameStuff/GameOverStuff.h"

class player;

struct crime{
    short sIllegalness; //range from 1 - 1000
    float fWitnessability;
    std::string sName;
};

void prisonCharge(player& thePlayer, crime crimeCaughtFor);

#endif // CRIMINALSTUFF_H
