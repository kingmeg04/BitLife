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
    bool bIsAdmin = false;

public:

    short sSalary; //paid weekly
    short sMentalInstability; //range from 1 - 1000
    std::string sName;

    job(short Salary, short MentalInstability, std::string Name){
        this->sSalary = Salary;
        this->sMentalInstability = MentalInstability;
        this->sName = std::move(Name);
    }

};


#endif //JOBSTUFF_H
