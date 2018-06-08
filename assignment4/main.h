/*====================================================================
 * Adrian M. Perez
 * 3180957
 * Bill Feild COP4338 - UO1 Programming III
 * Assignment 4 Due March 20, 2018
 *=====================================================================*/

#ifndef MAIN_H
#define MAIN_H

/* Defines */
#define ARGUMENT_COUNT 3

/* Includes */
#include <stdio.h>
#include <stdlib.h> //srand()
#include <time.h> //time()
#include "deck.h"
#include "players.h"
#include "stud_poker.h"

/* Functions */
void deal(int number_of_players, int cards_per_hand);
int validate(int argc, char **argv);

#endif /* MAIN_H */
