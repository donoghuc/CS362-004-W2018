#include "dominion.h"
#include "interface.h"
#include <stdio.h>


int main () {
	// set up game state
    int fail = 0; 
    printf("Initialize a game with 2 players and add great_hall to player 0 hand\n");
    struct gameState G;
    int k[10] = {adventurer, great_hall, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);
    // put great hall in position 0 to play it
    G.hand[G.whoseTurn][0] = great_hall;
    printHand(0,&G);
    // track hand count 
    int hand_count_pre = G.handCount[0];

    printf("whos turn?: player %d\n", G.whoseTurn);
    printf("handCount player 0 pre: %d\n", hand_count_pre);

    int numActions = G.numActions;
    printf("Num Actions pre: %d\n", numActions);
    int ret = cardEffect(great_hall, -1,-1,-1,&G,0,0);
    if (ret != 0){
    	printf("CARD EFFECT NON ZERO RETURN VALUE\n");
    	fail++;
    }

    // great hall should be discarded (so it cannot be in same position)
    if (G.hand[G.whoseTurn][0] == great_hall){
   	    printf("ERROR FAILURE TO DISCARD GREAT HALL\n");
    	fail++;
    }
    // check that 4 cards drawn
    int hand_count_post = G.handCount[0];
    printf("Player 0 hand and count post: %d\n", hand_count_post);
    printHand(0,&G);
    int new_cards = hand_count_post - (hand_count_pre - 1);
    if ( new_cards != 1){
    	if (new_cards < 1){
   	        printf("ERROR TOO FEW CARDS DRAWN\n");    		
    	}
    	else{
    		printf("ERROR TOO MANY CARDS DRAWN\n");
    	}
    	fail++;  	
    }
    // check that numBuys incremented
    printf("Num actions post: %d\n", G.numActions);
    if (G.numActions - numActions != 1){
    	printf("ERROR, ACTIONS NOT PROPERLY INCREMENTED\n");
    	fail++;
    }


    printf("====================================\n");
    if(fail == 0){
      printf("GREAT HALL TEST PASSED\n");
    }
    else{
    	printf("%d TEST FAILURE(s)\n", fail);
    }
    return 0;
}
