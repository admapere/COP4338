/* ========================================================================
 * Source Code: deck.c
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
 * Description: Deck is stored statically. Various functions are provided
 * 		which access the array of cards.
 *       Input: 
 *      Output: 
 *     Process: 
 *
 * Missing Features:
 *       Known Bugs: 
 * ======================================================================*/
#include "deck.h"

Card static deck[DECK_SIZE];
int static top_card_index;

/* ============ card_to_string ============
 * function: card_to_string(Card card)
 *
 *  purpose: represent a Card object as a string
 *
 *   @param: card to be displayed as a string
 *
 *  @return: string representation of card
 * ========================================*/
char *card_to_string(Card card)
{
	#define CARD_BUFF 10
	//utf-8 masks for suits
	char const *SUIT_MASK = "\xE2\x99\xA0\xA5\xA6\xA3";
	char const *RANK_MASK = "A23456789TJQK";
	char static string[CARD_BUFF];
	int iterator = 0;
	
	if(card.rank >= 0){		
		string[iterator] = '[';
		iterator++;
		string[iterator] = RANK_MASK[card.rank];
		iterator++;
		string[iterator] = SUIT_MASK[0];
		iterator++;
		string[iterator] = SUIT_MASK[1];
		iterator++;
		string[iterator] = SUIT_MASK[2 + card.suit];
		iterator++;
		string[iterator] = ']';
		iterator++;
	}//end if
	string[iterator] = '\0';

	return string;
}//end function

/* ============ display_deck() ============
 * function: display_deck()
 *
 *  purpose: display the current deck
 *
 *   @param: 
 *
 *  @return: 
 * ========================================*/
void display_deck()
{
	int loop_counter = 0;
	int index = 0;
	
	fputc('\n',stdout);
	for(index = top_card_index; index < DECK_SIZE; index++){
		if(loop_counter % RANKS == 0 && loop_counter != 0){
			fputc('\n',stdout);
		}//end if
		fputs(card_to_string(deck[index]),stdout);
		loop_counter++;
		if(loop_counter % RANKS !=0){
			fputc(' ',stdout);
		}//end if
	}//end loop
	fputc('\0',stdout);
}//end function

/* ============ draw_card ============
 * function: draw_card()
 *
 *  purpose: returns the top card of the deck
 *
 *   @param: 
 *
 *  @return: Card that top_card_index is pointing to
 * ========================================*/
Card draw_card()
{
	Card top_card = deck[top_card_index];
	top_card_index++;
	return top_card;
}//end function

/* ============ new_deck  ============
 * function: new_deck()
 *
 *  purpose: create a new ordered deck
 *
 *   @param: 
 *
 *  @return: 
 * ========================================*/
void new_deck()
{	
	top_card_index = 0;

	int index = 0;
	for(index = 0; index < DECK_SIZE; index++){
		deck[index].rank = index % RANKS;
		deck[index].suit = index / RANKS;
	}//end loop
}//end function

/* ============ shuffle_deck ============
 * function: shuffle_deck()
 *
 *  purpose: randomize order of previously made deck
 *           uses Fisher-Yates shuffling algorithm
 *           https://en.wikipedia.org/wiki/Fisher-Yates_shuffle
 *
 *   @param: 
 *
 *  @return: 
 * ========================================*/
void shuffle_deck()
{
	Card shuffled_card = {0,0};
	int rand_int = 0;

	int index = 0;
	for(index = 0; index < DECK_SIZE; index++){
		rand_int = rand() % DECK_SIZE;
		shuffled_card = deck[index];
		deck[index] = deck[rand_int];
		deck[rand_int] = shuffled_card;
	}//end loop
}//end function
