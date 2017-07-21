/*
 * Author: Jonathan Horton
 * Date:   2017-07-20
 * Desc:   CS362 Assignment 4 -- Random Tests for dominion.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"
//#include "assertTrue.h"

#define DEBUG 0
#define NOISY_TEST 1

// We expect to gain up to 2 additional cards so long as we have two treasury cards,
// then discard the Adventurer card when done searching
int checkAdventurerCard(int p, struct gameState *post) {
	
	// Make a copy of the recieved gameState
	struct gameState pre;
	memcpy( &pre, post, sizeof(struct gameState) );
	
	// Choose random card position in hand
	int handPos = floor(Random() * post->handCount[p]);

	// Call Adventurer card!
	int resultStatus;
	resultStatus = actionAdventurer(post, handPos);

	// Ensure correct values
	// TODO: Need to do a bool check that has no output, maybe
	// Also keep in mind that this value should just be +1
	assert(pre.handCount[p] + 2 == post->handCount[p]);


	return resultStatus;
}


/*
 *	main
 */
int main () {


	// Initial card selection
	//int k[10] = {adventurer, council_room, feast, gardens, mine,
	//	remodel, smithy, village, baron, great_hall};

	struct gameState G;
	printf ("Testing Adventurer Card with random tests\n");

	// Initailizing RNG
	//TestRandom(); // Makes sure RNG is working correctly
	SelectStream(1);
	PutSeed(1);

	int n, i, p;
	for (n = 0; n < 2000; n++) {
		printf("Beginning test %d\n", n);

		// Fills gameState with entirely random junk characters
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 4); // sets player number

		// 27 cards, with enumed values of 0 to 26
		// replace critical values to be a bit more limited
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		G.whoseTurn = p;
		
		
		for (i = 0; i < G.handCount[p]; i++)
			G.hand[p][i] = floor(Random() * 27);
		for (i = 0; i < G.deckCount[p]; i++)
			G.deck[p][i] = floor(Random() * 27);
		for (i = 0; i < G.discardCount[p]; i++)
			G.discard[p][i] = floor(Random() * 27);

		checkAdventurerCard(p, &G);
	}

	printf ("ALL TESTS OK\n");

	return 0;
}
