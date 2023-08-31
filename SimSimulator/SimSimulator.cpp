// SimSimulator.cpp
//Goal: Make a Sim Simlator, or see if you can copy how a Sim's needs and mechnics work

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <random>
#include <conio.h>

#include "CatNeedHierarchy.h"
#include "Cat.h"
#include "Item.h"
#include "Wallet.h"
#include "ItemShop.h"
#include "PlayerInput.h"

using namespace std::literals::chrono_literals;

/*
    CAT Sim! Basic Design Outline followed to create this project

    //Let Player create their Cat!

    //Auto-Create basic set of Items that the Cat can use to fullfill a Need (toilet, bed, stove)
    
    // Every 'turn' (set-interval of time (1-10s)) print a message on the screen about Cat's status

    // --Based on Cat's current status, Cat can try to fulfill a need
    --Cat will get a list of items near it, and compare the needs they fullfill + in what ammount with what needs that it
    currently wants to be fulfilled
    --After making this list, the Cat will decide to either use an item, or it will Meow at the Player if it is not satisfied
    
    //Player can choose to take an "Action"
    --Buy Item, Show Cat Item (force-uses the Item on the Cat, but could randomly reject and 'waste' the item),
    Pet Cat, Talk to Cat, Check Current Items + Money
    // --Actions will take different number of 'turns'

    //Cat should meow at you when it has a need

    //When Player can create a new item
    //--Name the Object, and select from a menu which need(s) it can fulfill
   Items cost points/cash (which should generate over time automatically) so the player can't
   just infinitely spawn things indefinitely

    player should be able to Pet the Cat (raise Cat's Social)


    //---------------Ways this could be extended and improved--------------//
    //'Pause' the Wallet accuring Money and Cat stat decrease when the Player is in the Shop
    Add 'Durability' for Items, so that instead of Using Item automatically destroying them they can be used X-Times
    (increase the cost for the item along with the Item durability)
    //Let the Kitty 'Talk' to the Player
    //Player can spawn an additional Cat (at a cost)
    --if you do this, cats can increase each other's social and play
    --Would need a personality (pursonality) to determine if they like each other, ect
    --Could generate pursonality as a hash(?) based off of the Player-provided name/species, and the current time
    --Could also set some default "bad" items to start with, like a dusty broom, that makes Cat more dirty
    --Items should take an amount of time to use
*/



int main()
{
    //std::cout << "Threads available: " << std::thread::hardware_concurrency() << "\n"; 

    //----Introduction Text----//
    std::cout << "Welcome to the Cat Simulator! This text-based terminal game is was inspired by The Sims, but has you caring for\n";
    std::cout << "a Cat, similar to a Tamagotchi.\n\n";
    std::cout << "In this game, your cat's stats will slowly diminish over time.\n\n";
    std::cout << "If more than one of your cats stats are fully depleted... it's GAME OVER!\n\n";
    std::cout << "Your cat will do things periodically, and sometimes ";
    std::cout << "they will be trying\nto give you a clue about which of their stats are low.\n\n";
    std::cout << "After you name your cat, you'll be responsible for petting it,\nand buying it things from the item shop to keep it happy.\n\n";
    std::cout << "Speaking of the Item Shop, instead of a fixed-number of items, you can create your OWN items!\nYou can name them, decide which of your cat's stats you want it to affect, ";
    std::cout << "and how potent the item is.\nThe stronger it is though, the more money it will cost!\n\n";
    std::cout << "Money in your Wallet will increase on its own over time.\n\n";
    std::cout << "Your Cat may interupt you from time to time if you are trying to type. That's just how kitties are.\n";
    std::cout << "Don't worry, your entered information isn't interupted or changed when your cat does something.\n\n";

    std::cout << "Press any key to continue\n\n";
    _getch();

    Cat playerCat = PlayerInput::CreateCat();
    Wallet playerWallet = Wallet(30, 5s, 10);

    std::thread catStatThread(&Cat::RunCatNeedSimulation, &playerCat);
    std::thread walletThread(&Wallet::GenerateMoneyOverTime, &playerWallet);
    std::thread playerInputThread(PlayerInput::GetPlayerInput, std::ref(playerWallet), std::ref(playerCat));

    //Create some starting Items
    Item("DryFood", CatNeeds::CatNeedEnum::Eat, 15, 1);
    Item("Blanket", CatNeeds::CatNeedEnum::Sleep, 15, 1);
    Item("Mirror", CatNeeds::CatNeedEnum::Social, 15, 1);
    Item("Brush", CatNeeds::CatNeedEnum::Cleanliness, 15, 1);
    Item("String", CatNeeds::CatNeedEnum::Play, 15, 1);

    //Central Loop that keeps game running
    bool isGameRunning = true;
    while (isGameRunning)
    {
        //If the player's cat has run away, the game is over
        if (playerCat.HasCatRunAway())
        {
            isGameRunning = false;
            playerWallet.PauseMoneyProduction();
            PlayerInput::StopGettingPlayerInput();
        }
    };

    //After Cat has run away, show GameOver message
    std::cout << "\n\n\n" << "Your cat has run away! Their needs were not all being met, so they went out on their own.\n";
    std::cout << "Don't worry, they will be ok. You can always play again, and spend more time with them!\n";
    std::cout << "Please try again!" << std::endl;

    //Detach or end all additional coroutines/threads so program doesn't crash
    catStatThread.join();
    walletThread.join();
    playerInputThread.join();

    return 0;
}