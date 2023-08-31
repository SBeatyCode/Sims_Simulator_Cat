#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <thread>
#include <algorithm>

#include "CatNeedHierarchy.h"
#include "Cat.h"
#include "CatText.h"
#include "Item.h"

using namespace CatText;
using namespace std::literals::chrono_literals;


Cat::Cat(std::string newName) : name(newName)
{
    needsList = Need::CreateNeedVector();
    isSimulatingStats = false;
    hasCatRunAway = false;
}

//Should be called on it's own thread. Constantly decrements the Cat's Needs.
void Cat::RunCatNeedSimulation()
{
    //This is just for testing
    //PerformAction();

    isSimulatingStats = true;
    
    while (isSimulatingStats)
    {
        for (int i = 0; i < needsList.size(); i++)
        {
            needsList[i].DecrementStatus();

            //testing
            //std::cout << CatNeeds::GetEnumName(needsList[i].GetNeedType()) << ": " << needsList[i].GetNeedStatus() << "\n";
        }
        std::this_thread::sleep_for(statSimulationInterval);
        PerformAction();
        std::this_thread::sleep_for(statSimulationInterval);
        CheckIfShouldRunAway();
    }
};

    //Returns the Cat's name as a pointer
const std::string* Cat::GetName() const
{
    return &name;
}

    //Returns the Cat's NeedList Vector
std::vector<Need> Cat::GetNeedsList()
{
    return needsList;
}

//Pet the Cat. Gives a Boost to Social and Play
void Cat::PetCat()
{
    needsList[CatNeeds::CatNeedEnum::Social].ModifyNeedStatus(5);
    needsList[CatNeeds::CatNeedEnum::Play].ModifyNeedStatus(5);

    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, CatText::catPets.size() - 1);
    std::cout << "\n" << "You pet " << name << ". " << CatText::catPets[dist(rd)] << "\n" << std::endl;
};


//Change the specified CatNeed by the specified Ammount
void Cat::ModifyNeed(CatNeeds::CatNeedEnum catNeed, float changeAmmount)
{
    needsList[catNeed].ModifyNeedStatus(changeAmmount);
};

//Return a Vector giving the name and status of each of the Cat's Needs
std::vector<std::string> Cat::GetNeedStatusVector()
{
    std::vector<std::string> needsStatusVector;

    for (int i = 0; i < needsList.size(); i++)
    {
        std::string value = CatNeeds::CatNeedNames[needsList[i].GetNeedType()];
        value += " ";
        value += std::to_string(needsList[i].GetNeedStatus());
        needsStatusVector.push_back(value);
    }

    return needsStatusVector;
};

//The Cat will either do an action conveyed through flavor text, that's just for fun, or they will try to fullfill a need
void Cat::PerformAction()
{
    //Randomly Pick whther to fill a need or do a kitty action
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 2);

    if (dist(rd) == 1)
        DoCatAction();
    else
        FillNeed();
};

//Called from PerformAction. The Cat randomly chooses and displays a fun flavortext message
void Cat::DoCatAction()
{
    //Call a random number to pick a message from CatText
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, CatText::catActions.size() -1);

    std::cout << "\n" << name << CatText::catActions[dist(rd)] << "\n" << std::endl;
};

//The Cat will try to use one of the available items in order to fill one of it's needs
void Cat::FillNeed()
{
    //This is just for testing
    //std::cout << CatNeeds::GetEnumName(PickNeed().GetNeedType()) << " needs to be filled!" << std::endl;

    std::vector<Item> itemlist = Item::GetItemList();
    std::vector<Need> highestNeeds = GetHighestNeeds();

    Item selectedItem;
    float selectedItemScore = 120;

    //Search through the items list for items that match the 2 highest needs, and find the one that returns the lowest value
    for (int i = 0; i < itemlist.size(); i++)
    {
        for (int j = 0; j < highestNeeds.size(); j++)
        {
            //Check if the current item in the iteration matches the currently selected need type
            if (itemlist[i].HasCatNeedType(highestNeeds[j].GetNeedType()))
            {
                float needItemScore = (highestNeeds[j].GetNeedStatus() + itemlist[i].GetFullfillmentValue() < 100) ? highestNeeds[j].GetNeedStatus() + itemlist[i].GetFullfillmentValue() : 100;
                needItemScore += highestNeeds[j].GetNeedWeight();

                if (needItemScore < selectedItemScore)
                {
                    selectedItem = itemlist[i];
                    selectedItemScore = needItemScore;
                }
            }
        }
    }

    //If no suitable item was found, see if you can use one of the Cat's 'default item actions', eg the static class Items belonging to Cat
    if (!selectedItem.IsItemValid())
    {
        //If one of the values that are in highestNeeds are Cleanliness or Sleep, use those Class 'default items'
        if (highestNeeds[0].GetNeedType() == CatNeeds::CatNeedEnum::Sleep || highestNeeds[1].GetNeedType() == CatNeeds::CatNeedEnum::Sleep)
        {
            std::cout << "\n" << name << SLEEP_SELF << "\n" << std::endl;
            needsList[CatNeeds::CatNeedEnum::Sleep].ModifyNeedStatus(sleepSelfDefault.GetFullfillmentValue());
        }
        else if (highestNeeds[0].GetNeedType() == CatNeeds::CatNeedEnum::Cleanliness || highestNeeds[1].GetNeedType() == CatNeeds::CatNeedEnum::Cleanliness)
        {
            std::cout << "\n" << name << CLEAN_SELF << "\n" << std::endl;
            needsList[CatNeeds::CatNeedEnum::Cleanliness].ModifyNeedStatus(cleanSelfDefault.GetFullfillmentValue());
        }
        else
        {
            //If no item found and/or clean/sleep self can't work, flavor text to show that cat is upset or needs/wants something
            std::cout << "\n" << name << NEED_DONT_KNOW << "\n \n";
            CheckCatStatus();
        }
    }
    else
    {
        UseItem(selectedItem);
    }
};

