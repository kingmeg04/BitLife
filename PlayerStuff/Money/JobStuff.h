//
// Created by jbrui on 17.12.2024.
//

#ifndef JOBSTUFF_H
#define JOBSTUFF_H

#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include "../../UniversalStuff/RandomStuff.h"


class job {


public:

    bool bIsAdmin = false;
    short sSalary; //paid weekly
    short sMentalInstability; //range from 1 - 100
    std::string sName;

    job(short Salary, short MentalInstability, std::string Name){
        this->sSalary = Salary;
        this->sMentalInstability = MentalInstability;
        this->sName = std::move(Name);
    }

};

// Deklaration der Funktion
job getRandomJob();

#endif //JOBSTUFF_H
