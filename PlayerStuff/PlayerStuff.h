//
// Created by jbrui on 17.12.2024.
//

#ifndef PLAYERSTUFF_H
#define PLAYERSTUFF_H

#include <vector>
#include "../GameStuff/ShopStuff.h"
#include "Money/JobStuff.h"

class item;

class player {
    std::vector<job> vPrevJobs;

public:

    job jCurrentJob;
    long balance = 0;
    std::vector<std::pair<item, int>> vItems;
    short saturation = 100;
    short mentalHealth = 100;
    short criminalReputation = 0; //How involved in the crime world you are

    player(job CurrentJob) : jCurrentJob(CurrentJob) {}


    void newJob(job newJob);
    void useItem(item itemUsed, int amountUsed);

};

#endif //PLAYERSTUFF_H
