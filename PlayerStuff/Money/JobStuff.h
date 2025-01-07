#ifndef JOBSTUFF_H
#define JOBSTUFF_H

#include <string>
#include <vector>
#include <random>

// Definition der Klasse job
class job {
public:
    short sSalary; // Gehalt
    short sMentalInstability; // Mentale Instabilität
    std::string sName;

    job(short Salary, short MentalInstability, std::string Name)
        : sSalary(Salary), sMentalInstability(MentalInstability), sName(std::move(Name)) {}
};

// Deklaration der Funktion
job getRandomJob();

#endif //JOBSTUFF_H
