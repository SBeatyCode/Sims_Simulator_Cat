#pragma once

#include "Cat.h"
#include "Wallet.h"

//A class to handle Player input, and calls methods on other classes. Acts as an interface between the player and other classes
class PlayerInput
{
public:
    //Method to open the Item Shop
    //Needs to pass the Player's Wallet to the Item shop, so that the Item shop can see how much the Player has
    static void InteractWithShop(Wallet & playerWallet);

    //Method to prompt Player to make their first Cat
    static Cat CreateCat();

    //Method to Show the Cat an Item

    //Constantly running Method that's looking for Player input
    //TODO - Move to Private after you're done testing all of this Method's responsibilities are working
    static void GetPlayerInput(Wallet & playerWallet, Cat & playerCat);

    //Stop looking for Player Input
    static void StopGettingPlayerInput();

private:
    //Should Player Input be tracked?
    static bool isGettingPlayerInput;

    //Method to Pet the Player's Cat, fulfills some small stat replenishment
    static void PetCat(Cat& playerCat);

    static bool playerInputRunning;
};