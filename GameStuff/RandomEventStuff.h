//
// Created by kingm on 07/01/2025.
//

#ifndef RANDOMEVENTSTUFF_H
#define RANDOMEVENTSTUFF_H

#include <vector>
#include "../PlayerStuff/PlayerStuff.h"
#include "../PlayerStuff/Money/JobStuff.h"
#include "ShopStuff.h"
class item;

//


int randomEventSelector(player& thePlayer, int currentDay);

void dating(player& thePlayer); // 50/50 -> be asked out or ask someone out --> rejection decreases mental stability
void prank(player& thePlayer); // only possible below age of 16 --> if pull prank criminalReputation rises and possibly get caught for action
void policeInvestigation(player& thePlayer); // Randomly asked to rat out a person for a crime that was committed
//void strayAnimal(player& thePlayer);
void winRandomGiveaway(player& thePlayer); // random stranger gives you a sum of money or an item with high value
void naturalDisaster(player& thePlayer); // make a decision --> balance between mentalStability, health and property/balance (check for insurance (house insurance))
void makeDonation(player& thePlayer); // possibility to make a donation which increases your mental stability and reduces CriminalReputation
void becomeAdmin(player& thePlayer); // get the option to be promoted to admin variant of current Job
void carCrash(player& thePlayer); // check if player has insurance (car insurance)
void slipOnBananaPeal(player& thePlayer); //take some damage
void getCaughtInStripclubByMedia(player& thePlayer); // reduce mentalStability and dependent on Job lower the income
void askedToCommitCrime(player& thePlayer); // asked to commit a certain crime (help out in bank robbery, be get away driver, etc.) --> raises criminalLife and have the option of getting caught
void explosiveDiarrheaInPublicSpace(player& thePlayer); // add the crime of diarrheaInPublicSpace to the players charges
void organisedCrime(player& thePlayer); // organised crime like robbing a bank


#endif //RANDOMEVENTSTUFF_H
