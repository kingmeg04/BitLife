//
// Created by jbrui on 17.12.2024.
//
#include "TimeStuff.h"

using namespace std;

/**
 *
 * @param timeType 1 = day, 2 = week, 3 = month
 */
void TimeManager::advanceOneTime(int timeType) { //possibly make it a function that directly asks player how much time to skip
    switch(timeType) {
        case 1:
            this->iDay += 1;
        break;
        case 2:
            this->iDay += 7;
        break;
        case 3:
            this->iDay += 30;
        break;
        case 4:
            this->iDay += 360;
        break;
    }

}