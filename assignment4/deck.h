/*====================================================================
 * Adrian M. Perez
 * 3180957
 * Bill Feild COP4338 - UO1 Programming III
 * Assignment 4 Due March 20, 2018
 *=====================================================================*/

#ifndef DECK_H
#define DECK_H

/*defines*/
#define SUITS 4
#define RANKS 13
#define DECK_SIZE (RANKS * SUITS) 

#include <stdio.h>
#include <stdlib.h> //rand()

/*types*/
typedef struct Card_Struct Card;

/*structures*/
struct Card_Struct
{
	char rank;
	char suit;
};

/*functions*/
char *card_to_string(Card card);
void display_deck();
Card draw_card();
void new_deck();
void shuffle_deck();

#endif /*DECK_H*/
