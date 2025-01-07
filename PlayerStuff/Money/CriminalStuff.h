#ifndef CRIMINALSTUFF_H
#define CRIMINALSTUFF_H

#include <array>
#include <string>

// Definition der Crime-Struktur
struct Crime {
    short sIllegalness;  // Bereich von 1 - 1000
    float fWitnessability;
    std::string sName;
    short sTimesCommitted = 0;
};

// Deklaration von prisonCharge
void prisonCharge(std::array<Crime, 6>& BadBoyArray, const Crime& CrimeCaughtFor, int totalMoney);

#endif // CRIMINALSTUFF_H
