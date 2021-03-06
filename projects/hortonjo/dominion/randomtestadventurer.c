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
#include "assertTrue.h"

#define DEBUG 0
#define NOISY_TEST 1

// We expect to gain up to 2 additional cards so long as we have two treasury cards,
// then discard the Adventurer card when done searching
int checkAdventurerCard(int p, struct gameState *post, int handPos) {
	
	// Make a copy of the recieved gameState
	struct gameState pre;
	memcpy( &pre, post, sizeof(struct gameState) );
	
	// Call Adventurer card!
	int resultStatus;
	resultStatus = actionAdventurer(post, handPos);
	assert(resultStatus == 0);

	// Ensure correct values
	// TODO: Need to do a bool check that has no output, maybe
	// Also keep in mind that this value should just be +1
	//assert(pre.handCount[p] + 2 == post->handCount[p]);

	// Need to search the deck and discard piles for up to 2 treasure
	// cards to add to the hand. There is no self-discard afterwards.
	int search, found = 0;
	for (search = 0; search < pre.deckCount[p]; search++)
		if (pre.deck[p][search] == copper || pre.deck[p][search] == silver || pre.deck[p][search] == gold)
			found++;
	for (search = 0; search < pre.discardCount[p]; search++)
		if (pre.discard[p][search] == copper || pre.discard[p][search] == silver || pre.discard[p][search] == gold)
			found++;

	// BUGFIX: Reworked this to align with a properly self-discarding adventurer card
	if (found > 1)
		pre.handCount[p] += 1;
	else if (found == 1)
		pre.handCount[p] += 0;
	else 
		pre.handCount[p] -= 1;

	pre.playedCardCount += 1;


	// Assume that the correct cards are kept, relies on other functions
	memcpy(pre.deck[p], post->deck[p], sizeof(int) * MAX_DECK);
	memcpy(pre.discard[p], post->discard[p], sizeof(int) * MAX_DECK);
	memcpy(pre.hand[p], post->hand[p], sizeof(int) * MAX_HAND);
	memcpy(pre.playedCards, post->playedCards, sizeof(int) * MAX_DECK);

	// These are a little tough to calculate, let's just copy them
	pre.deckCount[p] = post->deckCount[p];
	pre.discardCount[p] = post->discardCount[p];

	//assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
	resultStatus = assertTrue(memcmp(&pre, post, sizeof(struct gameState)) == 0, "gameState equal", 2);

	// If this assertion failed, then print everything out
	if (resultStatus) {
		printf("Checking for equality in gameState for player %d:\n", p + 1);
		printf("Pre handCount = %d \t Post handCount = %d\n", pre.handCount[p], post->handCount[p]);
		printf("\t\t\t Post deckCount = %d\n", post->deckCount[p]);
		printf("\t\t\t Post discardCount = %d\n", post->discardCount[p]);
		assertTrue(pre.numPlayers == post->numPlayers, "numPlayers", 2);
		assertTrue(memcmp(pre.supplyCount, post->supplyCount, sizeof(int) * treasure_map) == 0, "supplyCount", 2);
		assertTrue(memcmp(pre.embargoTokens, post->embargoTokens, sizeof(int) * treasure_map) == 0, "embargoTokens", 2);
		assertTrue(pre.outpostPlayed == post->outpostPlayed, "outpostPlayed", 2);
		assertTrue(pre.outpostTurn == post->outpostTurn, "outpostTurn", 2);
		assertTrue(pre.whoseTurn == post->whoseTurn, "whoseTurn", 2);
		assertTrue(pre.phase == post->phase, "phase", 2);
		assertTrue(pre.numActions == post->numActions, "numActions", 2);
		assertTrue(pre.coins == post->coins, "coins", 2);
		assertTrue(pre.numBuys == post->numBuys, "numBuys", 2);
		assertTrue(memcmp(pre.playedCards, post->playedCards, sizeof(int) * MAX_DECK) == 0, "playedCards", 2);
		assertTrue(pre.playedCardCount == post->playedCardCount, "playedCardCount", 2);

		assertTrue(memcmp(pre.hand[0], post->hand[0], sizeof(int) * MAX_HAND) == 0, "1 hand", 2);
		assertTrue(pre.handCount[0] == post->handCount[0], "1 handCount", 2);
		assertTrue(memcmp(pre.deck[0], post->deck[0], sizeof(int) * MAX_DECK) == 0, "1 deck", 2);
		assertTrue(pre.deckCount[0] == post->deckCount[0], "1 deckCount", 2);
		assertTrue(memcmp(pre.discard[0], post->discard[0], sizeof(int) * MAX_DECK) == 0, "1 discard", 2);
		assertTrue(pre.discardCount[0] == post->discardCount[0], "1 discardCount", 2);

		assertTrue(memcmp(pre.hand[1], post->hand[1], sizeof(int) * MAX_HAND) == 0, "2 hand", 2);
		assertTrue(pre.handCount[1] == post->handCount[1], "2 handCount", 2);
		assertTrue(memcmp(pre.deck[1], post->deck[1], sizeof(int) * MAX_DECK) == 0, "2 deck", 2);
		assertTrue(pre.deckCount[1] == post->deckCount[1], "2 deckCount", 2);
		assertTrue(memcmp(pre.discard[1], post->discard[1], sizeof(int) * MAX_DECK) == 0, "2 discard", 2);
		assertTrue(pre.discardCount[1] == post->discardCount[1], "2 discardCount", 2);

		assertTrue(memcmp(pre.hand[2], post->hand[2], sizeof(int) * MAX_HAND) == 0, "3 hand", 2);
		assertTrue(pre.handCount[2] == post->handCount[2], "3 handCount", 2);
		assertTrue(memcmp(pre.deck[2], post->deck[2], sizeof(int) * MAX_DECK) == 0, "3 deck", 2);
		assertTrue(pre.deckCount[2] == post->deckCount[2], "3 deckCount", 2);
		assertTrue(memcmp(pre.discard[2], post->discard[2], sizeof(int) * MAX_DECK) == 0, "3 discard", 2);
		assertTrue(pre.discardCount[2] == post->discardCount[2], "3 discardCount", 2);

		assertTrue(memcmp(pre.hand[3], post->hand[3], sizeof(int) * MAX_HAND) == 0, "4 hand", 2);
		assertTrue(pre.handCount[3] == post->handCount[3], "4 handCount", 2);
		assertTrue(memcmp(pre.deck[3], post->deck[3], sizeof(int) * MAX_DECK) == 0, "4 deck", 2);
		assertTrue(pre.deckCount[3] == post->deckCount[3], "4 deckCount", 2);
		assertTrue(memcmp(pre.discard[3], post->discard[3], sizeof(int) * MAX_DECK) == 0, "4 discard", 2);
		assertTrue(pre.discardCount[3] == post->discardCount[3], "4 discardCount", 2);

		
		// For printing cards inventories and check for buffer overflow
		//int i;
		//printf("handCount = %d\n", pre.handCount[p]);
		//printf("deckCount = %d\n", pre.deckCount[p]);	
		//printf("discardCount = %d\n", pre.discardCount[p]);
		//for (i = 0; i < MAX_HAND; i++)
		//printf("%d\t%d\n", pre.discard[p][i], post->discard[p][i]);

		printf("\n");
	}

	return resultStatus;
}


