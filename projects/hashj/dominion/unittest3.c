/*************************************************************************
 John Hash
 CS 362 
 Fall 2019
 Assignment 3
 unittest3.c
 This is the implementation file for unittest3.c
 This file contains the test suite for the refactored "cardEffectAmbassdor"
 function in the dominion.c file.
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

    int k[10] = {adventurer, council_room, ambassador, gardens, mine,
                 remodel, smithy, village, baron, minion
                };

    struct gameState game, testGame;

    printf("*********************** BEGIN UNIT TEST 3 ************************************\n");
    printf("Testing the function cardEffectAmbassador():\n\n");

    // set the state of your variables so that you will trigger the bug for Baron
    initializeGame(numPlayers, k, seed, &game);

    // create a known, sample hand with three identical cards to test if more than 2 can be discarded
    game.handCount[0] = 7;
    game.hand[0][0] = estate;
    game.hand[0][1] = smithy;
    game.hand[0][2] = smithy;
    game.hand[0][3] = smithy;
    game.hand[0][4] = ambassador;
    game.hand[0][5] = estate;
    game.hand[0][6] = mine;

    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // the choice to discard and draw a new hand
    int choice1 = 1;   // get rid of smithy card
    int choice2 = 1;   // get rid of 1 additional card
    int currentPlayer = 0;
    int handpos = 4;
    
    
    // call the function
    cardEffectAmbassador(choice1, choice2, &testGame, handpos, currentPlayer);

    printf("Part 1: Choice1 = Smithy (Get rid of Smithy card in hand position 1) Choice2 = 1 (Discard 1 copy of Smithy card)\n");
    printf("** Expect: Hand after to contain 2 fewer Smithy cards. **\n");
    printf("** Expect: Other player's hand to contain 1 more Smithy card. **\n");
    printf("** Expect: Supply count of Smithy cards to increase by 1. **\n");

    // check if player hand is the same
    int pos = 0;
    int smithysBefore = 3;
    int smithysAfter = 0;
    
    // iterate over the hand of the other player and check the control game state to the test game state
    for (int i = 0; i < game.handCount[0]; i++){
        printf("Card %d Before: %d     Card %d After: %d\n", pos, game.hand[currentPlayer][pos], pos, testGame.hand[currentPlayer][pos]);
        
        if (testGame.hand[currentPlayer][pos] == smithy) {
            smithysAfter++;
        }
        pos++;
    }

    if (smithysAfter > 1) {
        printf("FAILED: Smithy cards before: %d  Smithy cards after: %d\n", smithysBefore, smithysAfter);
    }

    if (smithysAfter == 1) {
        printf("PASSED: Smithy cards before: %d  Smithy cards after: %d\n", smithysBefore, smithysAfter);
    }

    // code for determining the opponent's hand before and after
    int opponentSmithyBefore = 0;
    int opponentSmithyAfter = 0;
    for (int i = 0; i < game.handCount[1]; i++) {
        if (game.hand[1][i] == smithy) {
            opponentSmithyBefore++;
        }
    }

    for (int i = 0; i < testGame.handCount[1]; i++) {
        if (testGame.hand[1][i] == smithy) {
            opponentSmithyAfter++;
        }
    }

    if (opponentSmithyBefore + 1 == opponentSmithyAfter) {
        printf("PASSED: Other player gained a Smithy card.\n");
    }
    else {
        printf("FAILED: Other player did not gain a Smithy card. Smithy cards before: %d  Smithy cards after: %d\n", opponentSmithyBefore, opponentSmithyAfter);
    }

    if (game.supplyCount[smithy] == testGame.supplyCount[smithy]) {
        printf("FAILED: Smith supply did not increase. Supply before: %d  Supply after: %d\n\n", game.supplyCount[smithy], testGame.supplyCount[smithy]);
    }

    if (game.supplyCount[smithy] > testGame.supplyCount[smithy]) {
        printf("TENTATIVE PASS: Check by how much it was supposed to increase. Supply before: %d  Supply after: %d\n\n", game.supplyCount[smithy], testGame.supplyCount[smithy]);
    }


    printf("Part 2: Choice1 = Smithy (Get rid of Smithy card in hand position 1) Choice2 = 0 (Discard 0 copies of Smithy card)\n");
    printf("** Expect: Hand after to contain 1 fewer Smithy cards. **\n");
    printf("** Expect: Other player's hand to contain 1 more Smithy card. **\n");
    printf("** Expect: Supply count of Smithy cards to remain the same. **\n");

    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // the choice to discard and draw a new hand
    choice1 = 1;   // get rid of smithy card
    choice2 = 0;   // get rid of 0 additional copies
    currentPlayer = 0;
    handpos = 4;
    
    // call the function
    cardEffectAmbassador(choice1, choice2, &testGame, handpos, currentPlayer);

    pos = 0;
    smithysBefore = 3;
    smithysAfter = 0;

    // iterate over the hand of the other player and check the control game state to the test game state
    for (int i = 0; i < game.handCount[0]; i++){
        printf("Card %d Before: %d     Card %d After: %d\n", pos, game.hand[currentPlayer][pos], pos, testGame.hand[currentPlayer][pos]);
        
        if (testGame.hand[currentPlayer][pos] == smithy) {
            smithysAfter++;
        }

        pos++;

    }

    if (smithysAfter > 1) {
        printf("FAILED: Smithy cards before: %d  Smithy cards after: %d\n", smithysBefore, smithysAfter);
    }

    if (smithysAfter == 1) {
        printf("PASSED: Smithy cards before: %d  Smithy cards after: %d\n", smithysBefore, smithysAfter);
    }

        // code for determining the opponent's hand before and after
    opponentSmithyBefore = 0;
    opponentSmithyAfter = 0;
    for (int i = 0; i < game.handCount[1]; i++) {
        if (game.hand[1][i] == smithy) {
            opponentSmithyBefore++;
        }
    }

    for (int i = 0; i < testGame.handCount[1]; i++) {
        if (testGame.hand[1][i] == smithy) {
            opponentSmithyAfter++;
        }
    }

    if (opponentSmithyBefore + 1 == opponentSmithyAfter) {
        printf("PASSED: Other player gained a Smithy card.\n");
    }
    else {
        printf("FAILED: Other player did not gain a Smithy card. Smithy cards before: %d  Smithy cards after: %d\n", opponentSmithyBefore, opponentSmithyAfter);
    }

    if (game.supplyCount[smithy] == testGame.supplyCount[smithy]) {
        printf("PASSED: Smith supply did not increase. Supply before: %d  Supply after: %d\n", game.supplyCount[smithy], testGame.supplyCount[smithy]);
    }

    if (game.supplyCount[smithy] > testGame.supplyCount[smithy]) {
        printf("FAILED: Supply before: %d  Supply after: %d\n\n", game.supplyCount[smithy], testGame.supplyCount[smithy]);
    }


    printf("Part 3: Choice1 = Hand Position\n");
    printf("** Expect: Game state to be unaltered. In full game, this would result in invalid choice. **\n");

    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // the choice to discard and draw a new hand
    choice1 = 1;   // get rid of smithy card
    choice2 = 2;   // get rid of 2 additional copies
    currentPlayer = 0;
    handpos = 1;
    int didStateChange = 0;


    // call the function
    cardEffectAmbassador(choice1, choice2, &testGame, handpos, currentPlayer);

    // series of if statements checking if the game states are identical
    // if they aren't, didStateChange increments and is used to print the pass/fail message
    for (int i = 0; i < game.hand[0][0]; i++){

        if (game.hand[currentPlayer][i] != testGame.hand[currentPlayer][i]) {
            didStateChange++;    
        }
    }

    if (game.coins != testGame.coins) {
        didStateChange++;
    }

    if (game.numActions != testGame.numActions) {
        didStateChange++;
    }

    if (didStateChange == 0) {
        printf("PASSED: Game state did not change.\n\n");
    }
    else {
        printf("FAILED: Game state did not remain identical.\n\n");
    }

    printf("Part 4: Choice2 is higher than the maxiumum allowed 2 \n");
    printf("** Expect: Game state to be unaltered. In full game, this would result in invalid choice. **\n");
    printf("** Expect: cardEffectAmassador should return -1 **\n");


    // copy gameState Game to a new test gameState testGame
    memcpy(&testGame, &game, sizeof(struct gameState));

    // the choice to discard and draw a new hand
    choice1 = 1;   // get rid of smithy card
    choice2 = 5;   // attempt to get rid of 5 copies of a card
    currentPlayer = 0;
    handpos = 1;
    int negativeOneReturn;

    // call the function
    negativeOneReturn = cardEffectAmbassador(choice1, choice2, &testGame, handpos, currentPlayer);

    if (negativeOneReturn == -1) {
        printf("PASSED: Didn't allow game to proceed. Returned -1.\n\n");
    }
    else {
        printf("FAILED: Game proceeded with bad input.\n\n");
    }

    printf("\n\n");

    printf("Unit Test 3, Ambassador, Completed.\n");
    printf("*********************** END  UNIT TEST 3 ************************************\n\n");
  
}