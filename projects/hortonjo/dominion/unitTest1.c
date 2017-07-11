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
	
	// Since we need to initialize the game for everything else, so let's start with that one!

	// int assertTrue(int testBool, char *label, int exitBool);
	// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);
	int r;
	
	printf("\n");
	printf ("Testing initializeGame with 2, 3, and 4 players\n");
	printf ("-----------------------------------------------\n");
	r = initializeGame(2, k, 1, &G);
	assertTrue(r == 0, "initializeGame returns 0", 0);
	assertTrue(G.numPlayers == 2, "Number of players set to 2", 0);
	assertTrue(G.supplyCount[curse] == 10, "Number of curse cards set to 10", 0);
	assertTrue(G.supplyCount[estate] == 8, "Number of estate cards set to 8", 0);
	assertTrue(G.supplyCount[duchy] == 8, "Number of duchy cards set to 8", 0);
	assertTrue(G.supplyCount[province] == 8, "Number of province cards set to 8", 0);
	assertTrue(G.supplyCount[copper] == 46, "Number of copper cards set to 46", 0);
	assertTrue(G.supplyCount[silver] == 40, "Number of silver cards set to 40", 0);
	assertTrue(G.supplyCount[gold] == 30, "Number of gold cards set to 30", 0);
	
	printf("\n");
	r = initializeGame(3, k, 1, &G);
	assertTrue(r == 0, "initializeGame returns 0", 0);
	assertTrue(G.numPlayers == 3, "Number of players set to 3", 0);
	assertTrue(G.supplyCount[curse] == 20, "Number of curse cards set to 20", 0);
	assertTrue(G.supplyCount[estate] == 12, "Number of estate cards set to 12", 0);
	assertTrue(G.supplyCount[duchy] == 12, "Number of duchy cards set to 12", 0);
	assertTrue(G.supplyCount[province] == 12, "Number of province cards set to 12", 0);
	assertTrue(G.supplyCount[copper] == 39, "Number of copper cards set to 39", 0);
	assertTrue(G.supplyCount[silver] == 40, "Number of silver cards set to 40", 0);
	assertTrue(G.supplyCount[gold] == 30, "Number of gold cards set to 30", 0);

	printf("\n");
	r = initializeGame(4, k, 1, &G);
	assertTrue(r == 0, "initializeGame returns 0", 0);
	assertTrue(G.numPlayers == 4, "Number of players set to 4", 0);
	assertTrue(G.supplyCount[curse] == 30, "Number of curse cards set to 30", 0);
	assertTrue(G.supplyCount[estate] == 12, "Number of estate cards set to 12", 0);
	assertTrue(G.supplyCount[duchy] == 12, "Number of duchy cards set to 12", 0);
	assertTrue(G.supplyCount[province] == 12, "Number of province cards set to 12", 0);
	assertTrue(G.supplyCount[copper] == 32, "Number of copper cards set to 39", 0);
	assertTrue(G.supplyCount[silver] == 40, "Number of silver cards set to 40", 0);
	assertTrue(G.supplyCount[gold] == 30, "Number of gold cards set to 30", 0);

	return 0;
}
