/*************************************************************************
 John Hash
 CS 362 
 Fall 2019
 Assignment 5
 unittest1.c
 This is the implementation file for unittest1.c
 This file contains the test suite for the refactored "processBaronCard"
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

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall
                };

    struct gameState game, testGame;

    printf("*********************** BEGIN UNIT TEST 1 ************************************\n");
    printf("Testing the function processBaronCard():\n\n");

    // set the state of your variables so that you will trigger the bug for Baron
    initializeGame(numPlayers, k, seed, &game);

    printf("Part 1: discardEstate = 1 (Player uses Baron to discard Estate card for +4 Treasure)\n");
    printf("** Expect: +4 Treasure. **\n");

    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // the choice to discard an Estate card
    int discardEstate = 1;
    int handPos = 2;
    processBaronCard(discardEstate, handPos, &testGame);

    int moreTreasure = 4;

    
    
    // check to see if 4 coins have been added to game
    if (testGame.coins == game.coins + moreTreasure) {
        printf("PASSED: Treasure before: %d, Treasure after: %d\n\n", game.coins, testGame.coins);
    }
    else {
        printf("FAILED: Treasure before: %d, Treasure after: %d\n\n", game.coins, testGame.coins);
    }

    printf("Part 2: discardEstate = 0 (Player uses Baron to gain an Estate card)\n");

    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // the choice to discard an Estate card, choice 0
    discardEstate = 0;
    handPos = 0;

    // variables to check number of Estate cards before and after
    int originalEstates = 0;
    int finalEstates = 0;
    processBaronCard(discardEstate, handPos, &testGame);

    // check if game has the same amount of treasure

    printf("** Expect: Treasure before and after to be the same. **\n** Expect +1 Estate card (card number 4). **\n");

    if (testGame.coins == game.coins) {
        printf("PASSED: Treasure before: %d, Treasure after: %d\n\n", game.coins, testGame.coins);
    }
    else {
        printf("FAILED: Treasure before: %d, Treasure after: %d\n\n", game.coins, testGame.coins);
    }

    // check if player hand is the same

    int pos = 0;
    int differenceFlag = 0;
    int currentPlayer = 0;
    
    for (int i = 0; i < game.handCount[currentPlayer]; i++){
        printf("Card %d Before: %d     Card %d After: %d\n", pos, game.hand[currentPlayer][pos], pos, testGame.hand[currentPlayer][pos]);
        pos++;

        if (game.hand[currentPlayer][pos] != testGame.hand[currentPlayer][pos]) {
            differenceFlag++;
        }

        if (game.hand[currentPlayer][pos] == estate) {
            originalEstates += 1;
        }

        if (game.hand[currentPlayer][pos] == estate) {
            finalEstates += 1;
        }
    }

    if (differenceFlag == 0){
        printf("FAILED: Player hand did not change. No Estate card added.\n");
    }

    if (originalEstates == finalEstates) {
        printf("FAILED: Estate cards before: %d  Estate cards after: %d\n", originalEstates, finalEstates);
    }

    if (finalEstates == originalEstates + 1) {
        printf("PASSED: Estate cards before: %d  Estate cards after: %d\n", originalEstates, finalEstates);
    }

    printf("\n");

    printf("Part 3: discardEstate = 0 (Player uses Baron to gain the final Estate card in the Supply)\n");
    printf("** Expect: Game to be over and Estate supply to decrease from 1 to 0 **\n");

    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // choice 0, when cardEffectBaron is called, choice 0 will cause estate supply count to hit 0
    // isGameOver should return 1 for game to end
    testGame.supplyCount[estate] = 1;

    // the choice to discard an Estate card, choice 0
    currentPlayer = 0;

    // variables to check number of Estate cards before and after    
    processBaronCard(discardEstate, handPos, &testGame);


    int gameDone = isGameOver(&testGame);
    if (gameDone == 1) {
        printf("PASSED: Last Estate card removed from Supply and game has ended.\n");
        printf("Supply of Estate cards = %d", testGame.supplyCount[estate]);
    }

    if (gameDone == 0) {
        printf("FAILED: Game failed to end with last card removed.\n");
        printf("Supply of Estate cards = %d", testGame.supplyCount[estate]);

    }

    printf("\n\n");

    printf("Unit Test 1, Baron, Completed.\n");
    printf("*********************** END  UNIT TEST 1 ************************************\n\n");

}


    
    

