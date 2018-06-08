/* ========================================================================
 * Source Code: stud_poker.c
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
 * Description: Array indicates position of players that win
 *       Input: 
 *      Output: 
 *     Process: 
 *
 * Missing Features:
 *       Known Bugs: 
 * ======================================================================*/
#include "stud_poker.h"

int static winners[MAX_PLAYERS];
int static highest_rank = INT_MAX;

/* ======== determine_hand ========
 * function: int determine_hand(Card player[])
 *
 *  purpose: ranks input hand
 *
 *   @param: Card a player's hand
 *
 *  @return: relative rank of input hand
 * ==============================*/
int determine_hand(Card player[], int length)
{
	char unsigned hand_rank = 0;
	int pairs = 0;
	int triples = 0;
	int quads = 0;
	
	int index = 0;
	int sub_index = 0;

	for(index = length - 1; index > 0; index--){
		if((player[index].rank - player[index - 1].rank) != 1){
			hand_rank |= NOT_STRAIGHT_FLUSH;
			hand_rank |= NOT_STRAIGHT;
		}//end if

		if(player[index].suit - player[index - 1].suit != 0){
			hand_rank |= NOT_FLUSH;
		}//end if
		
		if(index >= 3 &&
		player[index].rank == player[index - 3].rank){
			quads++;
			index -= 3;
		}//end if
		if(index >= 2 && 
		player[index].rank == player[index - 2].rank){
			triples++;
			index -= 2;
		}//end if
		if(player[index].rank == player[index - 1].rank){
			pairs++;
			index -= 1;
		}//end if
	}//end loop

	if(quads == 0){
		hand_rank |= NOT_FOUR_OF_A_KIND;
	}
	if(triples == 0){
		hand_rank |= NOT_FULL_HOUSE;
		hand_rank |= NOT_THREE_OF_A_KIND;
	}
	if(pairs == 0){
		hand_rank |= NOT_FULL_HOUSE;
		hand_rank |= NOT_TWO_PAIR;
		hand_rank |= NOT_ONE_PAIR;
	}
	if(pairs == 1){
		hand_rank |= NOT_TWO_PAIR;
	}

	index = 0;
	while(hand_rank > 127){
		hand_rank <<= 1;
		index++;
	}//end loop
	return index;
}//end function

/* ============ display_ranks ============
 * function: display_ranks(Card hands[],
 * 			   int number_of_players, int cards_per_hand)
 *
 *  purpose: display the ranking of all player hands
 *
 *   @param: array of hands
 *           number of players in game
 *           cards per person
 *
 *  @return:
 * ========================================*/
void display_ranks(Card hands[], int number_of_players, int cards_per_hand)
{
	const char* POKER_HAND_RANKS[] = 
	{
		"Straight Flush", "Four of a Kind", "Full House", "Flush",
		"Straight", "Three of a Kind", "Two Pair", "One Pair",
		"High Card"
	};

	int index = 0;
	int rank = 0;
	int hand = 0; 

	for(index = 0; index < number_of_players; index++){
		hand = index * cards_per_hand;
		rank = determine_hand(&hands[hand], cards_per_hand);
		display_player_hand(index);
		printf(" -%-10s-", POKER_HAND_RANKS[rank]);
		
		winners[index] = rank;
		if(rank < highest_rank){
			highest_rank = rank;
		}
	}//end loop
}//end function

/* ============ display_winners ============
 * function: display_winners(int number_of_players)
 *
 *  purpose: display the winners of the game
 *
 *   @param: number of players in game
 *           
 *  @return:
 * ========================================*/

void display_winners(int number_of_players)
{
	int index = 0;

	for(index = 0; index < number_of_players; index++){
		if(winners[index] == highest_rank){
			printf("%s %d: %s\n","Player", index + 1, "wins!"); 
		}else{
			printf("%s %d: %s\n","Player", index + 1, 
			"better luck next time!");
		}//end if
	}//end loop	
}//end function
