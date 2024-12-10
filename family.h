//
// Created by leona on 09.12.2024.
//

#ifndef FAMILY_H
#define FAMILY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Family {
    string spouseName;
    vector<string> children;
};

class FamilyManager {
public:
    void getMarried(Family& family, int& balance);
    void haveChild(Family& family, int& balance);
    void displayFamily(const Family& family);
};

#endif // FAMILY_H
