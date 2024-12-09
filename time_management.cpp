//
// Created by leona on 09.12.2024.
//

#include "time_management.h"

TimeManagement::TimeManagement() : day(1), week(1), month(1), year(2024) {}

void TimeManagement::advanceDay() {
    day++;
    if (day > 30) {
        day = 1;
        advanceMonth();
    }
    displayDate();
}

void TimeManagement::advanceWeek() {
    day += 7;
    if (day > 30) {
        day -= 30;
        advanceMonth();
    }
    displayDate();
}

void TimeManagement::advanceMonth() {
    month++;
    if (month > 12) {
        month = 1;
        year++;
    }
    displayDate();
}

void TimeManagement::displayDate() const {
    cout << "Current Date: " << year << "/"
         << (month < 10 ? "0" : "") << month << "/"
         << (day < 10 ? "0" : "") << day << endl;
}

unsigned short TimeManagement::getDay() const {
    return day;
}

void cashday(int& balance, int salary) {
    balance += salary;
    cout << "Cashday! You received: $" << salary << endl;
    cout << "Current Balance: $" << balance << endl;
}
