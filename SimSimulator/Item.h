#pragma once

#include <vector>
#include <string>

#include "CatNeedHierarchy.h"

//TODO take Cost and fullfillValue out of Constructor, and make them generated

class Item
{
public:
    //Default Constructor - only use when you can't otherwise creat an item. Basically a "null" item
    Item();

    //Contructor, Item with one NeedType it relates to
    Item(std::string newName, CatNeeds::CatNeedEnum need, float fullfillmentValue, int newCost);

    //Search trhough the ItemVector for and return any items in it that are of a certain CatNeed type in a Vector
    static std::vector<Item> GetItemsOfType(CatNeeds::CatNeedEnum needType);

    //Returns the List of all currently existing Items
    static std::vector<Item> GetItemList();

    //Generates the Cost for a Item based on how much Value is desired
    static int GenerateItemCost(float potentialValue);

    //A Method that lets another Object 'Use' this Item. The Item is used up/destroyed afterwards.
    void UseItem();

    //Check if this item supports the specified CatNeed
    bool HasCatNeedType(CatNeeds::CatNeedEnum needType);

    //Returns the NeedType of this Item
    CatNeeds::CatNeedEnum GetNeedType();

    //Gets the Name of this Item
    std::string GetItemName();

    //Gets the Fullfillment Value for this Item
    const float & GetFullfillmentValue() const;

    //Gets the cost of this Item
    const int & GetItemCost() const;

    //Checks if the given Item is valid, or in other words, if it's a properly instantiated Item or just a blank default
    bool IsItemValid();


private:
    //A Vector containing all currently existing Item instances
    static std::vector<Item> itemList;

    std::string itemName; //The name of this item
    CatNeeds::CatNeedEnum needType; //The Needs that this Item can fulfill
    float needFullfillmentValue; //Corresponds to needTypes with how much each need can be fulfilled
    int itemCost; //How much does this item cost to create

    //Deestroys this item
    void DestroyItem();
};