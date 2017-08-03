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
	//printf("Testing actionAdventurer\n");
	printf("Testing AdventurerEffect\n");
	printf("------------------------\n");
	

	// FIXME: Refactoring here, must add prototype and new call
	//actionAdventurer(&newG, 0);
	int AdventurerEffect(int currentPlayer, int handPos, struct gameState *state);

	AdventurerEffect(newG.whoseTurn, 0, &newG);


	// Adventurer requirements:
	// 1. Current player should get up to 2 cards.
	// 2. The 2 cards should come from his own pile.
	// 3. No state change should occur for other players.
	// 4. No state change should occur to the victory card piles and kingdom card piles.
	

	// Expect to lose 1 card but gain 2 (at least at beginning of game)
	assertTrue(oldG.handCount[0] + 1 == newG.handCount[0], "Adds net one card to hand", 0);
	assertTrue(oldG.deckCount[0] - 2 == newG.deckCount[0], "Removes two cards from deck", 0);

	assertTrue(oldG.handCount[1] == newG.handCount[1], "Other player hand count unchanged", 0);
	assertTrue(oldG.deckCount[1] == newG.deckCount[1], "Other player deck count unchanged", 0);

	printf("\nChecking all supply counts...\n");
	int i;
	char buffer[1024];
	for (i = 0; i < treasure_map+1; i++) {
		sprintf(buffer, "Same supply count for card %d", i);
		assertTrue(oldG.supplyCount[i] == newG.supplyCount[i], buffer, 0);
	}

	printf("\nChecking boundary where deck count is 0...\n");
	initializeGame(2, k, 1, &newG);
	newG.deckCount[0] = 0;
	// FIXME: Refactoring here too
	//actionAdventurer(&newG, 0);
	AdventurerEffect(newG.whoseTurn, 0, &newG);
	assertTrue(oldG.handCount[0] - 1 == newG.handCount[0], "Hand size goes down by 1", 0);
	assertTrue(newG.deckCount[0] == 0, "Deck count is set to zero", 0);

	printf("\nBuilding deck of two silver cards...\n");
	initializeGame(2, k, 1, &newG);
	newG.deckCount[0] = 2;
	newG.deck[0][0] = silver;
	newG.deck[0][1] = silver;
	// FIXME: Refactoring here too
	//actionAdventurer(&newG, 0);
	AdventurerEffect(newG.whoseTurn, 0, &newG);
	assertTrue(oldG.handCount[0] + 1 == newG.handCount[0], "Adds net one card to hand", 0);
	assertTrue(newG.deckCount[0] == 0, "Removes two cards from deck", 0);


	// FIXME: This is the only series of tests that do not seg fault!!
	printf("\nBuilding deck of two gold cards...\n");
	initializeGame(2, k, 1, &newG);
	newG.deckCount[0] = 2;
	newG.deck[0][0] = gold;
	newG.deck[0][1] = gold;
	// FIXME: Refactoring here too
	//actionAdventurer(&newG, 0);
	AdventurerEffect(newG.whoseTurn, 0, &newG);
	assertTrue(oldG.handCount[0] + 1 == newG.handCount[0], "Adds net one card to hand", 0);
	assertTrue(newG.deckCount[0] == 0, "Removes two cards from deck", 0);


	return 0;
}
