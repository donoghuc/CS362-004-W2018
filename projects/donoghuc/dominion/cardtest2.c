#include "dominion.h"
#include "interface.h"
#include <stdio.h>

// return 0 if card is a treasutre, one if not
int is_treasure(int card){
    if (card == copper || card == silver || card == gold){
        return 0;
    }
    else{
    	return 1;
    }
}

int main () {
	// set up game state
    int fail = 0; 
    printf("Initialize a game with 2 players and add smithy to player 0 hand\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);
    // put smitthy in position 0 to play it
    G.hand[G.whoseTurn][0] = adventurer;
    printHand(0,&G);
    // track hand count 
    int hand_count_pre = G.handCount[0];
    printf("handCount pre: %d\n", hand_count_pre);
    int ret = cardEffect(adventurer, -1,-1,-1,&G,0,0);
    if (ret != 0){
    	printf("CARD EFFECT NON ZERO RETURN VALUE\n");
    	fail++;
    }
    // check that adventurer added two treasure cards
    int hand_count_post = G.handCount[0];
    printf("handCount post: %d\n", hand_count_post);
    int new_cards = hand_count_post - (hand_count_pre);
    if ( new_cards != 2){
    	if (new_cards < 2){
   	        printf("ERROR TOO FEW CARDS DRAWN\n");    		
    	}
    	else{
    		printf("ERROR TOO MANY CARDS DRAWN\n");
    	}
    	fail++;  	
    }
    // check that only treasure cards were added 
    if (is_treasure(G.hand[G.whoseTurn][5]) + is_treasure(G.hand[G.whoseTurn][6]) != 0){
    	printf("NON-TREASURE CARDS ADDED\n");
    	fail++;
    }

    printHand(0,&G);
    printf("====================================\n");
    if(fail == 0){
      printf(" ADVENTURER TEST PASSED\n");
    }
    else{
    	printf("%d TEST FAILURE(s)\n", fail);
    }
    return 0;
}

