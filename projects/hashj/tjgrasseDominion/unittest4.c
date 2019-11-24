/*************************************************************************
 John Hash
 CS 362 
 Fall 2019
 Assignment 5
 unittest4.c
 This is the implementation file for unittest4.c
 This file contains the test suite for the refactored "processTributeCard"
 function in the dominion.c file, refactored by tjgrasse.
 *************************************************************************/
 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {

    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
    int handPos = 4;
    //int tributeRevealedCards[2] = {-1, -1};


    int k[10] = {adventurer, council_room, ambassador, tribute, mine,
                 remodel, smithy, village, baron, minion
                };

    struct gameState game, testGame;

    printf("*********************** BEGIN UNIT TEST 4 ************************************\n");
    printf("Testing the function processTributeCard():\n\n");

    printf("Part 1: Next player has Victory, Treasure, and Action in both discard and deck piles\n");
    printf("** Expect: Treasure to increase by + 2. **\n");
    printf("** Expect: Current player hand count to increase by +2. **\n");

    initializeGame(numPlayers, k, seed, &game);

    // the next player to have one of each type of card in their discard and deck piles
    game.discardCount[nextPlayer] = 3;
    game.discard[nextPlayer][0] = estate;
    game.discard[nextPlayer][1] = copper;
    game.discard[nextPlayer][2] = mine;

    game.deckCount[nextPlayer] = 3;
    game.deck[nextPlayer][0] = duchy;
    game.deck[nextPlayer][1] = silver;
    game.deck[nextPlayer][2] = tribute;

    // setup a hand for the current player
    game.handCount[currentPlayer] = 5;
    game.hand[currentPlayer][0] = estate;
    game.hand[currentPlayer][1] = silver;
    game.hand[currentPlayer][2] = copper;
    game.hand[currentPlayer][3] = smithy;
    game.hand[currentPlayer][4] = tribute;

    memcpy(&testGame, &game, sizeof(struct gameState));

    processTributeCard(handPos, &testGame);

    // check if the number of coins increases
    if (game.coins + 2 == testGame.coins) {
        printf("PASSED: Number of coins increased by +2.\n");
    }
    if (game.coins + 2 != testGame.coins) {
        printf("FAILED: Coins before: %d   Coins after: %d\n", game.coins, testGame.coins);
    }

    // check the current player's hand
    if (game.handCount[currentPlayer] + 2 == testGame.handCount[currentPlayer]) {
        printf("PASSED: Number of cards in current player's hand increased by +2.\n\n");
    }
    if (game.handCount[currentPlayer] + 2 != testGame.handCount[currentPlayer]) {
        printf("FAILED: Card number before: %d   Card number after: %d\n\n", game.handCount[currentPlayer], testGame.handCount[currentPlayer]);
    }


    printf("Part 2: Next player only has a single Silver card in deck and 0 in discard pile.\n");
    printf("** Expect: Treasure to increase by + 2. **\n");
    printf("** Expect: Number of Actions to remain the same. **\n");

    initializeGame(numPlayers, k, seed, &game);

    // the next player to have one of each type of card in their discard and deck piles
    game.discardCount[nextPlayer] = 0;

    game.deckCount[nextPlayer] = 1;
    game.deck[nextPlayer][0] = silver;

    // setup a hand for the current player
    game.handCount[currentPlayer] = 5;
    game.hand[currentPlayer][0] = estate;
    game.hand[currentPlayer][1] = silver;
    game.hand[currentPlayer][2] = copper;
    game.hand[currentPlayer][3] = smithy;
    game.hand[currentPlayer][4] = tribute;

    memcpy(&testGame, &game, sizeof(struct gameState));

    processTributeCard(handPos, &testGame);

    // check if the number of coins increases
    if (game.coins + 2 == testGame.coins) {
        printf("PASSED: Number of coins increased by +2.\n");
    }
    if (game.coins + 2 != testGame.coins) {
        printf("FAILED: Coins before: %d   Coins after: %d\n", game.coins, testGame.coins);
    }

    // check if the number of actions increases
    if (game.numActions == testGame.numActions) {
        printf("PASSED: Number of actions stayed the same.\n\n");
    }
    if (game.numActions != testGame.numActions) {
        printf("FAILED: Actions before: %d   Actions after: %d\n\n", game.numActions, testGame.numActions);
    }


    printf("Part 3: Next player only has a single Silver card in discard pile and 0 in deck pile.\n");
    printf("** Expect: Treasure to increase by + 2. **\n");

    initializeGame(numPlayers, k, seed, &game);

    // the next player to have one of each type of card in their discard and deck piles
    game.discardCount[nextPlayer] = 1;
    game.discard[nextPlayer][0] = silver;

    game.deckCount[nextPlayer] = 0;
    

    // setup a hand for the current player
    game.handCount[currentPlayer] = 5;
    game.hand[currentPlayer][0] = estate;
    game.hand[currentPlayer][1] = silver;
    game.hand[currentPlayer][2] = copper;
    game.hand[currentPlayer][3] = smithy;
    game.hand[currentPlayer][4] = tribute;

    memcpy(&testGame, &game, sizeof(struct gameState));

    processTributeCard(handPos, &testGame);

    // check if the number of coins increases
    if (game.coins + 2 == testGame.coins) {
        printf("PASSED: Number of coins increased by +2.\n\n");
    }
    if (game.coins + 2 != testGame.coins) {
        printf("FAILED: Coins before: %d   Coins after: %d\n\n", game.coins, testGame.coins);
    }

    printf("Part 4: Next player has three cards in discard pile and 0 deck.\n");
    printf("** Expect: Treasure to increase by + 2. **\n");
    printf("** Expect: Current player hand count to increase by +2. **\n");

    initializeGame(numPlayers, k, seed, &game);

    // the next player to have one of each type of card in their discard and deck piles
    game.discardCount[nextPlayer] = 3;
    game.discard[nextPlayer][0] = estate;
    game.discard[nextPlayer][1] = copper;
    game.discard[nextPlayer][2] = mine;

    game.deckCount[nextPlayer] = 0;
    
    // setup a hand for the current player
    game.handCount[currentPlayer] = 5;
    game.hand[currentPlayer][0] = estate;
    game.hand[currentPlayer][1] = silver;
    game.hand[currentPlayer][2] = copper;
    game.hand[currentPlayer][3] = smithy;
    game.hand[currentPlayer][4] = tribute;

    memcpy(&testGame, &game, sizeof(struct gameState));

    processTributeCard(handPos, &testGame);

    // check if the number of coins increases
    if (game.coins + 2 == testGame.coins) {
        printf("PASSED: Number of coins increased by +2.\n");
    }
    if (game.coins + 2 != testGame.coins) {
        printf("FAILED: Coins before: %d   Coins after: %d\n", game.coins, testGame.coins);
    }

    // check the current player's hand
    if (game.handCount[currentPlayer] + 2 == testGame.handCount[currentPlayer]) {
        printf("PASSED: Number of cards in current player's hand increased by +2.\n\n");
    }
    if (game.handCount[currentPlayer] + 2 != testGame.handCount[currentPlayer]) {
        printf("FAILED: Card number before: %d   Card number after: %d\n\n", game.handCount[currentPlayer], testGame.handCount[currentPlayer]);
    }

    printf("\n\n");

    printf("Unit Test 4, Tribute, Completed.\n");
    printf("*********************** END  UNIT TEST 4 ************************************\n\n");


}