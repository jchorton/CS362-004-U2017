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
	printf("Testing shuffle\n");
	printf("---------------\n");
	
	assertTrue(G.deckCount[0] == 5, "Player 1 deck count is 5 before shuffle", 0);
	assertTrue(G.deckCount[1] == 10, "Player 2 deck count is 10 before shuffle", 0);

	printf("\nShuffling Player 1 deck...\n");
	shuffle(0, &G);
	assertTrue(G.deckCount[0] == 5, "Player 1 deck count is 5 after shuffle", 0);
	assertTrue(G.deckCount[1] == 10, "Player 2 deck count is 10 after shuffle", 0);

	printf("\nAdding 3 cards to player 1 discard pile and shuffling...\n");
	G.discardCount[0] = 3;
	shuffle(0, &G);
	assertTrue(G.deckCount[0] == 5, "Player 1 deck count is still 5 after shuffle", 0);
	assertTrue(G.discardCount[0] == 3, "Player 1 discard count is still 3 after shuffle", 0);


	return 0;
}
