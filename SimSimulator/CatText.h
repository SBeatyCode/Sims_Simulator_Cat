#pragma once

#include <vector>
#include <string>

//This is a list of flavor text relating to the Cat object. Since the Cat can pick one of many different flavor-text
//options depending on the context, all of the options of things the Cat can do are listed here to avoid having to
//keep track of a list of arbitrary numbers being related to various actions, ect.
namespace CatText
{
//----Default/Error Message----//
#define CAT_DEFAULT "Cats are great."

//----Cat Actions----//
#define CAT_LOOK_PUR " looks up at you and purrs gently."
#define CAT_LOAF " lays down on the ground in a loaf shape."
#define	CAT_MEOW " makes a sweet little meow."
#define CAT_SLOW_BLINK " is blinking slowly at you."
#define CAT_LOOK " is staring at nothing in particular."
#define CAT_FLOP " flops over on the floor."
#define CAT_WINDOW " is looking out the window."
#define CAT_CIRCLES	" is walking in circles around you."

	std::vector<std::string> catActions = {CAT_LOOK_PUR, CAT_LOAF, CAT_MEOW, CAT_SLOW_BLINK, CAT_LOOK, CAT_FLOP, CAT_WINDOW, CAT_CIRCLES};

//---Petting your cat---//
#define PURR_SOFT "They look up at you affectionately and purr softly."
#define SLOW_BLINK "They blink slowly at you."
#define LOW_RESPONSE "They stare at you vacantly. You assume they are appreciative."
#define FLOP_OVER "They flop on the floor and show you their tummy, hoping for more pets."
#define MORE_PETS_PLS "Once you stop petting them, they start batting at you, asking for more pets."
#define PET_CHOMP "They give you an affectionate nibble on your hand."
#define PET_LEAN "They lean into your hand, almost seeming to smile as you pet them."

	std::vector<std::string> catPets = {PURR_SOFT, SLOW_BLINK, LOW_RESPONSE, FLOP_OVER, MORE_PETS_PLS, PET_CHOMP, PET_LEAN};

//---Cat Action to solve its needs---//
#define CLEAN_SELF " is giving themself a bath."
#define SLEEP_SELF " is taking a small cat nap."

//----Using Items----//
#define USE_ITEM "They seem to be happy now."
#define USE_ITEM_DESTROY "It's been torn up, but your kitty is happier."

	std::vector<std::string> itemActions = {USE_ITEM, USE_ITEM_DESTROY};

//???? what was this for? am i keeping this?
//----Looking at Items----//

//----Expressing the Need that needs to be fulfilled----//
#define NEED_DONT_KNOW " is sitting in the middle of the room and meowing angrily." //Kind of a 'Default' or catch-all

//Play
#define PLAY_ZOOMIES " has a case of the zoomies! They're running all over the house!"
#define PLAY_BUG " is distracted by a nearby fly, and is trying to play with it."
#define PLAY_TRASH " has brought you a peice of trash that it found, and is meowing at you."

	std::vector<std::string> playActions = {PLAY_ZOOMIES, PLAY_BUG };
	
//Eat
#define EAT_BOWL " is staring at their empty food bowl."
#define EAT_CRUMBS " is sniffing around on the floor, maybe it's looking for crumbs?"

	std::vector<std::string> eatActions = {EAT_BOWL, EAT_CRUMBS};

//Sleep
#define SLEEP_YAWN " opens their mouth wide and does a big yawn!"
#define SLEEP_CLOSE_EYES " is blinking their eyes slowly, seemingly struggling to stay awake."

	std::vector<std::string> sleepActions = {SLEEP_YAWN, SLEEP_CLOSE_EYES};

//Cleanliness
#define CLEANLINESS_LOOK_LICK " looks at their paw, and gives it a lick. They look up at you and mew."
#define CLEANLINESS_FUR "'s fur is looking a bit messy and dirty."
#define CLEANLINESS_STINKY " is smelling kind of stinky!"

	std::vector<std::string> cleanlinessActions = {CLEANLINESS_LOOK_LICK, CLEANLINESS_FUR, CLEANLINESS_STINKY};

//Social
#define SOCIAL_MEOW " is meowing at you, and staring at you."
#define SOCIAL_FOLLOW " is following you everywhere you walk."

	std::vector<std::string> socialActions = {SOCIAL_MEOW, SOCIAL_FOLLOW };
};