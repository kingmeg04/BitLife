//
// Created by jbrui on 17.12.2024.
//

#ifndef PLAYERSTUFF_H
#define PLAYERSTUFF_H

#include <vector>
#include <iostream>
#include "Money/CriminalStuff.h"
#include "../GameStuff/ShopStuff.h"
#include "Money/JobStuff.h"

class item;
struct crime;

class player {


public:


    job jCurrentJob;
    long balance = 0;
    std::vector<std::pair<item, int>> vItems;
    std::vector<std::pair<crime, int>> vCrimes;
    std::vector<job> vPrevJobs;
    int iJailTime = 0;


    short playerActionPoints = 5; // how many actions the player can perform per day
    short playerHealth = 100;
    short saturation = 100;
    short mentalHealth = 100;
    short sCriminalReputation = 0; //How involved in the crime world you are

    player(job CurrentJob) : jCurrentJob(CurrentJob) {}


    void newJob(job newJob);
    void useItem(item itemUsed, int amountUsed);

};

#endif //PLAYERSTUFF_H
