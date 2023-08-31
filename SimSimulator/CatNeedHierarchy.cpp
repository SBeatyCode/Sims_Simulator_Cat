#include "CatNeedHierarchy.h"
#include <vector>

//TODO Adjust Need Weights and Decrements as needed

//Returns the name for a CatNeedEnum type
const char* CatNeeds::GetEnumName(CatNeedEnum catNeedType)
{
    return CatNeedNames[catNeedType];
};

Need::Need(CatNeeds::CatNeedEnum catNeed, float needWeightSetter, float needDecrementSetter) 
    : needType(catNeed), needWeight(needWeightSetter), decrementRate(needDecrementSetter)
{
    needStatus = 75;
};

//Creates a Vector containing one of each CatNeed with a default value
std::vector<Need> Need::CreateNeedVector()
{
    std::vector<Need> needsVector;
    needsVector.push_back(Need(CatNeeds::CatNeedEnum::Eat, 20, -5));
    needsVector.push_back(Need(CatNeeds::CatNeedEnum::Sleep, 20, -5));
    needsVector.push_back(Need(CatNeeds::CatNeedEnum::Cleanliness, 15, -5));
    needsVector.push_back(Need(CatNeeds::CatNeedEnum::Play, 10, -5));
    needsVector.push_back(Need(CatNeeds::CatNeedEnum::Social, 10, -5));

    return needsVector;
};

//Returns this Nedd's Need-Type
CatNeeds::CatNeedEnum Need::GetNeedType()
{
    return needType;
}

//Returns the 'weight' of this Need
float Need::GetNeedWeight()
{
    return needWeight;
}

//Returns the current needStatus of this Need
float Need::GetNeedStatus()
{
    return needStatus;
}

//Gets the Status of the need, minus the weight value, to give the total adjusted need value of the Need
float Need::GetAdjustedNeedLevel()
{
    return needStatus - needWeight;
};

//Change the Need Status for this need by the provided ammount - positive or negative
void Need::ModifyNeedStatus(float changeAmount)
{
    needStatus += changeAmount;

    //Make sure the NeedStatus can't go above or below 0-100
    if (needStatus < 0) needStatus = 0;
    if (needStatus > 100) needStatus = 100;
}

//Used to Decrement the Status for every turn by a base ammount + a 10th of the needWeight
void Need::DecrementStatus()
{
    ModifyNeedStatus(decrementRate);
}