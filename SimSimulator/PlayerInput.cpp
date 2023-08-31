#include <conio.h>
#include <iostream>

#include "PlayerInput.h"
#include "ItemShop.h"
#include "Item.h"
#include "Wallet.h"
#include "Cat.h"

bool PlayerInput::isGettingPlayerInput = false;
bool PlayerInput::playerInputRunning = true;

//Looks for Player Input to interact with various systems
//Needs a Wallet instance so that it can display the Player's current Wallet when requested
void PlayerInput::GetPlayerInput(Wallet & playerWallet, Cat & playerCat)
{
    //playerInputRunning = true;

    while (playerInputRunning)
    {
        isGettingPlayerInput = true;

        while (isGettingPlayerInput)
        {
            std::cout << "Commands: \n i: Item Shop    c: Check Cat    p: Pet Cat    r: check the Room    w: Check Wallet" << "\n";

            char playerInput = _getch();

            if (playerInput == 'i' || playerInput == 'I')
            {
                //Call method to Interact with the ItemShop class
                InteractWithShop(playerWallet);
                std::cout << std::endl;
                isGettingPlayerInput = false;
            }
            else if (playerInput == 'c' || playerInput == 'C')
            {
                //Check the Cat's Status - will give a flavor-text hint about how it's doing
                playerCat.CheckCatStatus();
                std::cout << std::endl;
                isGettingPlayerInput = false;
            }
            else if (playerInput == 'p' || playerInput == 'P')
            {
                //Call method to Pet the Cat
                PetCat(playerCat);
                isGettingPlayerInput = false;
            }
            else if (playerInput == 'r' || playerInput == 'R')
            {
                //Gets a list of Items currently available, and shows current funds
                std::cout << "\n" << "You look around the room, and you see all of these items:" << "\n";
                std::vector<Item> itemList = Item::GetItemList();

                for (int i = 0; i < itemList.size(); i++)
                {
                    std::cout << itemList[i].GetItemName() << "\n";
                }

                std::cout << "\n" << std::endl;
                isGettingPlayerInput = false;
            }
            else if (playerInput == 'w' || playerInput == 'W')
            {
                //Shows the current Wallet ammount
                std::cout << "Checking Wallet. . ." << "\n";
                std::cout << "Current Money in Wallet: " << playerWallet.GetCurrentMoneyAmmount() << "\n\n";
                isGettingPlayerInput = false;
            }
            //When no valid command is chosen, the commands just get reprinted
            else
            {
                std::cout << "Please choose from one of the following commands:\n\n";
            }
        }
    }
};

//Stop looking for Player Input
void PlayerInput::StopGettingPlayerInput()
{
    playerInputRunning = false;
    isGettingPlayerInput = false;
};

//Method to prompt Player to make their first Cat
Cat PlayerInput::CreateCat()
{
    std::cout << "It's time to pick out your cat!\n\n";

    std::string catName;
    bool playerIsMakingSelection = true;

    while (playerIsMakingSelection)
    {
        std::cout << "What is your cat's name?\n\n";
        std::cin >> catName;

        std::cout << "Is the name " << catName << " ok?\n\n y = Yes    n = No\n \n";
        char playerSelection = _getch();

        if (playerSelection == 'y' || playerSelection == 'Y')
        {
            std::cout << "Great! So your cat will be called " << catName << "!\n" << std::endl;
            playerIsMakingSelection = false;
        }
        else if (playerSelection == 'n' || playerSelection == 'N')
        {
            std::cout << "I see, so that name's no good, then? Let's try again.\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            std::cout << "Please press y to confirm your cat's name, or press n to pick a different name.\n";
    }

    std::cout << "Now, it's time to care for your cat! Buy them items to take care of them, and don't forget to ";
    std::cout << "pet them and talk to them!\n I hope you enjoy your time with your new kitty!\n\n";
    std::cout << "Press any key to begin\n\n";
    _getch(); //This is just to give the player a chance to pause before they begin the game, don't need to store char

    return Cat(catName);
};

//Method to open the Item Shop and to initiate Player Interaction
void PlayerInput::InteractWithShop(Wallet & playerWallet)
{
    ItemShop::OpenShop(playerWallet);
};

//Method to Pet the Player's Cat, fulfills some small stat replenishment for the Cat
void PlayerInput::PetCat(Cat& playerCat)
{
    playerCat.PetCat();
};