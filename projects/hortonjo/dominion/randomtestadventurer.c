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

int checkDrawCard(int p, struct gameState *post) {
	int r;

	r = drawCard (p, post);
	assert(r == 0);

	return 0;
}

// We expect to gain up to 2 net cards so long as we have two treasury cards,
// then discard the Adventurer card when done searching
int checkAdventurerCard(int p, struct gameState *pre, struct gameState *post, int handPos) {
	
	
	// Call the card to test
	actionAdventurer(&post, handPos);

	// Ensure correct values
	assert(pre.handCount[p] + 1 == post.handCount[p]);


	return 0;
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

	int n, i, p, handPos;
	for (n = 0; n < 2000; n++) {
		// TODO: Need to somehow randomize initialize?
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 4);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		handPos = floor(Random() * G.handCount[p]);
		checkAdventurerCard(p, &G, handPos);
	}

	printf ("ALL TESTS OK\n");

	return 0;
}
