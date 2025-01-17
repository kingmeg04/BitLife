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

    const unsigned short itemType = 0;
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
    const unsigned short itemType = 1;
    int iSaturationInfluence;
    int iHydrationInfluence;

    consumable(int HydrationInfluence, int SaturationInfluence, std::string ItemName = "", int Price = 0, bool IsReusable = false, int MentalInfluence = 0)
        : item(ItemName, Price, IsReusable, MentalInfluence), iHydrationInfluence(HydrationInfluence), iSaturationInfluence(SaturationInfluence) {}

};

class car : public item {
public:
    const unsigned short itemType = 2;
    int iActionsGained;

    car(int ActionsGained, std::string ItemName = "", int Price = 0, bool IsReusable = true, int MentalInfluence = 0)
        : item(ItemName, Price, IsReusable, MentalInfluence), iActionsGained(ActionsGained) {}

};

class house : public item {
public:
    const unsigned short itemType = 3;
    int iStrength;

    house(int Strength, std::string ItemName = "", int Price = 0, bool IsReusable = true, int MentalInfluence = 0)
        : item(ItemName, Price, IsReusable, MentalInfluence), iStrength(Strength) {}
};

class shop {
public:
    unsigned short usDistance;
    std::string sShopName;
    std::vector<std::shared_ptr<item>> vAvailableItems; // Use shared_ptr to manage polymorphic objects

    shop(std::string ShopName, unsigned short Distance, std::vector<std::shared_ptr<item>> AvailableItems = {})
        : sShopName(ShopName),usDistance(Distance), vAvailableItems(AvailableItems) {}

    void openShop(player& player);
    void sellItem(player& player);
};

int checkForItem(player thePlayer, std::string itemName);
int checkForItem(std::vector<std::shared_ptr<item>> itemList, std::string itemName);
shop generateShop(std::vector<unsigned short> posCases, unsigned short maxDistance);

#endif //SHOPSTUFF_HPP
