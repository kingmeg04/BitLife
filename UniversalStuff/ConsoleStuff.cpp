//
// Created by jbrui on 17.12.2024.
//

#include "ConsoleStuff.h"

#pragma execution_character_set("utf-8")

// [] randomElement(vector<[]> elements, vector<float> weights)

/**
 * @note 0 = black
 * @note 1 = navy
 * @note 2 = green
 * @note 3 = teal
 * @note 4 = maroon
 * @note 5 = purple
 * @note 6 = olive
 * @note 7 = silver
 * @note 8 = gray
 * @note 9 = blue
 * @note 10 = lime
 * @note 11 = aqua
 * @note 12 = red
 * @note 13 = fuchsia
 * @note 14 = yellow
 * @note 15 = white
 */
void setColor(unsigned short foreground, unsigned short background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground | background << 4);
}

void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
