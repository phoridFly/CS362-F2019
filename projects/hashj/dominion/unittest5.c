#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {

    int seed = 1000;
    int numPlayers = 2;
    int notNegOne = 0;

    int k[10] = {adventurer, council_room, ambassador, tribute, mine,
    remodel, smithy, mine, baron, minion};

    struct gameState game, testGame, gameOne, testGameOne;

    initializeGame(numPlayers, k, seed, &game);

    printf("*********************** BEGIN UNIT TEST 5 ************************************\n");
    printf("Testing the function cardEffectMine():\n\n");

    // setup a hand with appropriate treasure cards
    game.handCount[0] = 5;
    game.hand[0][0] = estate;
    game.hand[0][1] = silver;
    game.hand[0][2] = copper;
    game.hand[0][3] = smithy;
    game.hand[0][4] = mine;

    int choice1 = 1;
    int choice2 = gold;
    int currentPlayer = 0;
    int handPos = 4;

    memcpy(&testGame, &game, sizeof(struct gameState));

    cardEffectMine(&testGame, currentPlayer, choice1, choice2, handPos);

    printf("Part 1: Choice1 = Silver Card, Choice2 = Gold (Trade Silver for Gold)\n");
    printf("** Expect: Hand after to contain a Gold card. **\n");
    printf("** Expect: Hand after to not have a Silver card or Mine card. **\n");
    printf("** Expect: Hand after to have 4 cards. **\n");

    int goldFound = 0;
    int silverFound = 0;

    for(int i = 0; i < game.handCount[0]; i++) {
        printf("Card %d Before: %d     Card %d After: %d\n", i, game.hand[0][i], i, testGame.hand[0][i]);
    
        if (testGame.hand[currentPlayer][i] == silver) {
            silverFound = 1;
        }

        if (testGame.hand[currentPlayer][i] == gold) {
            goldFound = 1;
        }
    }

    if (goldFound == 1) {
        printf("PASSED: Gold successfully exchanged.\n");
    }
    else if(goldFound == 0) {
        printf("FAILED: Gold card not found.\n");
    }

    if (silverFound == 0) {
        printf("PASSED: Silver card discarded from hand.\n");
    }
    else if(silverFound == 1) {
        printf("FAILED: Silver card still in hand.\n");
    }

    if (testGame.handCount[currentPlayer] != 4) {
        printf("FAILED: Incorrect number of cards in hand. Cards in hand = %d\n\n", testGame.handCount[currentPlayer]);
    }
    else if (testGame.handCount[currentPlayer] == 4) {
        printf("PASSED: Four cards are in hand.\n\n");
    }

    printf("Part 2: Choice1 = Estate card, Choice2 = Gold (Estate for Gold)\n");
    printf("** Expect: cardEffectMine function should return -1. **\n");

    initializeGame(numPlayers, k, seed, &gameOne);

    // setup a hand with appropriate treasure cards
    gameOne.handCount[0] = 5;
    gameOne.hand[0][0] = estate;
    gameOne.hand[0][1] = silver;
    gameOne.hand[0][2] = copper;
    gameOne.hand[0][3] = smithy;
    gameOne.hand[0][4] = mine;

    memcpy(&testGameOne, &gameOne, sizeof(struct gameState));


    choice1 = 0;
    choice2 = gold;
    currentPlayer = 0;
    handPos = 4;

    notNegOne = cardEffectMine(&testGameOne, currentPlayer, choice1, choice2, handPos);

    if (notNegOne == -1) {
        printf("PASSED: function returned -1, Estate was not traded for Gold\n\n");
    }
    else if (notNegOne == 0) {
        printf("FAILED: function erroneously proceeded allowing illegal move.\n\n");
    }

    printf("Part 3: Choice1 = Silver card, Choice2 = 27, one beyond range of enumerated cards\n");
    printf("** Expect: cardEffectMine function should return -1. **\n");

    memcpy(&testGameOne, &gameOne, sizeof(struct gameState));

    choice1 = 1;
    choice2 = 27;

    notNegOne = cardEffectMine(&testGameOne, currentPlayer, choice1, choice2, handPos);

    if (notNegOne == -1) {
        printf("PASSED: function returned -1, card number was beyond Treasure-Map\n\n");
    }
    else if (notNegOne == 0) {
        printf("FAILED: function erroneously proceeded allowing illegal move.\n\n");
    }

    printf("Part 4: Choice1 = Copper card, Choice2 = Silver\n");
    printf("** Expect: cardEffectMine function should return 0. **\n");

    memcpy(&testGameOne, &gameOne, sizeof(struct gameState));
    choice1 = 2;
    choice2 = silver;

    notNegOne = cardEffectMine(&testGameOne, currentPlayer, choice1, choice2, handPos);

    if (notNegOne == 0) {
        printf("PASSED: allowed a legal Treasure card trade.\n\n");
    }
    else if (notNegOne == -1) {
        printf("FAILED: returned -1, function did not allow a legal Treasure card trade.\n\n");
    }

    printf("Part 5: Choice1 = Copper card, Choice2 = Gold\n");
    printf("** Expect: cardEffectMine function should return -1. **\n");

    memcpy(&testGameOne, &gameOne, sizeof(struct gameState));
    choice1 = 2;
    choice2 = gold;

    notNegOne = cardEffectMine(&testGameOne, currentPlayer, choice1, choice2, handPos);

    if (notNegOne == 0) {
        printf("FAILED: allowed an illegal Treasure card trade of a difference greater than 3.\n\n");
    }
    else if (notNegOne == -1) {
        printf("PASSED: returned -1, function did not allow an illegal Treasure card trade of a difference greater than 3.\n\n");
    }

    printf("\n\n");

    printf("Unit Test 5, Mine, Completed.\n");
    printf("*********************** END  UNIT TEST 5 ************************************\n\n");

}