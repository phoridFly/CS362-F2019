/*************************************************************************
 John Hash
 CS 362 
 Fall 2019
 Assignment 5
 randomtestcard2.c
 This is the implementation file for  randomtestcard2.c
 This file contains the random test suite for the refactored "processMinionCard"
 function in the dominion.c file, refactored by tjgrasse.
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
void testTheMinion();

// void function that prints out the hand of the player
void printHand(struct gameState *stateBefore, struct gameState *stateAfter, int player);

// generates a random card from the enum CARD array
enum CARD randCard();

// takes two game states and a player number to compare hands before and after
int compareHands(struct gameState *stateBefore, struct gameState *stateAfter, int player);

int main () {

    printf("*********************** BEGIN RANDOM TEST 2 ************************************\n");
    printf("Testing the function processMinionCard():\n\n");

    testTheMinion();

}

void testTheMinion() {

    struct gameState game, testGame;

    // call functions to setup the random variable inputs

    int done = MAXITERATIONS;
    float interationNum = 0;
    float numTestsPassed = 0;
    float numTestsFailed = 0; 
    float proportionFail, proportionPass;

    while (done !=0) {

        // setup a game with 1-4 players and kingdom cards
        int seed = 1000;
        int numPlayers = randomNumberFunction(2, 4);
        int chooseCoins = randomNumberFunction(-5, 5);
        int chooseCards = randomNumberFunction(-5, 5);
        int handPos = randomNumberFunction(0, 4);
        int k[10] = {adventurer, council_room, minion, gardens, tribute,
                 remodel, smithy, village, baron, great_hall };
        int currentPlayer = 0; //randomNumberFunction(1, 4);
        int numCardsInHand = 0;
        int c, z = 0;
        enum CARD randoCard = 0;
        int handsSame = 0;
        
        // set the state of your variables so that you will trigger the bug for Baron
        initializeGame(numPlayers, k, seed, &game);

        // get the number of cards in hand
        numCardsInHand = game.handCount[currentPlayer];

        // randomize all player's hands
        for (z = 0; z < numPlayers; z++){
            for (c = 0; c < numCardsInHand; c++) {
                randoCard = randCard();
                game.hand[z][c] = randoCard;  
            }
        }

        printf("ITERATION NUMBER: %.0f\n", interationNum + 1);
        printf("numPlayers = %d\n", numPlayers);

        for (int j = 0; j < 10; j++) {
            printf("Kingdom card %d = %d\n",j , k[j]);
        }

        // copy gameState Game to a new test gameState testGame
        memcpy(&testGame, &game, sizeof(struct gameState));
    
        // call cardEffectMinion with the test game
        processMinionCard(chooseCards, chooseCoins, handPos, &testGame);

        // print hand
        //printf("Hand After: \n");
        for (z = 0; z < numPlayers; z++){
            printf("Player Number: %d\n", z);
            printHand(&game, &testGame, z);
            printf("\n");
        }

        printf("chooseCoins = %d   chooseCards = %d\n", chooseCoins, chooseCards);

        // print out the expectations
        if (chooseCoins == 0) {

            if (chooseCards == 0) {
                printf("** Expect: Player hand to have one fewer card and Treasure remains the same. **\n");

                // we expect 1 card to be discarded
                if (testGame.handCount[currentPlayer] == 4 && game.coins == testGame.coins) {
                    printf("PASSED: One card discarded, and treasure stayed same.\n");
                    numTestsPassed++;
                }
                else {
                    printf("FAILED: Player hand and Treasure incorrect.\n");
                    numTestsFailed++;
                }

            }

            else if (chooseCards == 1) {
                printf("** Expect Players to discard and redraw 4 cards, if they have 5 or more. **\n");
                // check the opponent
                handsSame = compareHands(&game, &testGame, 1);

                if (handsSame == 0) {
                    printf("FAILED: Opponent's hand did not change.\n");
                    numTestsFailed++;
                }
                else {
                    printf("PASSED: Opponent's hand changed.\n");
                    numTestsPassed++;
                }
            }

            else{
                printf("PASSED: Function robust to invalid input.\n");
                numTestsPassed++;
            }
            
        } 

        else if (chooseCoins == 1) {

            if (chooseCards == 0) {
                printf("** Expect: The amount of Treasure (number of coins) to increase by 2. **\n");
                if (game.coins + 2 == testGame.coins) {
                    printf("PASSED: Number of coins increased.\n");
                    numTestsPassed++;
                }
                else {
                    printf("FAILED: Number of coins did not increase.\n");
                    printf("FAILED: Coins before: %d  Coins after: %d  \n", game.coins, testGame.coins);
                    numTestsFailed++;
                }


            }

            else if (chooseCards == 1) {
                printf("** Expect: The amount of Treasure (number of coins) to increase by 2. **\n");
                if (game.coins + 2 == testGame.coins) {
                    printf("PASSED: Number of coins increased.\n");
                    numTestsPassed++;
                }
                else {
                    printf("FAILED: Number of coins did not increase.\n");
                    printf("FAILED: Coins before: %d  Coins after: %d  \n", game.coins, testGame.coins);
                    numTestsFailed++;
                }

            }
            else {
                printf("PASSED: Function robust to invalid input.\n");
                numTestsPassed++;
            }
            

        } 
        else {
            printf("PASSED: Function robust to invalid input.\n");
            numTestsPassed++;
        }
        


        printf("\n");

    
        
        done--;
        interationNum++;

    }
        proportionPass = (numTestsPassed / interationNum);
        proportionFail = (numTestsFailed / interationNum);


        printf("****************************** TEST 2 SUMMARY **********************************\n\n");


        printf("Test Pass Proportion: %.4f\n", proportionPass);
        printf("Test Fail Proportion: %.4f\n\n", proportionFail);

        printf("****************************** TEST 2 END **********************************\n\n");


    
}

// begin the helper functions for this test


int randomNumberFunction (int lower, int upper) {

    int randNum = (rand() % (upper - lower + 1)) + lower;
    return randNum;
    
}

void printHand(struct gameState *stateBefore, struct gameState *stateAfter, int player) {
    for (int i = 0; i < 5; i++){
        printf("Position: %d Before: %d  After: %d\n", i, stateBefore->hand[player][i], stateAfter->hand[player][i]);

    }
}

enum CARD randCard() {

    enum CARD card;
    card = randomNumberFunction(0, 26);
    return card;
}

int compareHands(struct gameState *stateBefore, struct gameState *stateAfter, int player) {
    int diff = 0;
    for (int i = 0; i < 5; i++){
        if (stateBefore->hand[player][i] != stateAfter->hand[player][i]) {
            diff++;
        }

    }
    return diff;
}