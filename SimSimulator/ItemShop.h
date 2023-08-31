#pragma once

#include "Wallet.h"
#include "CatNeedHierarchy.h"

//A class that interacts with the Player to instantiate new Item or Cat objects
class ItemShop
{
public:
    //Method to Open the Shop - prints text to prompt Player for input
    //Needs acess to the Player's Wallet so it can check how much money the Player has
    static void OpenShop(Wallet & playerWallet);

    //Method to Close the Shop and stop looking for Player interactions with the Shop
    static void CloseShop();

    //Method to Generate a new Item
    //

    //Method to Buy an Item. Prompts the Player with a series of questions, and on success returns an Item
    static void BuyItem(Wallet & playerWallet);


    //Method to check if a given Item is possible to create - if so it returns True
    //Used within the Item Creation Method

private:
    //Bool to check if the Item Shop is 'Open' - aka is looking for Player Input
    static bool isItemShopOpen;

    //Called from BuyItem - prompts the Player to Select a CatNeed Type and applies it to the provided variable reference
    static void SelectItemCatNeedType(CatNeeds::CatNeedEnum &);

    //Called from BuyItem - prompts Player to enter their desired ItemPower for their new Item
    static void SelectItemPower(int& itemPower);
};