# Sims_Simulator_Cat
A console app that's somwhere between a Tamogatchi The Sims. Raise your Cat and don't let it run away!

I was inspired to create something similar to The Sims as a console app, so my solution was to create this project. The player has a cat, which they name, who has their own set of stats which decrease over time. The player has money, which will slowly increase over time. The user needs to pay attention to the things that the cat is doing and saying, in order to figure out what it's hinting that it needs. Although being a cat, sometimes it'll just do a random thing and ot be especiallly helpful in telling you what it needs. Taking this information, the player then needs to go to the shop, where they can make any kind of item they like to fullfill any kind of need for the cat, at a desired power-level. The stronger the item, the more expensive it is. Some of the cat's needs it can be somewhat self-sufficient, and take of itself (it can take a nap on it's own, it can clean itself). If 2 of the cat's stats drop down to 0, then the cat will run away and the game is over. The game is tuned to be pretty easy, the player would basically need to do nothing in order to lose, but these variables could all easily be changed to make it more challenging. The goal wasn't for it to be difficult, but moreso to see how closely I could replicate the experience of owning a cat as a console app.

Below is the in-code comment where I describe my outlined idea for this poject. Not ever feature made it into the final project, because I wanted to be sure to keep it within a reasonable scope and didn't just keep adding more and more to it. I alos listed some additional features I thought of that I would have ideally liked to have added, but again, I didn't want to spend too long making this.

One improvement it definitely needs is to have the console-logging thread locked when the player is typing, so that the cat messages don't interupt the player typing. This was my first attempt at making a multi-treaded project in C++, so there are probably more areas where I could improve as well.

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
