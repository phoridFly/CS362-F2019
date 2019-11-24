/*************************************************************************
 John Hash
 CS 362 
 Fall 2019
 Assignment 5
 unittest2.c
 This is the implementation file for unittest2.c
 This file contains the test suite for the refactored "processMinionCard"
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
                 remodel, smithy, village, baron, minion
                };

    struct gameState game, testGame;

    printf("*********************** BEGIN UNIT TEST 2 ************************************\n");
    printf("Testing the function processMinionCard():\n\n");

    // set the state of your variables so that you will trigger the bug for Baron
    initializeGame(numPlayers, k, seed, &game);

    printf("Part 1: Choice = chooseCoins (Gain +2 treasure)\n");
    printf("** Expect: +2 Treasure. **\n");
    
    // set the player's first card in hand to a minion
    game.hand[0][0] = minion;

    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // the choice to discard an Estate card
    int chooseCoins = 1;   // true
    int chooseCards = 0;   // false
    int currentPlayer = 0;
    int handpos = 0;
    // call the function
    processMinionCard(chooseCards, chooseCoins, handpos, &testGame);

    // check if game has the same amount of treasure

    if (testGame.coins == game.coins) {
        printf("FAILED: Treasure before: %d, Treasure after: %d\n\n", game.coins, testGame.coins);
    }
    else {
        printf("PASSED: Treasure before: %d, Treasure after: %d\n\n", game.coins, testGame.coins);
    }

    printf("Part 2: Choice = chooseCards (Player discards and draws new hand)\n");
    printf("** Expect: Tresaure to be unchanged. **\n");
    printf("** Expect: Player hand before and after to be different. Final hand should have only 4 cards. **\n");

    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // the choice to discard and draw a new hand
    chooseCoins = 0;   // false
    chooseCards = 1;   // true
    currentPlayer = 0;
    handpos = 0;
    
    // call the function
    processMinionCard(chooseCards, chooseCoins, handpos, &testGame);

    if (testGame.coins == game.coins) {
        printf("PASSED: Treasure before: %d, Treasure after: %d\n\n", game.coins, testGame.coins);
    }
    else {
        printf("FAILED: Treasure before: %d, Treasure after: %d\n\n", game.coins, testGame.coins);
    }

    // check if player hand is the same

    int pos = 0;
    int differenceFlag = 0;
    
    for (int i = 0; i < game.handCount[currentPlayer]; i++){
        printf("Card %d Before: %d     Card %d After: %d\n", pos, game.hand[currentPlayer][pos], pos, testGame.hand[currentPlayer][pos]);
        

        if (game.hand[currentPlayer][pos] != testGame.hand[currentPlayer][pos]) {
            differenceFlag++;
        }

        pos++;

    }

    if (differenceFlag == 0){
        printf("FAILED: Current player hand did not change.\n\n");
    }

    if (differenceFlag > 0){
        printf("PASSED: Current player hand changed, player hand discarded and redrawn.\n\n");
    }

    printf("Part 3: Choice = chooseCards (Minion attack).\n");
    printf("** Expect: Other player has 5 cards initially and only 4 cards after attack (-1 means no card). **\n");
    printf("** Expect: Other player has a different hand before and after. **\n");

    // make handcount five for the other player, so that they have to redraw 4
    game.handCount[1] = 5;

    // manually set other player's hand so we can see the difference after redraw
    game.hand[1][0] = estate;
    game.hand[1][1] = baron;
    game.hand[1][2] = minion;
    game.hand[1][3] = smithy;
    game.hand[1][4] = feast;


    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // the choice to discard and draw a new hand
    chooseCoins = 0;   // false
    chooseCards = 1;   // true
    currentPlayer = 0;
    handpos = 0;
    
    
    // call the function
    processMinionCard(chooseCards, chooseCoins, handpos, &testGame);

    // check if player hand is the same
    pos = 0;
    differenceFlag = 0;
    
    // iterate over the hand of the other player and check the control game state to the test game state
    for (int i = 0; i < game.handCount[1]; i++){
        printf("Card %d Before: %d     Card %d After: %d\n", pos, game.hand[1][pos], pos, testGame.hand[1][pos]);
        

        if (game.hand[1][pos] != testGame.hand[1][pos]) {
            differenceFlag++;
        }

        pos++;

    }

    if (differenceFlag == 0){
        printf("FAILED: Other player's hand did not change.\n\n");
    }

    if (differenceFlag > 0){
        printf("PASSED: Other player's hand changed, discarded 5 and redrew 4 cards.\n\n");
    }

    printf("Part 4: Choice = chooseCards (Checking the number of actions).\n");
    printf("** Expect: Number of actions to increase by 1. ** \n");

    // initialize a new game state
    initializeGame(numPlayers, k, seed, &game);

    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // get number of action before
    int numberOfActionBefore = game.numActions;

    // call minion function
    processMinionCard(chooseCards, chooseCoins, handpos, &testGame);

    int numberOfActionAfter = testGame.numActions;

    printf("Number of Actions Before: %d  Number of Actions After  %d\n", numberOfActionBefore, numberOfActionAfter);

    if (numberOfActionAfter > numberOfActionBefore) {
        printf("PASSED: Number of actions increased.\n");
    }
    else  {
        printf("FAILED: Number of actions did not increase.\n");
    }

    printf("\n\n");

    printf("Unit Test 2, Minion, Completed.\n");
    printf("*********************** END  UNIT TEST 2 ************************************\n\n");


}


    
    

