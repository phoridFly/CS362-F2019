/*************************************************************************
 John Hash
 CS 362 
 Fall 2019
 Assignment 5
 randomtestcard3.c
 This is the implementation file for  randomtestcard3.c
 This file contains the test suite for the refactored "processTributeCard"
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
void testTheTribute();

// void function that prints out the hand of the player
void printHand(struct gameState *stateBefore, struct gameState *stateAfter, int player);

// generates a random card from the enum CARD array
enum CARD randCard();

// takes two game states and a player number to compare hands before and after
int compareHands(struct gameState *stateBefore, struct gameState *stateAfter, int player);

// void function that takes a gamestate and a player and prints the deck
void printDeck(struct gameState *state, int nextPlayer);

// void function that takes a gamestate and a player and prints the discard pile
void printDiscard(struct gameState *state, int nextPlayer);

int main () {

    printf("*********************** BEGIN RANDOM TEST 3 ************************************\n");
    printf("Testing the function processTributeCard():\n\n");

    testTheTribute();

}

void testTheTribute() {

    struct gameState game, testGame;

    // call functions to setup the random variable inputs

    int done = MAXITERATIONS;
    float interationNum = 0;
    float numTestsPassed = 0;
    float numTestsFailed = 0;
    //float proportionFail, proportionPass;

    while (done !=0) {

        // setup a game with 1-4 players and kingdom cards
        int seed = 1000;
        int numPlayers = randomNumberFunction(2, 4);
        int handPos = randomNumberFunction(0, 4);
        int k[10] = {adventurer, council_room, minion, gardens, tribute,
                 remodel, smithy, village, baron, great_hall };
        int currentPlayer = 0;
        int nextPlayer = 1;
        int numCardsInHand = 0;
        int c, z = 0;
        enum CARD randoCard = 0;
        int randomDiscard = randomNumberFunction(0, 5);
        int randomDeck = randomNumberFunction(0, 5);
        //int tribute1 = randomNumberFunction(-1, 26);
        //int tribute2 = randomNumberFunction(-1, 26);
        //int tributeRevealedCards[2] = {tribute1, tribute2};
        int i = 0;
        
        // set the state of your variables so that you will trigger the bug for Baron
        initializeGame(numPlayers, k, seed, &game);

        // get the number of cards in hand
        numCardsInHand = game.handCount[currentPlayer];

        //randomize all player's hands
        for (z = 0; z < numPlayers; z++){
            for (c = 0; c < numCardsInHand; c++) {
                randoCard = randCard();
                game.hand[z][c] = randoCard;  
            }
        }

        // //setup a random number of cards in the deck of next player
        game.deckCount[nextPlayer] = randomDeck;
        for (c = 0; c < randomDeck; c++){
            randoCard = randCard();
            game.deck[nextPlayer][c] = randoCard;
        }
        
        // //setup a random number of cards in the discard pile of next player
        game.discardCount[nextPlayer] = randomDiscard;
        for (c = 0; c < randomDiscard; c++){
            randoCard = randCard();
            game.discard[nextPlayer][c] = randoCard;
        }

        printf("ITERATION NUMBER: %.0f\n", interationNum + 1);
        printf("numPlayers = %d\n", numPlayers);

        for (int j = 0; j < 10; j++) {
            printf("Kingdom card %d = %d\n",j , k[j]);
        }

        // copy gameState Game to a new test gameState testGame
        memcpy(&testGame, &game, sizeof(struct gameState));
    
        // call cardEffectTribute with the test game
        processTributeCard(handPos, &testGame);

        // print hand
        //printf("Hand After: \n");
        for (z = 0; z < numPlayers; z++){
            printf("Player Number: %d\n", z);
            printHand(&game, &testGame, z);
            printf("\n");
        }

        // print the next player's deck
        
        printDeck(&game, nextPlayer);
        printDeck(&testGame, nextPlayer);


        // print the next player's discard
        printDiscard(&game, nextPlayer);
        printDiscard(&testGame, nextPlayer);


        // if next player deck + discard pile is 0, should result in no change
        if (testGame.discardCount[nextPlayer] + testGame.deckCount[nextPlayer] == 0) {
            printf("** Expect: Treasure, Number of Actions, and Current Player hand count to remain same. **\n");
            if (game.coins == testGame.coins && game.numActions == testGame.numActions && game.handCount[currentPlayer] == testGame.handCount[currentPlayer]) {
                printf("PASSED: Game state did not change. Player to left had no cards in deck or discard pile.\n");
                numTestsPassed++;
            }
            else {
                printf("FAILED: Game state changed erroneously. Next player had no cards to reveal.\n");
                numTestsFailed++;
            }

        }

        else if (testGame.deckCount[nextPlayer] >= 1) {    
            // check if the deck's first two positions have cards
            int deckLoopHigh = 0;
            if (randomDeck >= 2) {
                deckLoopHigh = 2;
            }
            else if (randomDeck == 1) {
                deckLoopHigh = 1;
            }
            else {
                deckLoopHigh = 0;
            }


            for (i = 0; i < deckLoopHigh; i++) {

                // one of top two is a treasure card
                if (testGame.deck[nextPlayer][i] == copper || testGame.deck[nextPlayer][i] == silver || testGame.deck[nextPlayer][i] == gold) {
                    printf("** Expect: Current player coins to increase.\n");
                    if (game.coins < testGame.coins) {
                        printf("PASSED: Coins increased.\n");
                        numTestsPassed++;
                    }
                    else {
                        printf("FAILED: Coins stayed the same.\n");
                        numTestsFailed++;
                    }
                    
                }
                // one of top two is a victory card
                else if (testGame.deck[nextPlayer][i] == estate || testGame.deck[nextPlayer][i] == duchy || testGame.deck[nextPlayer][i] == province || testGame.deck[nextPlayer][i] == gardens || testGame.deck[nextPlayer][i] == great_hall) {
                    printf("** Expect: Current player hand count to increase.\n");
                    if (game.handCount[currentPlayer] < testGame.handCount[currentPlayer]) {
                        printf("PASSED: Current player hand count increased.\n");
                        numTestsPassed++;
                    }
                    else {
                        printf("FAILED: Current player hand count did not increase.\n");
                        numTestsFailed++;
                    }
                }
                // one of top two is an action card
                else { 
                    printf("** Expect: Current player number of actions to increase.\n");
                    if (game.numActions < testGame.numActions) {
                        printf("PASSED: Number of Actions increased.\n");
                        numTestsPassed++;
                    }
                    else {
                        printf("FAILED: Number of Actions did not increase.\n");
                        numTestsFailed++;
                    }

                }
            }
        }


        else { // (testGame.deckCount[nextPlayer] == 0 && testGame.discardCount[nextPlayer] >= 1) { 
            // check if the discard's first two positions have cards
            int discardLoopHigh = 0;
            if (randomDiscard >= 2) {
                discardLoopHigh = 2;
            }
            else if (randomDiscard == 1) {
                discardLoopHigh = 1;
            }
            else {
                discardLoopHigh = 0;
            }

            for (i = 0; i < discardLoopHigh; i++) {
                if (testGame.discard[nextPlayer][i] == copper || testGame.discard[nextPlayer][i] == silver || testGame.discard[nextPlayer][i] == gold) {
                    printf("** Expect: Current player coins to increase.\n");
                    if (game.coins < testGame.coins) {
                        printf("PASSED: Coins increased.\n");
                        numTestsPassed++;
                    }
                    else {
                        printf("FAILED: Coins stayed the same.\n");
                        numTestsFailed++;
                    }
                }

                else if (testGame.discard[nextPlayer][i] == estate || testGame.discard[nextPlayer][i] == duchy || testGame.discard[nextPlayer][i] == province || testGame.discard[nextPlayer][i] == gardens || testGame.discard[nextPlayer][i] == great_hall) {
                    printf("** Expect: Current player hand count to increase.\n");
                    if (game.handCount[currentPlayer] < testGame.handCount[currentPlayer]) {
                        printf("PASSED: Current player hand count increased.\n");
                        numTestsPassed++;
                    }
                    else {
                        printf("FAILED: Current player hand count did not increase.\n");
                        numTestsFailed++;
                    }

                }
                else { 
                    printf("** Expect: Current player number of actions to increase.\n");
                    if (game.numActions < testGame.numActions) {
                        printf("PASSED: Number of Actions increased.\n");
                        numTestsPassed++;
                    }
                    else {
                        printf("FAILED: Number of Actions did not increase.\n");
                        numTestsFailed++;
                    }
                }
            }

        }
        printf("\n");
        
        done--;
        interationNum++;
    }
    
        //proportionPass = (numTestsPassed / interationNum);
        //proportionFail = (numTestsFailed / interationNum);

        printf("****************************** TEST 3 SUMMARY **********************************\n\n");


        printf("Test Passes: %.0f\n", numTestsPassed);
        printf("Test Fails: %.0f\n\n", numTestsFailed);

        printf("****************************** TEST 3 END **********************************\n\n");


    
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


void printDeck(struct gameState *state, int nextPlayer) {
    printf("Next player's deck: \n");
    for (int i = 0; i < state->deckCount[nextPlayer]; i++){
        printf("Position: %d Card: %d\n", i, state->deck[nextPlayer][i]);

    }
}

void printDiscard(struct gameState *state, int nextPlayer) {
    printf("Next player's discard pile: \n");
    for (int i = 0; i < state->discardCount[nextPlayer]; i++){
        printf("Position: %d Card: %d\n", i, state->discard[nextPlayer][i]);

    }
}
