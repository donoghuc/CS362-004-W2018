#include "dominion.h"
#include "interface.h"
#include <stdio.h>
#include <assert.h>

int compare(const int* a, const int* b);


// test some state values (will be used multiple times)
int check_state(int fails, struct gameState *state){
    if (state->outpostPlayed != 0){
    	printf("ERROR OUTPOST PLAYED NOT SET\n");
    	fails++;
    } 

    if (state->phase != 0){
    	printf("ERROR PHASE NOT SET\n");
    	fails++;
    } 

    if (state->numActions != 1){
    	printf("ERROR NUM ACTIONS NOT SET\n");
    	fails++;
    }

    if (state->numBuys != 1){
    	printf("ERROR NUM BUYS NOT SET\n");
    	fails++;
    } 

    if (state->playedCardCount != 0){
    	printf("ERROR PLAYED CARD COUNT NOT SET\n");
    	fails++;
    } 

    if (state->handCount[state->whoseTurn] != 5){
    	printf("ERROR NEW HAND NOT DEALT\n");
    	fails++;   	
    }

    return fails;
}

int main () {
	// set up new game for testing
    int fail = 0; 
    printf("Initialize a game with 2 players\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);

    // use this to compare who's turn durring test
    int player = G.whoseTurn;
    // print out details of current player's state
    printf("Whos turn?: %d\n", G.whoseTurn);
    printf("Player 0 hand count: %d\n", G.handCount[0]);
    printState(&G);
    printHand(0,&G);      
    /// now execute funtion under test and check new state
    printf("Call endTurn\n");
    int ret = endTurn(&G);
    // will use this set twice so added to other function
    fail = check_state(fail, &G);
    if (ret != 0){
   		printf("END TURN GIVES NON ZERO RETURN");
    	fail++;	
    }
    // check that previous player does not have hand
    if (G.handCount[player] != 0){
   		printf("ERROR FAIL TO RESET HAND COUNT FOR LAST PLAYER");
    	fail++;
    }
    // check new player got hand
    if (G.handCount[G.whoseTurn] != 5){
    	printf("FAILED TO DRAW NEW HAND");
    	fail++;
    }
    // check who's turn is incremented 
    if (G.whoseTurn != (player + 1) % 2){
    	printf("FAILED TO INCREMENT PLAYER TURN");
    	fail++;
    }
    // print out state for debugging
    printf("Whos turn?: %d\n", G.whoseTurn);
    printf("Player 1 hand count: %d\n", G.handCount[0]);
    printState(&G);
    printHand(1,&G); 
    player = G.whoseTurn;

    // in order to test the "back to player zero" case, increment again
    printf("Call endTurn\n");
    ret = endTurn(&G);

    fail = check_state(fail, &G);
    if (ret != 0){
   		printf("END TURN GIVES NON ZERO RETURN");
    	fail++;	
    }

    if (G.handCount[player] != 0){
   		printf("ERROR FAIL TO RESET HAND COUNT FOR LAST PLAYER");
    	fail++;
    }

    // check new player got hand
    if (G.handCount[G.whoseTurn] != 5){
    	printf("FAILED TO DRAW NEW HAND");
    	fail++;
    }

    if (G.whoseTurn != (player + 1) % 2){
    	printf("FAILED TO INCREMENT PLAYER TURN");
    	fail++;
    }
    
    // final prints and message
    printf("Whos turn?: %d\n", G.whoseTurn);
    printf("Player 0 hand count: %d\n", G.handCount[0]);
    printState(&G);
    printHand(0,&G); 
    printf("====================================\n");
    if(fail == 0){
      printf("END TURN TEST PASSED\n");
    }
    else{
    	printf("%d TEST FAILURE(s)\n", fail);
    }

    return 0;
}
