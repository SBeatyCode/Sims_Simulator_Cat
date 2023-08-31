#pragma once

#include <vector>
#include <string>
#include <chrono>

#include "CatNeedHierarchy.h"
#include "Item.h"

class Cat
{
public:

    Cat(std::string newName);

    //Should be called on it's own thread. Constantly decrements the Cat's Needs.
    void RunCatNeedSimulation();

    //Returns the Cat's name as a pointer
    const std::string* GetName() const;

    //Returns the Cat's NeedList Vector
    std::vector<Need> GetNeedsList();

    //Pet the Cat. Gives a Boost to Social and Play
    void PetCat();

    //Change the specified CatNeed by the specified Ammount
    void ModifyNeed(CatNeeds::CatNeedEnum catNeed, float changeAmmount);

    //Return a Vector giving the name and status of each of the Cat's Needs
    std::vector<std::string> GetNeedStatusVector();

    //The Cat acts in a way to give you a clue what need it wants to be filled
    void CheckCatStatus();

    //Stops simulating the Cat's Stats' over time
    void StopSimulatingStats();

    //Checks if the cat has run away. If true, the cat has run and the game should be over.
    bool HasCatRunAway();

private:
    static std::chrono::seconds statSimulationInterval; //The time in seconds between decrementing the Cat's stats

    //Default 'Items' the Cat can use to clean itself and to take a nap if no items are available
    static Item cleanSelfDefault;
    static Item sleepSelfDefault;

    const std::string name; //The Cat's name
    std::vector<Need> needsList; //The Cat's Needs as a Vector
    bool isSimulatingStats; //Is the Cat currently simulating its stats, and having them decremented?
    bool hasCatRunAway; //Has the cat run away? The cat will run away when 2 or more stats hit 0

    //The Cat will either do an action conveyed through flavor text, that's just for fun, or they will try to fullfill a need
    void PerformAction();

    //Called from PerformAction. The Cat randomly chooses and displays a fun flavortext message
    void DoCatAction();

    //The Cat will try to use one of the available items in order to fill one of it's needs
    void FillNeed();

    //The Cat determines which Need is most important for it to fulfill, and returns a reference to it
    Need& PickNeed();

    //Get a vector with the 2 highest needs
    std::vector<Need> GetHighestNeeds();

    //The Cat uses an item to fill one of its needs
    void UseItem(Item itemToUse);

    //Checks if the Cat should run away. If the Cat has 2 or more stats at 0, they will run away and the game will end
    void CheckIfShouldRunAway();
};