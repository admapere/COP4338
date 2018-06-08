/* ========================================================================
 * Source Code: players.c
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
 * Description: Contains various functions for the manipulation of player
 *              Hands
 *              The players and their hands are represented via a 2d array
 *              Rows represent players, columns their cards.
 *              Negative numbers represent that a player doesn't have cards
 *              thus:
 *              {2,5,3,12,-1,-1}
 *              {11,4,1,8,1,-1}
 *              Player 1 has 4 cards and is playing a game with a max of 6
 *              Player 2 has 5 cards and is playing a game with a max of 6
 *
 *       Input: none
 *      Output: none
 *     Process: new_hands creates a new hand for the passed player of
 *              size of passed value
 *              add_card takes a drawn card, and adds it to the specified
 *              player's hand.
 *              hand_to_string returns a string representation of a player's
 *              hand.
 *
 * Missing Features: 
 *       Known Bugs: 
 * ======================================================================*/

/*includes*/
#include "card_game.h"
#include <string.h> //memcpy()

/*variables*/
/*Can only be accessed from methods in this file*/
int hands[MAX_PLAYERS][MAX_HAND];

/*functions*/

/* ============ add_card ============
 * function: add_card(int card)
 *
 *  purpose: create new players and set hands to empty.
 *
 *   @param: number_of_players: the total number of players in this game
 *           hand_size: the maximum size of any player's hand
 *
 *  @return: void
 * ========================================*/

void add_card(int player, int card)
{
	int iterator = 0;
	while(hands[player][iterator] >= 0){
		iterator++;
	}//end loop
	hands[player][iterator] = card;
}

/* ============ new_hands ============
 * function: new_hands(int number_of_players, int hand_size)
 *
 *  purpose: create new players and set hands to empty.
 *
 *   @param: number_of_players: the total number of players in this game
 *           hand_size: the maximum size of any player's hand
 *
 *  @return: void
 * ========================================*/

void new_hands(int number_of_players, int hand_size)
{
	#define NO_CARD (-1)
	int player_index = 0;
	int card_index = 0;
	
	for (player_index = 0; player_index < MAX_PLAYERS; player_index++){
		hands[player_index][0] = NO_CARD;

		for(card_index = 0; card_index < MAX_HAND; card_index++){
			hands[player_index][card_index] = NO_CARD;
		}//end loop
	}//end loop
}//end function

/* ============ hand_to_string() ============
 * function: hand_to_string(int player_number)
 *
 *  purpose: return pointner to hand of cards associated with player number
 *           String is large enough to support very large hands
 *
 *   @param: player_number the number of the player requested
 *
 *  @return: pointer to string representation of player's hand
 * ================================*/

char* hand_to_string(int player_number)
{
	#define HAND_BUFFER 200
	static char string[HAND_BUFFER];
	char *cardptr = NULL;
	int index = 0;
	int iterator = 0;
	
	 
	while((index < MAX_HAND) &&  (hands[player_number][index] >= 0) ){
		if(index != 0){
			string[iterator] = ' ';
			iterator++;
		}//end if
		cardptr = card_to_string(hands[player_number][index]);
		memcpy(&string[iterator], cardptr, strlen(cardptr));
		iterator += strlen(cardptr);
		index++;
	}//end loop
	string[iterator] = '\0';
	
	return string;
}//end function
