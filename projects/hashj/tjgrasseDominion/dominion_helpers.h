#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int drawXCards(int count, int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);
int isTreasure(int card);
int isVictoryCard(int card);
int locateAndDiscard(int trashCard, int player, struct gameState *state, int trashFlag);
void discardHand(struct gameState *state, int player);
int getCardHandQuantity(int card, struct gameState *state, int player);
int getNextPlayer(int currentPlayer, int numPlayers);
int discardLastDrawnCard(int player, struct gameState *state);
int returnLastDrawnCardType(int player, struct gameState *state);

#endif