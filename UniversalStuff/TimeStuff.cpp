//
// Created by jbrui on 17.12.2024.
//e
#include "TimeStuff.h"

using namespace std;

/**
 *
 * @param timeType 1 = day, 2 = week, 3 = month
 */
void TimeManager::advanceOneTime(int timeType) { //possibly make it a function that directly asks player how much time to skip
    switch(timeType) {
        case 1:
            this->iday += 1;
        break;
        case 2:
            this->iday += 7;
        break;
        case 3:
            this->iday += 30;
        break;
    }

}