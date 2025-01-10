//
// Created by jbrui on 17.12.2024.
//

#ifndef TIMESTUFF_H
#define TIMESTUFF_H
#include <array>

class TimeManager {
public:
    int iDay;

    TimeManager(int startDay) {
        this->iDay = startDay;
    };
    /**
     *
     * @return dd,mm,yyyy
     * @note year has 360 days, 12 months, 30 days per month
     */
    std::array<int, 3> getDate() {
        int day = this->iDay;
        int month = 0;
        int year = 0;

        year = day / 360;
        day -= year * 360;

        month = day / 30 + 1;
        day -= (month - 1) * 30 - 1;

        return std::array<int, 3>{day, month, year};
    }
    void advanceOneTime(int timeType);

};
#endif //TIMESTUFF_H
