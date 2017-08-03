/*
 * Author: Jonathan Horton
 * Date:   2017-07-05
 * Desc:   CS362 Assignment 3 -- Creating Unit Tests for dominion.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "assertTrue.h"


/*
 *	main
 */
int main () {

	// Initial card selection
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	struct gameState G;

	// int assertTrue(int testBool, char *label, int exitBool);
	// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);
	initializeGame(2, k, 1, &G);

	printf("\n");
	printf("Testing isGameOver\n");
	printf("------------------\n");
	
	
	assertTrue(isGameOver(&G) == 0, "Game is not over at beginning", 0); 

	G.supplyCount[province] = 0;
	assertTrue(isGameOver(&G) == 1, "Game is over when out of provinces", 0);

	initializeGame(2, k, 1, &G);
	G.supplyCount[0] = 0;
	G.supplyCount[1] = 0;
	assertTrue(isGameOver(&G) == 0, "Game is not over when only two supply piles are empty", 0);
	G.supplyCount[2] = 0;
	assertTrue(isGameOver(&G) == 1, "Game is over when out of three supply piles", 0);


	return 0;
}
