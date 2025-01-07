//
// Created by jbrui on 19.12.2024.
//

#ifndef SHOPSTUFF_HPP
#define SHOPSTUFF_HPP

#include <string>
#include <vector>
#include "../PlayerStuff/PlayerStuff.h"
class player;


class item {

public:
    std::string sItemName;
    int iPrice;
    int iMentalInfluence = 0;
    int iSaturationInfluence = 0;

    item(std::string ItemName, int Price, int MentalInfluence = 0, int SaturationInfluence = 0) {
        this->sItemName = ItemName;
        this->iPrice = Price;
        if(MentalInfluence != 0) {
            this->iMentalInfluence = MentalInfluence;
        }
        if(SaturationInfluence != 0) {
            this->iSaturationInfluence = SaturationInfluence;
        }
    }
};

class shop {
public:
    std::string sShopName;
    std::vector<item> vAvailableItems = {};

    shop(std::string ShopName, std::vector<item> AvailableItems = {}) {
        this->sShopName = ShopName;
        if(AvailableItems.size() != 0) {
            this->vAvailableItems = AvailableItems;
        }
    }
    void openShop(player& player);
    void sellItem(player& player);
};



#endif //SHOPSTUFF_HPP
