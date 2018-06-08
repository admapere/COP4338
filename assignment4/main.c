/* ========================================================================
 * Source Code: main.c
 *      Author: Adrian M. Perez
 *  Student ID: 3180957
 *  Assignment: Assignment 4
 * 
 *      Course: COP 4338 Programming III
 *     Section: U01
 *  Instructor: Bill Feild
 *    Due Date: March 20, 2018
 *
 *              I hereby certify that this collective work is my own
 *              and none of it is the work of any other person or entity.
 *              _____________________________________________[Signature]
 *
 *    Language: c
 * Compile/Run: make
 *
 * 		alternatively
 *
 * 		$ gcc main.c deck.c players.c stud_poker.c main.h 
 * 		deck.h players.h stud_poker.h -o poker_game.out
 *		$ ./poker_game.out
 *
 * +-----------------------------------------------------------------------
 *
 * Description: Creates a deck of cards and hands for a game of poker
 *       Input: Number of players and accepts input for number of cards
 *      Output: Displays of the deck's contents and the player's hands
 *      	Furthermore, shows which players win the game.
 *     Process: First creates a new deck of cards
 *     		Second creates players' hands
 *     		Third shuffles cards and deals out
 *     		fourth checks to see the various rankings of the hands
 *     		finally determines victors
 *
 * Missing Features: displaying the winner inline would be nice; draws
 * 		     are undecided. No poker hands test.
 *       Known Bugs: 
 * ======================================================================*/
#include "main.h"

int main(int argc, char **argv)
{
	int cards_per_hand = 0;
	int number_of_players = 0;
	Card *hands = NULL;
	srand(time(NULL));

	if(validate(argc, argv) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}//end if
	
	cards_per_hand = CARDS_PER_HAND;
	number_of_players = atoi(argv[2]);

	printf("\n%s\n","Here's a fresh deck!");
	new_deck();
	display_deck();

	printf("\n\n%s\n","Here are this game's players:");
	hands = new_hands(number_of_players, cards_per_hand);
	display_hands();

	printf("\n\n%s\n","This is how the deck was shuffled");
	shuffle_deck();
	display_deck();
	
	printf("\n\n%s\n","This is how the cards were dealt");
	deal(number_of_players, cards_per_hand);
	display_hands();

	printf("\n\n%s\n","Cards are now sorted");
	sort();
	display_hands();

	printf("\n\n%s\n","These are the cards left in the deck");
	display_deck();

	printf("\n\n%s\n","Here are the players' rankings");
	display_ranks(hands, number_of_players, cards_per_hand);

	printf("\n\n%s\n\n","Here are the winners and losers");
	display_winners(number_of_players);

	fputc('\n', stdout);
	
	return EXIT_SUCCESS;
}
/* ============ validate ============
 * function: validate(int argc, char **argv)
 *
 *  purpose: validate user input and print out error messages
 *
 *   @param: argc number of command line inputs
 *           **argv actual parameters passed from command line
 *
 *  @return: int error code
 * ========================================*/

int validate(int argc, char **argv)
{
	int parsed_char = 0;
	
	if(argc != ARGUMENT_COUNT)
	{
		printf("%s\n","ERROR! Not enough arguments");
		printf("%s %s\n","Expected input :", 
                "[number of cards per hand] [number of players]");
		return EXIT_FAILURE;
	}//end if
	
	
	parsed_char = CARDS_PER_HAND;
	if(parsed_char < MIN_HAND || parsed_char > MAX_HAND){
		printf("%s\n","ERROR! Range of first argument incorrect");
		printf("%s %s [%d,%d]\n","Please input only",
		"integers in the range", MIN_HAND, MAX_HAND);
		
		return EXIT_FAILURE;
	}//end if
	
	parsed_char = atoi(argv[2]);
	if(parsed_char < MIN_PLAYERS || parsed_char > MAX_PLAYERS){
		printf("%s\n","ERROR! Range of second argument incorrect");
		printf("%s %s [%d,%d]\n","Please input only",
		"integers in the range", MIN_PLAYERS, MAX_PLAYERS);
		
		return EXIT_FAILURE;
	}//end if
	
	return EXIT_SUCCESS;
}//end function 

/* ============ deal() ============
 * function: deal()
 *
 *  purpose: gives cards to each player from top of the deck
 *
 *   @param: none
 *
 *  @return: void
 * ========================================*/

void deal(int number_of_players, int cards)
{
	int player = 0;

	for(player = 0; player < number_of_players * cards; player++){
		add_card(player % number_of_players, draw_card());
	}//end loop
}//end function
