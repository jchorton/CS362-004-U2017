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

	struct gameState oldG;
	struct gameState newG;

	// int assertTrue(int testBool, char *label, int exitBool);
	// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);
	initializeGame(2, k, 1, &oldG);
	initializeGame(2, k, 1, &newG);


	printf("\n");
	printf("Testing actionCouncilRoom\n");
	printf("-------------------------\n");
	
	actionCouncilRoom(&newG, 0);


	// Council Room requirements:
	// 1. Current player should receive exactly 4 cards.
	// 2. 4 cards should come from his own pile.
	// 3. Number of buys for this turn should increase by +1.
	// 3. Other players should draw a card from their respective piles.
	// 4. No state change should occur to the victory card piles and kingdom card piles.
	

	// Expect to lose 1 card but gain 3 (at least at beginning of game)
	assertTrue(oldG.handCount[0] + 3 == newG.handCount[0], "Adds net three cards to player hand", 0);
	assertTrue(oldG.deckCount[0] - 4 == newG.deckCount[0], "Removes four cards from player deck", 0);

	assertTrue(oldG.handCount[1] + 1 == newG.handCount[1], "Other player hand count + 1", 0);
	assertTrue(oldG.deckCount[1] - 1 == newG.deckCount[1], "Other player deck count - 1", 0);

	printf("\nChecking all supply counts...\n");
	int i;
	char buffer[1024];
	for (i = 0; i < treasure_map+1; i++) {
		sprintf(buffer, "Same supply count for card %d", i);
		assertTrue(oldG.supplyCount[i] == newG.supplyCount[i], buffer, 0);
	}

	printf("\nChecking boundary where current player deck count is only 1...\n");
	initializeGame(2, k, 1, &newG);
	newG.deckCount[0] = 1;
	actionCouncilRoom(&newG, 0);
	assertTrue(oldG.handCount[0] == newG.handCount[0], "Hand size remains the same", 0);
	assertTrue(newG.deckCount[0] == 0, "Deck count is set to zero", 0);

	printf("\nChecking boundary where current player deck count is 0...\n");
	initializeGame(2, k, 1, &newG);
	newG.deckCount[0] = 0;
	actionCouncilRoom(&newG, 0);
	assertTrue(oldG.handCount[0] - 1 == newG.handCount[0], "Hand size goes down by 1", 0);
	assertTrue(newG.deckCount[0] == 0, "Deck count is set to zero", 0);

	printf("\nChecking boundary where other player deck count is 0...\n");
	initializeGame(2, k, 1, &newG);
	newG.deckCount[1] = 0;
	actionCouncilRoom(&newG, 0);
	assertTrue(oldG.handCount[1] == newG.handCount[1], "Other player hand size stays the same", 0);
	assertTrue(newG.deckCount[1] == 0, "Other player deck count remains at 0", 0);



	return 0;
}
