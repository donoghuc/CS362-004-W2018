#include "dominion.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

// forward declaration of copare function for qsort function
int compare(const int* a, const int* b);

// I end up printing out deck a couple times so i wrote a function for it
void print_deck(int player, struct gameState *state){
  int i;
  for (i=0; i < state->deckCount[player]; i++){
    printf("%d ", state->deck[player][i]);
  }
  printf("\n");
}

// unit test for shuffle function implemented in dominion.c
int main () {
  //initialize a game with two players
  printf("Initialize a game with 2 players\n");
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  initializeGame(2, k, 10, &G);

  // will want to do some shuffles and compare back to original, so make a copy
  printf("Test that copy of initialized game is exact copy\n");
  struct gameState G2;
  memcpy (&G2, &G, sizeof(struct gameState));
  assert(memcmp(&G, &G2, sizeof(struct gameState)) == 0); 
  // print out pre and post shuffle and make sure the return values are 0
  printf("Whos turn?: %d\n", G.whoseTurn);
  printf("Player 0 deckCount: %d\n", G2.deckCount[0]);
  printf("Player 1 deckCount: %d\n", G.deckCount[1]);
  printf("Player 0 deck pre shuffle: ");
  print_deck(0, &G);
  printf("Player 1 deck pre shuffle: ");
  print_deck(1, &G);
  printf("Shuffle both players and assert return value is 0\n");
  assert(shuffle(0,&G) == 0);
  assert(shuffle(1,&G) == 0);
  printf("Both player shuffles return 0\n");
  printf("Player 0 deck post shuffle: ");
  print_deck(0, &G);
  printf("Player 1 deck post shuffle: ");
  print_deck(1, &G);
  // give the suffle function 10 tries to shuffle the decks, if they do not in 10 then there is likely a rpblem. 
  printf("Assert that the shuffle has shuffled the deck (give it several tries)\n");
  int i;
  int warning = 0;
  for (i=0; i<10; i++){
    if(memcmp(&G, &G2, sizeof(struct gameState)) != 0){
      printf("tries: %d\n",i + 1);
      break;
    }
    warning++;
  }
  assert(warning < 10);

  // make sure the content of the pre and post shuffle decks are the same
  printf("Assert no cards were added or removed from deck\n");
  qsort ((void*)(G.deck[0]), G.deckCount[0], sizeof(int), compare);
  qsort ((void*)(G.deck[1]), G.deckCount[1], sizeof(int), compare);
  qsort ((void*)(G2.deck[0]), G2.deckCount[0], sizeof(int), compare);
  qsort ((void*)(G2.deck[1]), G2.deckCount[1], sizeof(int), compare);
  assert(memcmp(&G, &G2, sizeof(struct gameState)) == 0);  

  // test that shuffle can return -1 when problem occurs 
  printf("Assert that -1 is returned when a players deck count is less than 1\n");
  G.deckCount[0] = 0;
  assert(shuffle(0,&G) == -1);
  printf("====================================\n");
  printf("SHUFFLE TEST PASSED\n");

  return 0;
}

