#ifndef TIME_MANAGEMENT_H
#define TIME_MANAGEMENT_H

#include <iostream>

class TimeManagement {
    unsigned short day;
    unsigned short week;
    unsigned short month;
    unsigned short year;

public:
    TimeManagement();
    void advanceDay();
    void advanceWeek();
    void advanceMonth();
    void displayDate() const;
    unsigned short getDay() const;
};

void cashday(int& balance, int salary);

#endif //TIME_MANAGEMENT_H
