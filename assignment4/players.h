/*====================================================================
 * Adrian M. Perez
 * 3180957
 * Bill Feild COP4338 - UO1 Programming III
 * Assignment 4 Due March 20, 2018
 *=====================================================================*/

#ifndef PLAYERS_H
#define PLAYERS_H

/*defines*/
#define MIN_PLAYERS 1
#define MAX_PLAYERS 7
#define MIN_HAND 1
#define MAX_HAND 5

#include <stdio.h>
#include <stdlib.h> //qsort()
#include "deck.h" //Card

/*functions*/
void add_card(int player, Card card);
int comparator(void const* first_card, void const* second_card);
void display_hands();
void display_player_hand(int player);
Card *new_hands(int number_of_players, int size);
void sort();

#endif /*PLAYERS_H*/