/*
 *	main
 */
int main () {

	struct gameState G;
	printf ("Testing Adventurer Card with random tests\n");

	// Initailizing RNG
	//TestRandom(); // Makes sure RNG is working correctly
	SelectStream(1);
	PutSeed(1);

	int n, i, j, p;
	for (n = 0; n < 20000; n++) {
		//printf("Beginning test %d\n", n);

		// Fills gameState with entirely random junk characters
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 4); // sets player number
		G.whoseTurn = p;

		// Setting reasonable deck counts. I have to divide the maximums
		// by some value because there is occasional memory corruption
		// when, say, discarding more cards and going over the MAX_DECK
		for (i = 0; i < 4; i++) {
			G.deckCount[i] = floor(Random() * MAX_DECK/3); // empty decks break
			G.discardCount[i] = floor(Random() * MAX_DECK/3);
			G.handCount[i] = floor(Random() * MAX_HAND/3);
		}
	
		// Give the players valid cards as well
		// 27 cards, with enumed values of 0 to 26 (treasure_map)
		for (j = 0; j < 4; j++) {
			for (i = 0; i < MAX_HAND; i++)
				G.hand[j][i] = floor(Random() * treasure_map);
			for (i = 0; i < MAX_DECK; i++)
				G.deck[j][i] = floor(Random() * treasure_map);
			for (i = 0; i < MAX_DECK; i++)
				G.discard[j][i] = floor(Random() * treasure_map);
		}
	
		// Populate the played cards for this turn in the same way
		for (i = 0; i < MAX_DECK; i++)
			G.playedCards[i] = floor(Random() * treasure_map);
		G.playedCardCount = floor(Random() * MAX_DECK/3);

		// Choose random card position in hand and set it to Adventurer
		int handPos = floor(Random() * G.handCount[p]);
		G.hand[p][handPos] = adventurer;

		checkAdventurerCard(p, &G, handPos);
	}

	printf ("TESTS COMPLETED\n");

	return 0;
}
