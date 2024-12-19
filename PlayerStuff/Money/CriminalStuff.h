//
// Created by jbrui on 17.12.2024.
//

#ifndef CRIMINALSTUFF_HPP
#define CRIMINALSTUFF_HPP

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <variant>
#include "../../UniversalStuff/RandomStuff.h"
#include "../../GameStuff/GameOverStuff.h"

struct Crime{
    short sIllegalness; //range from 1 - 1000
    float fWitnessability;
    std::string sName;
    short sTimesCommitted = 0;
};

void prisonCharge(std::array<Crime&, 6> BadBoyArray, Crime CrimeCaughtFor, int totalMoney);


#endif //CRIMINALSTUFF_HPP
