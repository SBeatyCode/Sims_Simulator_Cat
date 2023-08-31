#pragma once
#include <chrono>

class Wallet
{
public:
    Wallet(int startingMoney, std::chrono::seconds secondInterval, int moneyIncrement);

    //Generate Money over time(X ammount every X seconds) Should be called with it's own thread
    void GenerateMoneyOverTime();

    //Gets the current ammount of Money stored in the Wallet
    const int& GetCurrentMoneyAmmount() const;

    //Takes the given ammount of money out of the Wallet
    void DeductMoneyFromWallet(int deduction);

    //Pauses the Production of Money for the Wallet
    void PauseMoneyProduction();

private:
    int monetaryValue; //The current ammount of money that the Wallt has stored
    const std::chrono::seconds moneyGenerationInterval; //The ammount of time in sconds between generating more money
    const int moneyGenerationIncrement; //How much money gets generated every money generation
    bool isGeneratingMoney; //Should the Wallet be currently generating money or not?
};