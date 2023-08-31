#include "ItemShop.h"
#include "Wallet.h"
#include "CatNeedHierarchy.h"
#include "Item.h"

#include <iostream>
#include <conio.h>

//Bool to check if the Item Shop is 'Open' - aka is looking for Player Input
bool ItemShop::isItemShopOpen = false;

//Method to Open the Shop - prints text to prompt Player for input
//TODO will need to return an Item
void ItemShop::OpenShop(Wallet & playerWallet)
{
    isItemShopOpen = true;
    std::cout << "\nThe Item Shop is Open!\n\n";

    while (isItemShopOpen)
    {
        //Display Commands and look for Player input
        std::cout << "Commands: \n i: Buy Item    w: Check Wallet    x: Cancel" << "\n";

        char playerInput = _getch();

        if (playerInput == 'i')
        {
            std::cout << "Let's buy a new item!" << "\n";
            //Begin the Item buying process
            BuyItem(playerWallet);

            //May not nessisarily want to close the shop right away but keep this for now for testing
            //isItemShopOpen = false;
        }
        else if (playerInput == 'w')
        {
            //Shows the current Wallet ammount
            std::cout << "Checking Wallet. . ." << "\n";
            std::cout << "Current Money in Wallet: " << playerWallet.GetCurrentMoneyAmmount() << "\n \n";
        }
        else if (playerInput == 'x')
        {
            std::cout << "You exit the Shop. Please come again!" << std::endl;
            CloseShop();
        }
    }
};

//Method to Close the Shop and stop looking for Player interactions with the Shop
void ItemShop::CloseShop()
{
    isItemShopOpen = false;
};

//Method to Buy an Item. Prompts the Player with a series of questions, and on success returns an Item
void ItemShop::BuyItem(Wallet & playerWallet)
{
    std::string newItemName;

    //Player enters a Name for their Item
    bool playerIsMakingSelection = true;

    while (playerIsMakingSelection)
    {
        std::cout << "Item name? \n";
        std::cin >> newItemName;

        std::cout << "Is the name " << newItemName << " ok for your item?\ny = Yes    n = No\n \n";
        char playerSelection = _getch();

        if (playerSelection == 'y' || playerSelection == 'Y')
        {
            std::cout << "Great! So your new item will be called " << newItemName << "!\n" << std::endl;
            playerIsMakingSelection = false;
        }
        else if (playerSelection == 'n' || playerSelection == 'N')
        {
            std::cout << "I see, so that name's no good, then? Let's try again.\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            std::cout << "Please press y to confirm your item's name, or press n to pick a different name.\n";
    }


    //Prompts the Player for the CatNeedType and applies it
    CatNeeds::CatNeedEnum catNeedType;
    SelectItemCatNeedType(catNeedType);

    //Get desired Item Strength from user
    int itemPower;
    SelectItemPower(itemPower);

    //Show the Cost to the Player
    float potentialCost = Item::GenerateItemCost(itemPower);
    std::cout << "If you want to buy the " << newItemName << ", it will cost you " << potentialCost << ".\n";
    std::cout << "Do you want to buy this item?\n y = Yes    n = No\n \n";

    //Finalize Purchase

    playerIsMakingSelection = true;

    while (playerIsMakingSelection)
    {
        char playerSelection = _getch();

        if (playerSelection == 'y' || playerSelection == 'Y')
        {
            //Check if player's wallet has the funds to buy the item, if not close the shop. or start from the begining
            if (playerWallet.GetCurrentMoneyAmmount() < potentialCost)
            {
                std::cout << "You do not have sufficient funds. Wait for your Wallet to generate more money, or try to buy a cheaper item.\n";
            }
            else //Generate Item if Player has the funds
            {
                Item newItem = Item(newItemName, catNeedType, itemPower, potentialCost);
                playerWallet.DeductMoneyFromWallet(potentialCost);
                std::cout << "You purchased your new item!\n" << std::endl;
            }
            //Generate item
            playerIsMakingSelection = false;
        }
        else if (playerSelection == 'n' || playerSelection == 'N')
        {
            std::cout << "You changed your mind. Come again!\n" << std::endl;
            playerIsMakingSelection = false;
        }
        else
            std::cout << "Please enter y to buy the item, or n to not buy the item.\n";
    }
};

//Called from BuyItem - prompts the Player to Select a CatNeed Type
void ItemShop::SelectItemCatNeedType(CatNeeds::CatNeedEnum& catNeedType)
{
    std::cout << "\nPlease select a Cat Need Type for your new Item: \n";

    for (int i = 0; i < 5; i++)
    {
        std::cout << "Press " << i << " to select " << CatNeeds::CatNeedNames[i] << "\n";
    }

    //Player Selects the Cat Need Type they want for their Item
    char playerSelection;
    bool playerIsMakingSelection = true;

    while (playerIsMakingSelection)
    {
        playerSelection = _getch();

        if (playerSelection == '0')
        {
            catNeedType = CatNeeds::CatNeedEnum::Eat;
            playerIsMakingSelection = false;
        }
        else if (playerSelection == '1')
        {
            catNeedType = CatNeeds::CatNeedEnum::Sleep;
            playerIsMakingSelection = false;
        }
        else if (playerSelection == '2')
        {
            catNeedType = CatNeeds::CatNeedEnum::Cleanliness;
            playerIsMakingSelection = false;
        }
        else if (playerSelection == '3')
        {
            catNeedType = CatNeeds::CatNeedEnum::Play;
            playerIsMakingSelection = false;
        }
        else if (playerSelection == '4')
        {
            catNeedType = CatNeeds::CatNeedEnum::Social;
            playerIsMakingSelection = false;
        }
        else
        {
            std::cout << "Please select press one of the 0-4 keys to make your selection. \n";
        }
    }
};

//Called from BuyItem - prompts Player to enter their desired ItemPower for their new Item
void ItemShop::SelectItemPower(int& itemPower)
{
    std::cout << "\nHow strong should this item be?\n";
    bool playerIsMakingSelection = true;

    playerIsMakingSelection = true;

    while (playerIsMakingSelection)
    {
        std::cin >> itemPower;

        if (std::cin.fail()) //Check fail state separately from the value-check
        {
            std::cout << "Please enter a non-decimal number between 1-50. \n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            itemPower = NULL;
        }
        else if (itemPower < 1 || itemPower > 50)
            std::cout << "Please enter a non-decimal number between 1-50. \n";
        else
            playerIsMakingSelection = false;
    }
};