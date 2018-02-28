#include "dominion.h"
#include "interface.h"
#include <stdio.h>


int main () {
	// set up game state
    int fail = 0; 
    printf("Initialize a game with 2 players and add smithy to player 0 hand\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);
    // put smitthy in position 0 to play it
    G.hand[G.whoseTurn][0] = smithy;
    printHand(0,&G);
    // track hand count 
    int hand_count_pre = G.handCount[0];
    printf("handCount pre: %d\n", hand_count_pre);
    int ret = cardEffect(smithy, -1,-1,-1,&G,0,0);
    if (ret != 0){
    	printf("CARD EFFECT NON ZERO RETURN VALUE\n");
    	fail++;
    }
    // smithy should be discarded (so it cannot be in same position)
    if (G.hand[G.whoseTurn][0] == smithy){
   	    printf("ERROR FAILURE TO DISCARD SMITTHY\n");
    	fail++;
    }
    // test if three cards are added
    int hand_count_post = G.handCount[0];
    printf("handCount post: %d\n", hand_count_post);
    int new_cards = hand_count_post - (hand_count_pre - 1);
    if ( new_cards != 3){
    	if (new_cards < 3){
   	        printf("ERROR TOO FEW CARDS DRAWN\n");    		
    	}
    	else{
    		printf("ERROR TOO MANY CARDS DRAWN\n");
    	}
    	fail++;  	
    }
    printHand(0,&G);
    printf("====================================\n");
    if(fail == 0){
      printf("SMITTHY TEST PASSED\n");
    }
    else{
    	printf("%d TEST FAILURE(s)\n", fail);
    }
    return 0;
}
