/* ========================================================================
 * Source Code: card_game.h
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
 *              gcc -o card_game.out deck.c players.c card.c card_game.c
 *              ./card_game.out
 * ======================================================================*/
/*includes*/
#include <stdlib.h> //atoi(), rand(), srand()
#include <string.h> //strlen(), memcpy()
#include <time.h> //srand()
#include <stdio.h>

/*defines*/
#define ARGUMENT_COUNT_ERROR 1
#define ARGUMENT_VALUE_ERROR 2
#define ARGUMENT_COUNT 3
#define DECK_SIZE NUM_OF_SUITS * NUM_OF_RANKS
#define MAX_PLAYERS 13
#define MIN_PLAYERS 1
#define MAX_HAND 13
#define MIN_HAND 1
#define NO_ERROR 0
#define FATAL_ERROR 1
#define NOT_ENOUGH_CARDS_ERROR 3
#define NUM_OF_SUITS 4
#define NUM_OF_RANKS 13

/*enums*/
enum boolean {TRUE, FALSE};

/*prototypes*/
void add_card(int player,int card_number);
char* card_to_string(int card_number);
void deal(int number_of_cards,int cards_per_hand);
char* deck_to_string();
void display_deck(); 
void display_hands(int number_of_players);
int draw_card();
char* hand_to_string(int player_number);
void new_hands(int number_of_players, int hand_size);
void new_deck();
void shuffle_deck();
int validate(int argc, char **argv);
