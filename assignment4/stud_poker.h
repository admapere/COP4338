/*====================================================================
 * Adrian M. Perez
 * 3180957
 * Bill Feild COP4338 - UO1 Programming III
 * Assignment 4 Due March 20, 2018
 *=====================================================================*/

#ifndef STUD_POKER_H
#define STUD_POKER_H


/*defines*/
#define CARDS_PER_HAND 5

#include <stdio.h>
#include <limits.h> //MAX_INT
#include "players.h" //MAX_PLAYERS
#include "deck.h"

/*enumerations*/
enum Poker_Ranks
{
	NOT_STRAIGHT_FLUSH = 128,
	NOT_FOUR_OF_A_KIND = 64,
	NOT_FULL_HOUSE = 32,
	NOT_FLUSH = 16,
	NOT_STRAIGHT = 8,
	NOT_THREE_OF_A_KIND = 4,
	NOT_TWO_PAIR = 2,
	NOT_ONE_PAIR = 1,
};

/*prototypes*/
int determine_hand(Card player[], int length);
void display_ranks(Card hands[],int number_of_players,int cards_per_player);
void display_winners(int number_of_players);

#endif /*STUD_POKER_H*/
