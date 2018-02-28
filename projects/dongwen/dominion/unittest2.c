#include "dominion.h"
#include <stdio.h>

int compare(const int* a, const int* b);
// print the cards in a player's hand
// void print_hand(int player, struct gameState *state){
//     int i;
//     for (i=0; i < state->handCount[player]; i++){
//         printf("%d ", state->hand[player][i]);
//     }
//     printf("\n");
// }
// this function is built to count a card (supplyPos) in a players hand
int get_card_count(int supplyPos, int player, struct gameState *state){
    int i;
    int counter=0;
    for (i=0; i < state->discardCount[player]; i++){
        if(state->discard[player][i] == supplyPos){
        	counter++;
        }
    }
    return counter;
}

int main () {
  //keep track of overall passing test
  int fail = 0; 
  printf("Initialize a game with 2 players\n");
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  // set up test for functionality, buy a village card, expect it to be in hand
  int village_pre;
  int village_post; 
  int discard_count_pre = G.discardCount[0];
  initializeGame(2, k, 10, &G);
  printf("Player's Turn: %d\n", G.whoseTurn);
  printf("Num coins to spend pre buyCard: %d\n", G.coins);
  printf("Player 0 discard pre buy\n");
  printDiscard(0,&G); 
  printf("Village supply pre buyCard: %d\n", G.supplyCount[village]);
  printf("Num buys pre buyCard: %d\n", G.numBuys);
  village_pre = get_card_count(village,0,&G);
  printf("number village cards in discard pre buy: %d\n",village_pre);
  // execute function
  printf("execute buy card\n");
  int ret = buyCard(village, &G);
  if (ret != 0){
    printf("ERROR: BUY CARD NON ZERO RETURN VALUE\n");
    fail++;
  }
  printf("Num coins to spend post buyCard: %d\n", G.coins);
  printf("Village supply post buyCard: %d\n", G.supplyCount[village]);
  printf("Num buys post buyCard: %d\n", G.numBuys);
  printf("Player 0 discard post buy");
  printDiscard(0,&G); 
  village_post = get_card_count(village,0,&G);
  printf("number village cards in discard post buy: %d\n",village_post);
  // evaluate based on setup
  if(G.coins != 1){
  	printf("COIN ARITHMATIC FAIL\n");
  	fail++;
  }
  if(G.supplyCount[village] != 9){
  	printf("FAILURE TO DECREMENT SUPPLY COUNT\n");
  	fail++;
  }
  if(G.numBuys != 0){
  	printf("FAILURE TO DECREMENT NUM BUYS\n");
  	fail++;
  }
  if(village_post - village_pre != 1){
  	printf("FAILURE TO ADD CARD TO HAND\n");
  	fail++;
  }
  if(G.discardCount[0] - discard_count_pre != 1){
    printf("FAILURE TO INCREMEMNT DISCARD PILE WITH NEW CARD\n");
    fail++;  
  }
  // reinitialize and test failure mode 
  printf("Check case where no buys\n");
  initializeGame(2, k, 10, &G);
  G.numBuys = 0;
  ret = buyCard(village, &G);
  if(ret != -1){
  	printf("FAILURE TO VALIDATE NUM BUYS\n");
  	fail++; 	
  } 
  // reinitialize and test failure mode 
  printf("Check case where not enough card supply\n");
  initializeGame(2, k, 10, &G);
  G.supplyCount[village] = 0;
  ret = buyCard(village, &G);
  if(ret != -1){
  	printf("FAILURE TO VALIDATE CARD SUPPLY\n");
  	fail++; 	
  }
  // reinitialize and test failure mode 
  printf("Check case where not enough coins\n");
  initializeGame(2, k, 10, &G);
  G.coins = 0;
  ret = buyCard(village, &G);
  if(ret != -1){
  	printf("FAILURE TO VALIDATE COIN SUPPLY\n");
  	fail++; 	
  }
  printf("====================================\n");
  if(fail == 0){
    printf("BUY CARD TEST PASSED\n");
  }
  else{
  	printf("%d TEST FAILURE(s)\n", fail);
  }
  return 0;
}