//The Cat determines which Need is most important for it to fulfill, and returns a reference to it
Need& Cat::PickNeed()
{
    //Initialize a pointer looking at the first of the Cat's needs
    Need* mostNeeded = &needsList[0];

    //Loop through all of the Cat's Needs and find the one with the lowest fullfillment minus the Need's weight
    for (int i = 1; i < needsList.size(); i++)
    {
        if (needsList[i].GetAdjustedNeedLevel() < mostNeeded->GetAdjustedNeedLevel())
        {
            mostNeeded = &needsList[i];
        }
    }

    return *mostNeeded;
};

//Get a vector with the 2 highest needs
std::vector<Need> Cat::GetHighestNeeds()
{
    std::vector<Need> highestNeeds; //vector* to return
    Need highestNeed = PickNeed(); //get the highest need
    highestNeeds.push_back(highestNeed);

    //Set a default value for the next most-needed number. If the highest needed is already that value, use the next value as default
    Need nextMostNeeded = needsList[0];
    if (nextMostNeeded.GetNeedType() == highestNeed.GetNeedType())
        nextMostNeeded = needsList[1];

    //Loop through all of the Cat's Needs and find the one with the lowest fullfillment minus the Need's weight
    for (int i = 0; i < needsList.size(); i++)
    {
        //Skip this loop if the current selected Need is already the highestNeed
        if (needsList[i].GetNeedType() == highestNeed.GetNeedType()) continue;

        if (needsList[i].GetAdjustedNeedLevel() < nextMostNeeded.GetAdjustedNeedLevel())
        {
            nextMostNeeded = needsList[i];
        }
    }
    highestNeeds.push_back(nextMostNeeded);

    return highestNeeds;
};

//The Cat acts in a way to give you a clue what need it wants to be filled
void Cat::CheckCatStatus()
{
    std::random_device rd;
    std::uniform_int_distribution<int> distClean(0, CatText::cleanlinessActions.size() - 1);
    std::uniform_int_distribution<int> distEat(0, CatText::eatActions.size() - 1);
    std::uniform_int_distribution<int> distPlay(0, CatText::playActions.size() - 1);
    std::uniform_int_distribution<int> distSleep(0, CatText::sleepActions.size() - 1);
    std::uniform_int_distribution<int> distSocial(0, CatText::sleepActions.size() - 1);

    switch (PickNeed().GetNeedType())
    {
    case CatNeeds::CatNeedEnum::Cleanliness:
        std::cout << "\n" << name << CatText::cleanlinessActions[distClean(rd)] << "\n" << std::endl;
        break;
    case CatNeeds::CatNeedEnum::Eat:
        std::cout << "\n" << name << CatText::eatActions[distEat(rd)] << "\n" << std::endl;
        break;
    case CatNeeds::CatNeedEnum::Play:
        std::cout << "\n" << name << CatText::playActions[distPlay(rd)] << "\n" << std::endl;
        break;
    case CatNeeds::CatNeedEnum::Sleep:
        std::cout << "\n" << name << CatText::sleepActions[distSleep(rd)] << "\n" << std::endl;
        break;
    case CatNeeds::CatNeedEnum::Social:
        std::cout << "\n" << name << CatText::sleepActions[distSocial(rd)] << "\n" << std::endl;
        break;
    default:
        std::cout << "\n" << NEED_DONT_KNOW << "\n" << std::endl;
        break;
    }
};

//Stops simulating the Cat's Stats' over time
void Cat::StopSimulatingStats()
{
    isSimulatingStats = false;
};

//The Cat uses an item to fill one of its needs
void Cat::UseItem(Item itemToUse)
{
    //Show flavor text from using item
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, CatText::itemActions.size() - 1);
    std::cout << "\n" << name << " used the " << itemToUse.GetItemName() << "! " << CatText::itemActions[dist(rd)] << "\n" << std::endl;

    //Apply Item's restoration to the Cat's stat
    needsList[itemToUse.GetNeedType()].ModifyNeedStatus(itemToUse.GetFullfillmentValue());

    //'Use' the Item
    itemToUse.UseItem();
};

//Checks if the Cat should run away. If the Cat has 3 or more stats at 0, they will run away and the game will end
void Cat::CheckIfShouldRunAway()
{
    //Check how many stats are at 0
    int statsAtZero = 0;

    for (int i = 0; i < needsList.size(); i++)
    {
        if (needsList[i].GetNeedStatus() == 0)
            statsAtZero++;
    }

    if (statsAtZero >= 3)
    {
        StopSimulatingStats();
        hasCatRunAway = true;
    }
};

//Checks if the cat has run away. If true, the cat has run and the game should be over.
bool Cat::HasCatRunAway()
{
    return hasCatRunAway;
};


//----Setting values for Static class variables----//

std::chrono::seconds Cat::statSimulationInterval = 5s;
Item Cat::cleanSelfDefault = Item("Lick Self Clean", CatNeeds::CatNeedEnum::Cleanliness, 10, 1);
Item Cat::sleepSelfDefault = Item("Take a Cat Nap", CatNeeds::CatNeedEnum::Sleep, 10, 1);