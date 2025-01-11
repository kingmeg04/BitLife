#ifndef SHOPSTUFF_HPP
#define SHOPSTUFF_HPP

#include <string>
#include <vector>
#include <memory> // For smart pointers
#include <iostream>
#include "../PlayerStuff/PlayerStuff.h"
#include "../UniversalStuff/NamingStuff.h"
class player;

class item {
public:
    std::string sItemName;
    int iPrice;
    bool bIsReusable = false;
    int iMentalInfluence = 0;

    item(std::string ItemName, int Price, bool IsReusable = false, int MentalInfluence = 0)
        : sItemName(ItemName), iPrice(Price), bIsReusable(IsReusable), iMentalInfluence(MentalInfluence) {}

    virtual ~item() = default; // Virtual destructor to ensure proper cleanup

};

class consumable : public item {
public:
    int iSaturationInfluence = 0;
    int iHydrationInfluence = 0;

    consumable(int HydrationInfluence = 0, int SaturationInfluence = 0, std::string ItemName = "", int Price = 0, bool IsReusable = false, int MentalInfluence = 0)
        : item(ItemName, Price, IsReusable, MentalInfluence), iHydrationInfluence(HydrationInfluence), iSaturationInfluence(SaturationInfluence) {}

};

class car : public item {
public:
    int iActionsGained;

    car(int ActionsGained, std::string ItemName = "", int Price = 0, bool IsReusable = true, int MentalInfluence = 0)
        : item(ItemName, Price, IsReusable, MentalInfluence), iActionsGained(ActionsGained) {}

};

class shop {
public:
    std::string sShopName;
    std::vector<std::shared_ptr<item>> vAvailableItems; // Use shared_ptr to manage polymorphic objects

    shop(std::string ShopName, std::vector<std::shared_ptr<item>> AvailableItems = {})
        : sShopName(ShopName), vAvailableItems(AvailableItems) {}

    void openShop(player& player);
    void sellItem(player& player);
};

int checkForItem(player thePlayer, std::string itemName);
int checkForItem(std::vector<std::shared_ptr<item>> itemList, std::string itemName);
shop generateShop(std::vector<unsigned short> posCases);

#endif //SHOPSTUFF_HPP
