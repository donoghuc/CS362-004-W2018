#include "dominion.h"
#include <stdio.h>
#include <assert.h>

int compare(const int* a, const int* b);

int main () {
    int fail = 0; 
    printf("Initialize a game with 2 players\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);       
    printf("Whos turn?: %d\n", G.whoseTurn);
    printf("Call endTurn\n");
    int ret = endTurn(&G);
    printf("Whos turn?: %d\n", G.whoseTurn);
    return 0;
}

// int endTurn(struct gameState *state) {
//   int k;
//   int i;
//   int currentPlayer = whoseTurn(state);
  
//   //Discard hand
//   for (i = 0; i < state->handCount[currentPlayer]; i++){
//     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
//     state->hand[currentPlayer][i] = -1;//Set card to -1
//   }
//   state->handCount[currentPlayer] = 0;//Reset hand count
    
//   //Code for determining the player
//   if (currentPlayer < (state->numPlayers - 1)){ 
//     state->whoseTurn = currentPlayer + 1;//Still safe to increment
//   }
//   else{
//     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
//   }

//   state->outpostPlayed = 0;
//   state->phase = 0;
//   state->numActions = 1;
//   state->coins = 0;
//   state->numBuys = 1;
//   state->playedCardCount = 0;
//   state->handCount[state->whoseTurn] = 0;

//   //int k; move to top
//   //Next player draws hand
//   for (k = 0; k < 5; k++){
//     drawCard(state->whoseTurn, state);//Draw a card
//   }

//   //Update money
//   updateCoins(state->whoseTurn, state , 0);

//   return 0;
// }

// struct gameState {
//   int numPlayers; //number of players
//   int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
//   int embargoTokens[treasure_map+1];
//   int outpostPlayed;
//   int outpostTurn;
//   int whoseTurn;
//   int phase;
//   int numActions; /* Starts at 1 each turn */
//   int coins; /* Use as you see fit! */
//   int numBuys; /* Starts at 1 each turn */
//   int hand[MAX_PLAYERS][MAX_HAND];
//   int handCount[MAX_PLAYERS];
//   int deck[MAX_PLAYERS][MAX_DECK];
//   int deckCount[MAX_PLAYERS];
//   int discard[MAX_PLAYERS][MAX_DECK];
//   int discardCount[MAX_PLAYERS];
//   int playedCards[MAX_DECK];
//   int playedCardCount;
// };