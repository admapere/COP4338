/* ========================================================================
 * Source Code: players.c
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
 * Description: Player hands are stored statically. Various methods are 
 * 		provided to display and modify the various hands of the
 * 		players.
 *       Input: 
 *      Output: 
 *     Process: 
 *
 * Missing Features:
 *       Known Bugs: 
 * ======================================================================*/
#include "players.h"

Card static hands[MAX_PLAYERS][MAX_HAND];
int static players;
int static size;

/* ============ add_card ============
 * function: add_card(int player, Card card)
 *
 *  purpose: add a drawn card to a player's hand
 *
 *   @param: player hand to be added to
 *           card card to be added
 *
 *  @return:
 * ========================================*/
void add_card(int player, Card card)
{
	int iterator = 0;
	while((hands[player][iterator].rank >= 0) && (iterator < size)){
		iterator++;
	}//end loop
	hands[player][iterator] = card;
}//end function

/* ============ comparator ============
 * function: comparator(void const *first_card, void const *second_card)
 *
 *  purpose: comparison of two different cards to determine order
 *
 *   @param: *first_card a pointer to the first card to be compared
 *           *second_card a pointer to the second card to be compared
 *
 *  @return: relative ordering of both cards
 * ========================================*/
int comparator(void const *first_card, void const *second_card)
{
	int first = (*(Card*)first_card).rank;
	int second = (*(Card*)second_card).rank;
	
	if(first == second){
		first = (*(Card*)first_card).suit;
		second = (*(Card*)second_card).suit;
	}//end if
	return first - second;
}//end function

/* ============ sort ============
 * function: sort()
 *
 *  purpose: place array of cards in ascending order
 *
 *   @param: 
 *
 *  @return: 
 * ========================================*/
void sort()
{
	int player = 0;
	
	for(player = 0; player < players; player++){
		qsort(hands[player], size, sizeof(Card), comparator);
	}//end loop
}//end function

/* ============ new_hands ============
 * function: new_hands(number_of_players, int hand_size)
 *
 *  purpose: creates empty hands of cards
 *
 *   @param: number_of_players amount of players in game.
 *           hand_size the size of each player's hand
 *
 *  @return: 
 * ========================================*/
Card *new_hands(int number_of_players, int hand_size)
{
	#define NULL_CARD (-1)
	players = number_of_players;
	size = hand_size;

	int player = 0;
	int card = 0;

	for(player = 0; player < players; player++){
		for(card = 0; card < size; card++){
			hands[player][card].rank = NULL_CARD;
			hands[player][card].suit = NULL_CARD;
		}//end loop
	}//end loop
	return *hands;
}//end function

/* ============ display_hands ============
 * function: display_hands()
 *
 *  purpose: display the current status of player hands
 *
 *   @param: 
 *
 *  @return: 
 * ========================================*/
void display_hands()
{
	int index = 0;

	for(index = 0; index < players; index++){
		display_player_hand(index);
	}//end loop
}//end function

void display_player_hand(int player)
{
	int card = 0;

	printf("\n%s %d: ","Player",player + 1);
	for(card = 0; card < size; card++){
		fputs(card_to_string(hands[player][card]),stdout);
	}//end loop

	fputc('\0', stdout);
}//end function

