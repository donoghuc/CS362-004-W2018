#include "dominion.h"
#include <stdio.h>


int compare(const int* a, const int* b);
int updateCoins(int player, struct gameState *state, int bonus);

// print the cards in a player's hand
void print_hand(int player, struct gameState *state){
    int i;
    for (i=0; i < state->handCount[player]; i++){
        printf("%d ", state->hand[player][i]);
    }
    printf("\n");
}

int main () {
    int fail = 0; 
    printf("Initialize a game with 2 players\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);       
    printf("Initial Coin Count: %d\n", G.coins);
    printf("Player 0 hand: ");
    print_hand(0, &G);
    printf("Test that updateCoins properly counts player 0 hand\n");
    int ret;
    ret = updateCoins(0, &G, 0);
    printf("coins calculated: %d\n", G.coins);
    if(G.coins != 4){
    	printf("FAILURE TO COUNT COINS IN HAND\n");
    	fail++;
    }
    if(ret != 0){
    	printf("UPDATE COINS NON 0 RETURN VALUE\n");
    	fail++;
    }
    printf("Test bonus addition of 1\n");
    ret = updateCoins(0, &G, 1);
    printf("coins calculated: %d\n", G.coins);
    if(G.coins != 5){
    	printf("FAILURE TO COUNT COINS IN HAND\n");
    	fail++;
    }
    if(ret != 0){
    	printf("UPDATE COINS NON 0 RETURN VALUE\n");
    	fail++;
    }
    printf("Test addition of a silver and gold card\n");
    G.hand[0][0] = gold;
    G.hand[0][1] = silver;
    print_hand(0,&G);
    ret = updateCoins(0, &G, 0);
    printf("coins calculated: %d\n", G.coins); 
    if(G.coins != 7){
    	printf("FAILURE TO COUNT COINS IN HAND\n");
    	fail++;
    }
    if(ret != 0){
    	printf("UPDATE COINS NON 0 RETURN VALUE\n");
    	fail++;
    }
    printf("====================================\n");
    if(fail == 0){
      printf("UPDATE COINS TEST PASSED\n");
    }
    else{
    	printf("%d TEST FAILURE(s)\n", fail);
    }
       
    return 0;
}

