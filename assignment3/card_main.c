/* ========================================================================
 * Source Code: card_main.c
 *      Author: Adrian Manuel Perez
 *  Student ID: 3180957
 *  Assignment: Assignment #3
 * 
 *      Course: COP 4338 Programming III
 *     Section: U01
 *  Instructor: Bill Feild
 *    Due Date: February 22, 2018
 *
 *              I hereby certify that this collective work is my own
 *              and none of it is the work of any other person or entity.
 *              _____________________________________________[Signature]
 *
 *    Language: C
 * Compile/Run: make
 *              ./card_game.out
 *              
 *              ALTERNATIVELY
 *
 *              gcc -o card_game.out deck.c players.c card.c card_main.c
 *              ./card_game.out
 * +-----------------------------------------------------------------------
 *
 * Description: Creates a deck of cards, shuffles it, and then deals it to 
 *              each player.
 *       Input: command line input is two values ranging from
 *              MIN_PLAYERS to MAX_PLAYERS.
 *      Output: Display of the deck of cards after being created, shuffled
 *              and dealt. Furthermore, displays each player's hand.
 *     Process: Each of the functions that start with the word "new
 *              behave like the "new" operator in Object Oriented
 *              languages. They initialize arrays of their type.
 *
 *              The various display methods display the data from the
 *              associated type. The data all live statically on the stack
 *
 * Missing Features: 
 *       Known Bugs: sometimes when compiling a clock skew is detected.
 *                   not sure what that affects or why it happens but
 *                   it hasn't caused any issues I know of. 
 * ======================================================================*/

/*includes*/
#include "card_game.h"

int main(int argc, char **argv)
{
	srand(time(NULL));
	int proceed = validate(argc, argv);
	if(proceed != TRUE)
	{
		return FATAL_ERROR;
	}//end if
	
	int cards_per_hand = atoi(argv[1]);
	int number_of_players = atoi(argv[2]);
	int total_cards = number_of_players * cards_per_hand;

	printf("\n%s\n","Here's a fresh deck! The last card is the top");
	new_deck();
	display_deck();

	printf("\n%s\n","Here are this game's players:");
	new_hands(number_of_players, cards_per_hand);
	display_hands(number_of_players);

	printf("\n%s\n","This is how the deck was shuffled");
	shuffle_deck();
	display_deck();
	
	printf("\n%s\n","This is how the cards were dealt");
	deal(number_of_players,cards_per_hand);
	display_hands(number_of_players);
	
	printf("\n%s\n","These are the cards left in the deck");
	display_deck();
	
	return NO_ERROR;
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
	int index = 0;
	int total_cards = 1;
	int parsed_char = 0;
	
	if(argc != ARGUMENT_COUNT)
	{
		printf("%s\n","ERROR! Not enough arguments");
		printf("%s %s\n","Expected input :", 
                "[number of cards per hand] [number of players]");
		return ARGUMENT_COUNT_ERROR;
	}//end if
	
	for(index = 1; index < ARGUMENT_COUNT; index++)
	{
		parsed_char = atoi(argv[index]);
		total_cards *= parsed_char;

		if(parsed_char < MIN_PLAYERS || parsed_char > MAX_PLAYERS){
			printf("%s\n","ERROR! Range of argument incorrect");
			printf("%s %s\n","Please input only",
                         "integers in the range [1,13]");
			return ARGUMENT_VALUE_ERROR;
		}//end if
	}//end loop

	if(total_cards > DECK_SIZE)
	{
		printf("%s\n","ERROR! too many cards per hand or players!");
		printf("%s %s %d\n","Please make sure the",
                "product of both input values is less than",DECK_SIZE);
		return NOT_ENOUGH_CARDS_ERROR;
	}//end if
	
	return NO_ERROR;
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

void deal(int number_of_players,int cards_per_hand)
{
	int cards_dealt = 0;
	int card = 0;
	int total_cards = number_of_players * cards_per_hand;
	for(cards_dealt = 0; cards_dealt < total_cards; cards_dealt++)
	{
		card = draw_card();
		add_card(cards_dealt % number_of_players,card);
	}//end loop
}//end function

/* ============ display_hands() ============
 * function: display_hands()
 *
 *  purpose: displays the hands of all the players
 *
 *   @param: none
 *
 *  @return: void
 * ========================================*/

void display_hands(int number_of_players)
{
	int player_number = 0;
	
	putc('\n',stdout);
	for(player_number = 0; player_number < number_of_players;
            player_number++){
		printf("%s %d: %s\n","Player", player_number + 1,
                hand_to_string(player_number));
	}//endloop
}//end function

/* ============ display_deck ============
 * function: display_deck()
 *
 *  purpose: displays cards in the deck
 *
 *   @param: none
 *
 *  @return: void
 * ========================================*/

void display_deck()
{
	printf("%s\n",deck_to_string());
}//end function
