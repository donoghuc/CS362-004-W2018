#include "dominion.h"
#include "interface.h"
#include <stdio.h>
#include <assert.h>


int main () {
	// set up game state
    int fail = 0; 
    printf("Initialize a game with 2 players and add smithy to player 0 hand\n");
    struct gameState G;
    int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);
    // put council room in position 0 to play it
    G.hand[G.whoseTurn][0] = council_room;
    printHand(0,&G);
    // track hand count 
    int hand_count_pre = G.handCount[0];
    int other_hand_count = G.handCount[1];
    printf("whos turn?: player %d\n", G.whoseTurn);
    printf("handCount player 0 pre: %d\n", hand_count_pre);

    printf("player 1 hand and card count\n");
    printHand(1,&G);
    printf("handCount player 1 pre: %d\n", G.handCount[1]);
    printf("Now call council room effect\n");
    int buys = G.numBuys;
    printf("Num buys pre: %d\n", buys);
    int ret = cardEffect(council_room, -1,-1,-1,&G,0,0);
    if (ret != 0){
    	printf("CARD EFFECT NON ZERO RETURN VALUE\n");
    	fail++;
    }

    // council room should be discarded (so it cannot be in same position)
    if (G.hand[G.whoseTurn][0] == council_room){
   	    printf("ERROR FAILURE TO DISCARD COUNCIL ROOM\n");
    	fail++;
    }
    // check that 4 cards drawn
    int hand_count_post = G.handCount[0];
    printf("Player 0 hand and count post: %d\n", hand_count_post);
    printHand(0,&G);
    int new_cards = hand_count_post - (hand_count_pre - 1);
    if ( new_cards != 4){
    	if (new_cards < 4){
   	        printf("ERROR TOO FEW CARDS DRAWN\n");    		
    	}
    	else{
    		printf("ERROR TOO MANY CARDS DRAWN\n");
    	}
    	fail++;  	
    }
    // check that numBuys incremented
    printf("Num Buys post: %d\n", G.numBuys);
    if (G.numBuys - buys != 1){
    	printf("ERROR, BUYS NOT PROPERLY INCREMENTED\n");
    	fail++;
    }
    // check that other players get to draw a card. 
    printf("player 1 hand and count post\n");
    printHand(1,&G);
    printf("handCount player 1 post: %d\n", G.handCount[1]);
    int other_diff = G.handCount[1] - other_hand_count;
    if (other_diff != 1){
    	if (other_diff < 1){
   	        printf("ERROR OTHER PLAYER DID NOT GET NEW CARD\n");    		
    	}
    	else{
    		printf("ERROR OTHER PLAYER GOT TOO MANY NEW CARDS\n");
    	}
    	fail++;  
    }

    printf("====================================\n");
    if(fail == 0){
      printf("COUNCIL ROOM TEST PASSED\n");
    }
    else{
    	printf("%d TEST FAILURE(s)\n", fail);
    }
    return 0;
}

