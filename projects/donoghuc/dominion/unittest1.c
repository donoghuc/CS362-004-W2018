#include "dominion.h"
#include <stdio.h>
#include <assert.h>

int compare(const int* a, const int* b);

int main () {
  // struct gameState G;
  // struct gameState G2;

  // // Initialize G.

  // memcpy (&G2, &G, sizeof(struct gameState));

  // int ret = shuffle(0,&G);

  // if (G.deckCount[0] > 0) {
  //   assert (ret != -1);
    
  //   qsort ((void*)(G.deck[0]), G.deckCount[0], sizeof(int), compare);
  //   qsort ((void*)(G2.deck[0]), G2.deckCount[0], sizeof(int), compare);    
  // } else
  //   assert (ret == -1);

  // assert(memcmp(&G, &G2, sizeof(struct gameState)) == 0);  

  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  initializeGame(2, k, 10, &G);
  printf("%d", G.numPlayers);
  assert(1 == 1);
  return 0;
}

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