/*
 * Author: Jonathan Horton
 * Date:   2017-07-05
 * Desc:   CS362 Assignment 3 -- Creating Unit Tests for dominion.c
 * 	   This is based on the included file "supplyTest.c".
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "assertTrue.h"

#define DEBUG 0
#define NOISY_TEST 1

/*
 *	main
 */
int main () {

	// Initial card selection
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	struct gameState G;
	
	// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);
	int r;
	r = initializeGame(4, k, 1, &G);

	printf ("initializeGame(4, k, 1, &G) = %d\n", r);
	
	// int asserTrue(int testBool, char *label, int exitBool);
	assertTrue(r == 0, "Initilization of game", 0);


	return 0;
}
