/* ========================================================================
 * Source Code: card.c
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
 * Description: Helper functions describing cards of a deck
 *       Input: none
 *      Output: none
 *     Process: returns a string representation of a card
 *
 * Missing Features: 
 *       Known Bugs: 
 * ======================================================================*/
#include "card_game.h"

/* ============ card_to_string ============
 * function: char card_to_string(int card_number)
 * 
 *  purpose: constructs a string representation of a card
 *           Ace of Hearts = [A♥]
 * 
 *   @param: card_number unique identifing number for a card.
 * 
 *  @return: string representation of a card.
 * ================================*/

char *card_to_string(int card_number)
{
	#define CARD_BUFF 10
	//utf-8 masks for suits
	const char *SUIT_MASK = "\xE2\x99\xA0\xA5\xA6\xA3";
	const char *RANK_MASK = "A23456789TJQK";
	static char string[CARD_BUFF];
	int card_rank = 0;
	int card_suit = 0;
	int iterator = 0;
			
	card_rank = card_number % NUM_OF_RANKS;
	card_suit = card_number / NUM_OF_RANKS;

	string[iterator] = '[';
	iterator++;
	string[iterator] = RANK_MASK[card_rank];
	iterator++;
	string[iterator] = SUIT_MASK[0];
	iterator++;
	string[iterator] = SUIT_MASK[1];
	iterator++;
	string[iterator] = SUIT_MASK[2 + card_suit];
	iterator++;
	string[iterator] = ']';
	iterator++;
	string[iterator] = '\0';

	return string;
}
