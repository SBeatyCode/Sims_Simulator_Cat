#include "Wallet.h"
#include <thread>

//Just for testing
#include <iostream>

Wallet::Wallet(int startingMoney, std::chrono::seconds secondInterval, int moneyIncrement)
    :monetaryValue(startingMoney), moneyGenerationInterval(secondInterval), moneyGenerationIncrement(moneyIncrement) 
{
    //This is set to false by default, but will turn on as soon as Wallet is told to generate money
    isGeneratingMoney = false;
};

//Generate Money over time(X ammount every X seconds) Should be called with it's own thread
void Wallet::GenerateMoneyOverTime()
{
    isGeneratingMoney = true;

    while (isGeneratingMoney)
    {
        monetaryValue += moneyGenerationIncrement;
        std::this_thread::sleep_for(moneyGenerationInterval);

        //Test Code
        //std::cout << monetaryValue << "\n";
    };
};

//Gets the current ammount of Money stored in the Wallet
const int& Wallet::GetCurrentMoneyAmmount() const
{
    return monetaryValue;
};

//Takes the given ammount of money out of the Wallet
void Wallet::DeductMoneyFromWallet(int deduction)
{
    monetaryValue -= deduction;
};

//Pauses the Production of Money for the Wallet
void Wallet::PauseMoneyProduction()
{
    isGeneratingMoney = false;
};