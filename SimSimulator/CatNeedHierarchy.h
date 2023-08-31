#pragma once
#include <vector>

//A static class with an Enum of Needs, and a const char*[] to correlate to them
class CatNeeds
{
public:
    //An Enum that lists the different types of Cat Needs
    static enum CatNeedEnum
    {
        Eat,
        Sleep,
        Cleanliness,
        Play,
        Social
    };

    //An array that correlates to the CatNeedEnum, so that a const char* can be associated with each numerical enum
    static constexpr const char* CatNeedNames[] =
    {
        "Eat", "Sleep", "Cleanliness", "Play", "Social"
    };

    //Returns the name for a CatNeedEnum type
    static const char* GetEnumName(CatNeedEnum catNeedType);
};

//Represents a 'Need' for a Cat. Every Need degrades over time
class Need 
{
public:
    Need(CatNeeds::CatNeedEnum catNeed, float needWeightSetter, float needDecrementSetter);

    //Creates a Vector containing one of each CatNeed with a default value
    static std::vector<Need> CreateNeedVector();

    //Returns this Need's Need-Type
    CatNeeds::CatNeedEnum GetNeedType();

    //Returns the 'weight' of this Need
    float GetNeedWeight();

    //Returns the current needStatus of this Need
    float GetNeedStatus();

    //Gets the Status of the need, minus the weight value, to give the total adjusted need value of the Need
    float GetAdjustedNeedLevel();

    //Change the Need Status for this need by the provided ammount - positive or negative
    void ModifyNeedStatus(float changeAmount);

    //Used to Decrement the Status for every turn by a base ammount + a 10th of the needWeight
    void DecrementStatus();

private:
    CatNeeds::CatNeedEnum needType; //Which CatNeed type is this?
    float needWeight;     //What is the 'Weight' of this Cat Need?
    float needStatus;     //What is the Status, 0-100, of this Need?
    float decrementRate;  //How fast does this need's needStatus decrement?
};