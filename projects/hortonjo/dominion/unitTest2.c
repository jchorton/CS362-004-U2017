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

	int r;
	printf("\n");
	printf("Testing whoseTurn\n");
	printf("-----------------\n");
	r = whoseTurn(&G);
	assertTrue(r == G.whoseTurn, "Returned value matches what's stored", 0); 
	
	endTurn(&G);

	r = whoseTurn(&G);
	assertTrue(r == G.whoseTurn, "Still matches after ending the turn", 0);


	return 0;
}
