/* ========================================================================
 * Source Code: deck.c
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
 * Description: Functions for the creation and manipulation of a deck.
 *              Deck is represented as an array of unique integers
 *              Deck = {0,1,2,...,DECK_SIZE - 1}
 *              The last index is considered the top of the deck.
 *       Input: none
 *      Output: none
 *     Process: Deck array is stored statically. Every time the new_deck
 *              method is called, the array and pointer to the end are
 *              reset.
 *              The shuffle function uses the Fisher-Yates algorithm
 *              https://en.wikipedia.org/wiki/Fisher-Yates_shuffle
 *              The deck_to_string function makes a string representation of
 *              the deck of cards.
 *
 * Missing Features: 
 *       Known Bugs: 
 * ======================================================================*/

/*Includes*/
#include "card_game.h"

/*Variables*/
int deck[DECK_SIZE];
int top_card_index = 0;

/*Functions*/

/* ============ draw_card ============
 * function: int draw_card()
 * 
 *  purpose: returns int value of the top card of the deck and
 *           moves the index of the top card 1 space
 * 
 *   @param: none
 * 
 *  @return: int value of top card
 * ================================*/

int draw_card()
{
	int top_card = deck[top_card_index];
	top_card_index++;
	return top_card;
}//end function

/* ============ new_deck ============
 * function: void new_deck()
 * 
 *  purpose: initialize an array to {0,1,2,...,lastCard}
 *           in essence, "creating" a new deck of cards
 * 
 *   @param: none
 * 
 *  @return: void
 * ================================*/

void new_deck()
{
	int index = 0;
	top_card_index = 0;

	for(index = 0; index < DECK_SIZE; index++)
	{
		deck[index] = index;
	}//end loop
}//end function

/* ============ shuffle_deck ============
 * function: void shuffle_deck()
 * 
 *  purpose: shuffles deck using the Fisher-Yates shuffle
 *           https://en.wikipedia.org/wiki/Fisher-Yates_shuffle
 * 
 *   @param: none
 * 
 *  @return: void
 * ================================*/

void shuffle_deck()
{
	int shuffled_card = 0;
	int rand_int = 0;
	int index = 0;

	for(index = 0; index < DECK_SIZE; index++)
	{
		rand_int = rand() % (DECK_SIZE);
		shuffled_card = deck[index];
		deck[index] = deck[rand_int];
		deck[rand_int] = shuffled_card;
	}//end loop
}//end function

/* ============ deck_to_string ============
 * function: char* deck_to_string()
 * 
 *  purpose: creates a string representation of the passed deck.
 *           Array has 1000 spaces to represent large decks or multiple
 *           decks.
 * 
 *   @param: none
 * 
 *  @return: string representing the contents of the deck
 * ================================*/

char* deck_to_string()
{
	#define DECK_BUFF  1000
	static char string[DECK_BUFF];
		
	char *card_string = NULL;
	int iterator = 0;
	int loop_counter = 0;
	int index = 0;
	int card_len = 0;
	
	string[0] = '\0'; 
	for(index = top_card_index; index < DECK_SIZE; index++)
	{
		if(loop_counter % NUM_OF_RANKS != 0)
		{
			string[iterator] = ' ';
			iterator++;
		}
		else
		{
			string[iterator] = '\n';
			iterator++;
		}//end if 
		loop_counter++;
		
		card_string = card_to_string(deck[index]);
		card_len = strlen(card_string);
		memcpy(&string[iterator], card_string, card_len);
		iterator += card_len;
		string[iterator] = '\0';
	}//end loop
	
	return string;
}//end function
