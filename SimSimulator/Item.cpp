#include <string>

#include "Item.h"

Item::Item()
{
    itemName = "null";
    needFullfillmentValue = 0;
    itemCost = 0;
};

Item::Item(std::string newName, CatNeeds::CatNeedEnum need, float fullfillmentValue, int newCost)
    : itemName(newName), needType(need), needFullfillmentValue(fullfillmentValue), itemCost(newCost)
{
    itemList.push_back(*this);
};

//Vector that contains all Item instances
std::vector<Item> Item::itemList;

//Search through the ItemVector for and return any items in it that are of a certain CatNeed type in a Vector
//If no items of that type are found, will return an Empty Vector
std::vector<Item> Item::GetItemsOfType(CatNeeds::CatNeedEnum needType)
{
    std::vector<Item> foundItems;

    for (int i = 0; i < itemList.size(); i++)
    {
        if (itemList[i].HasCatNeedType(needType))
            foundItems.push_back(itemList[i]);
    }

    return foundItems;
};

//Returns a pointer to the current ItemList Vector
std::vector<Item> Item::GetItemList()
{
    return itemList;
}

//Generates the Cost for a Item based on how strong the desired item will be
int Item::GenerateItemCost(float potentialValue)
{
    return round(potentialValue * 1.25);
};

//A Method that lets another Object 'Use' this Item. The Item is used up/destroyed afterwards.
void Item::UseItem()
{
    this->DestroyItem();
};

bool Item::HasCatNeedType(CatNeeds::CatNeedEnum catNeedType)
{
    if (needType == catNeedType) return true;
    else return false;
};

//Returns the NeedType of this Item
CatNeeds::CatNeedEnum Item::GetNeedType()
{
    return needType;
};

//Returns a reference to the name of this item
std::string Item::GetItemName()
{
    return itemName;
};

//Gets the Fullfillment Value for this Item
const float & Item::GetFullfillmentValue() const
{
    return needFullfillmentValue;
};

//Gets the cost of this Item
const int& Item::GetItemCost() const
{
    return itemCost;
};

//Checks if the given Item is valid, or in other words, if it's a properly instantiated Item or just a blank default
bool Item::IsItemValid()
{
    if (itemName == "null" || itemCost == 0 || needFullfillmentValue == 0)
        return false;
    else
        return true;
};

//Destroys this Item and removes it from the Item list
//NOTE: If Items have similar names (for example, multiple items containing the name 'Kitty') it will still count
//as a 'match' for the algorithm, and erase multiple items. Be careful with naming
void Item::DestroyItem()
{
    itemList.erase(std::remove_if(itemList.begin(), itemList.end(), [this](Item& item)
    {
        return item.GetItemName() == this->GetItemName();
    }
    ), itemList.end());
};