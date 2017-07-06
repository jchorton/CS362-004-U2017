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

#define DEBUG 0
#define NOISY_TEST 1


/*
 *	assertTrue
 * This is a customized assert function that will allow the program
 * to keep running when tests fail. This is for using gcov analysis.
 * A label may be sent along with a command to exit if desired.
 */
int assertTrue(int testBool, char *label, int exitBool) {

	// Prints results of tests
	if (testBool)
		printf("PASS");
	else
		printf("FAIL");
	printf(" : %s", label);
	printf("\n");

	// Exit program if desired
	if (!testBool && exitBool) {
		printf("Terminating Program!\n");
		exit(1);
	}
	
	return testBool;
}



/*
 *	main
 */
int main () {

	// Initial card selection
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	struct gameState G;
	
	// initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)
	initializeGame(4, k, 1, &G);

	//printf ("initializeGame(4, k, 1, &G) = %d\n", r);
	//assertTrue(r == 0, "Initilization of game", 0);

	





	return 0;
}
