#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include "math.h"
#include <stdio.h>

// return a psudo random integer in given range (inclusive)
int rand_between(int min, int max){
    return rand() % (max + 1 - min) + min;
}

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
    G.deck[0][1] = 4;
    G.deck[0][4] = 1;
    G.deckCount[0] = 0;
    printHand(0,&G);
    printf("Hand Count: %d\n", G.handCount[0]);
    printDiscard(0,&G);
    printf("Discard Count: %d\n", G.discardCount[0]);
    printDeck(0,&G);
    printf("Deck Count: %d\n", G.deckCount[0]);
    printPlayed(0,&G);
    printf("Played Count: %d\n", G.playedCardCount);
    int ret = cardEffect(adventurer, -1,-1,-1,&G,0,0);
    printHand(0,&G);
    printf("Hand Count: %d\n", G.handCount[0]);
    printDiscard(0,&G);
    printf("Discard Count: %d\n", G.discardCount[0]);
    printDeck(0,&G);
    printf("Deck Count: %d\n", G.deckCount[0]);
    printPlayed(0,&G);
    printf("Played Count: %d\n", G.playedCardCount);
    // // track hand count 
    // int hand_count_pre = G.handCount[0];
    // printf("handCount pre: %d\n", hand_count_pre);
    // int ret = cardEffect(adventurer, -1,-1,-1,&G,0,0);
    // if (ret != 0){
    // 	printf("CARD EFFECT NON ZERO RETURN VALUE\n");
    // 	fail++;
    // }
    // // check that adventurer added two treasure cards
    // int hand_count_post = G.handCount[0];
    // printf("handCount post: %d\n", hand_count_post);
    // int new_cards = hand_count_post - (hand_count_pre);
    // if ( new_cards != 2){
    // 	if (new_cards < 2){
   	//         printf("ERROR TOO FEW CARDS DRAWN\n");    		
    // 	}
    // 	else{
    // 		printf("ERROR TOO MANY CARDS DRAWN\n");
    // 	}
    // 	fail++;  	
    // }
    // // check that only treasure cards were added 
    // if (is_treasure(G.hand[G.whoseTurn][5]) + is_treasure(G.hand[G.whoseTurn][6]) != 0){
    // 	printf("NON-TREASURE CARDS ADDED\n");
    // 	fail++;
    // }

    // printHand(0,&G);
    // printf("====================================\n");
    // if(fail == 0){
    //   printf(" ADVENTURER TEST PASSED\n");
    // }
    // else{
    // 	printf("%d TEST FAILURE(s)\n", fail);
    // }
    // SelectStream(2);
    // PutSeed(3);
    // int i;
    // for (i=0;i<35;i++){
    //     printf("%d\n",(int) floor(Random() * 2));
    // }
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