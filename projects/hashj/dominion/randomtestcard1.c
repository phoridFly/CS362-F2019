/*************************************************************************
 John Hash
 CS 362 
 Fall 2019
 Assignment 4
 randomtestcard1.c
 This is the implementation file for randomtestcard1.c
 This file contains the random test suite for the refactored "cardEffectBaron"
 function in the dominion.c file.
 *************************************************************************/
 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include<stdlib.h>
#include<time.h>
#include "rngs.h"

#define MAXITERATIONS 100

// call function with lower and upper bound to get a random number back
int randomNumberFunction (int lower, int upper);

// void function called by main that runs the test
void testTheBaron();

// void function that prints out the hand of the player
void printHandCompare(struct gameState *state, int currentPlayer);

// generates a random card from the enum CARD array
enum CARD randCard();

// returns 1 if an estate card is found, 0 if not
int estateCardFound(struct gameState *state, int currentPlayer);

// returns the number of estate cards in player's hand
int numberOfEstates (struct gameState *state, int currentPlayer);

int main () {

    printf("*********************** BEGIN RANDOM TEST 1 ************************************\n");
    printf("Testing the function cardEffectBaron():\n\n");

    testTheBaron();

}

void testTheBaron() {

    struct gameState game, testGame;

    // call functions to setup the random variable inputs

    int done = MAXITERATIONS;
    float interationNum = 0;
    float numTestsPassed, numTestsFailed = 0;
    float proportionFail, proportionPass;

    while (done !=0) {

        // setup a game with 1-4 players and kingdom cards
        int seed = 1000;
        int numPlayers = randomNumberFunction(2, 4);
        int choice1 = randomNumberFunction(-5, 5);
        int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall };
        int currentPlayer = 0;
        int numCardsInHand, estatesBefore, estatesAfter, estateFlag = 0;
        int c = 0;
        enum CARD randoCard = 0;
        
        // set the state of your variables so that you will trigger the bug for Baron
        initializeGame(numPlayers, k, seed, &game);

        printf("ITERATION NUMBER: %.0f\n", interationNum + 1);
        printf("numPlayers = %d\n", numPlayers);

        for (int j = 0; j < 10; j++) {
            printf("Kingdom card %d = %d\n",j , k[j]);
        }

        // get the number of cards in hand
        numCardsInHand = game.handCount[currentPlayer];

        printf("Hand Count: %d\n", numCardsInHand);

        //set hand to random cards
        for (c = 0; c < numCardsInHand; c++) {
            randoCard = randCard();
            game.hand[currentPlayer][c] = randoCard;
        }

        // print hand
        printf("Hand Before: \n");
        printHandCompare(&game, currentPlayer);

        // copy gameState Game to a new test gameState testGame
        memcpy(&testGame, &game, sizeof(struct gameState));
    
        // call cardEffectBaron with the test game
        cardEffectBaron(choice1, &testGame, currentPlayer);

        // print hand
        printf("Hand After: \n");
        printHandCompare(&testGame, currentPlayer);

        // get the number of estate cards before an after
        estatesBefore = numberOfEstates(&game, currentPlayer);
        estatesAfter = numberOfEstates(&testGame, currentPlayer);

        // print out the expectations
        if (choice1 > 0) {
            printf("Choice = %d.\n", choice1);
            printf("** Expect: +4 Treasure if Estate card is in hand. **\n");

            // check if an estate card is the current player's hand
            estateFlag = estateCardFound(&game, currentPlayer);

            // check to see if 4 coins have been added to game and function returned proper value
            if (estateFlag == 1 && testGame.coins == game.coins + 4) {
                printf("PASSED: Treasure before: %d, Treasure after: %d\n", game.coins, testGame.coins);
                printf("PASSED: Choice > 0, Estate Card in hand, correctly increased treasure.\n");

                numTestsPassed++;
            }

            if (estateFlag == 1 && testGame.coins != game.coins + 4) {
                printf("FAILED: Treasure before: %d, Treasure after: %d\n", game.coins, testGame.coins);
                printf("FAILED: Choice1 > 0, Estate Card in hand, failed to increase treasure.\n");
                
                numTestsFailed++;
            }

            if (estateFlag == 0 && testGame.coins == game.coins + 4) {
                printf("FAILED: Treasure before: %d, Treasure after: %d\n", game.coins, testGame.coins);
                printf("FAILED: Choice1 > 0, Estate Card NOT in hand, erroneously increased treasure.\n");

                numTestsFailed++;
            }

            if (estateFlag == 0 && testGame.coins != game.coins + 4) {
                printf("PASSED: Treasure before: %d, Treasure after: %d\n", game.coins, testGame.coins);
                printf("PASSED: Choice > 0, Estate Card NOT in hand, correctly didn't increase treasure.\n");
                
                numTestsPassed++;
            }

        }
        if (choice1 <= 0){
            printf("Choice = %d\n", choice1);
            printf("** Expect: +1 Estate Card AND +0 Treasure. **\n");

            // check if an estate card is the current player's hand
            //estateFlag = estateCardFound(&game, currentPlayer);

            if(estatesAfter == estatesBefore + 1 && game.coins == testGame.coins) {

                printf("PASSED: Estate cards before: %d, Estate cards after: %d\n", estatesBefore, estatesAfter);
                printf("PASSED: Choice <= 0, Estate Card number increased, treasure stayed the same.\n");
                numTestsPassed++;
            }

            else {

                printf("FAILED: Estate cards before: %d, Estate cards after: %d\n", estatesBefore, estatesAfter);
                printf("FAILED: Treasure before: %d, Treasure after: %d\n", game.coins, testGame.coins);
                numTestsFailed++;
            }

        }

        printf("\n");
        
        done--;
        interationNum++;

    }

    proportionPass = (numTestsPassed / interationNum);
    proportionFail = (numTestsFailed / interationNum);

    printf("****************************** TEST 1 SUMMARY **********************************\n\n");


    printf("Test Pass Proportion: %.4f\n", proportionPass);
    printf("Test Fail Proportion: %.4f\n\n", proportionFail);

    printf("****************************** TEST 1 END **********************************\n\n");


}

// begin the helper functions for this test


int randomNumberFunction (int lower, int upper) {

    int randNum = (rand() % (upper - lower + 1)) + lower;
    return randNum;
    
}

void printHandCompare(struct gameState *state, int currentPlayer) {
    for (int i = 0; i < state->handCount[currentPlayer]; i++){
        printf("Hand Number: %d Type Number: %d\n", i, state->hand[currentPlayer][i]);

    }
}

enum CARD randCard() {

    enum CARD card;
    card = randomNumberFunction(0, 26);
    return card;
}

int estateCardFound(struct gameState *state, int currentPlayer) {
    for (int i = 0; i < state->handCount[currentPlayer]; i++){
        if(state->hand[currentPlayer][i] == estate){
            return 1;
        }    
    }
    return 0;
}

int numberOfEstates(struct gameState *state, int currentPlayer) {

    int numEstates = 0;

    for (int i = 0; i < state->handCount[currentPlayer]; i++){
        if(state->hand[currentPlayer][i] == estate){
            numEstates++;
        }    
    }
    return numEstates;
}