#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include "math.h"
#include <stdio.h>

#define DEBUG 0
#define NUM_TESTS 500

// return a psudo random integer in given range (inclusive)
int rand_between(int min, int max){
    return rand() % (max + 1 - min) + min;
}

/* generate a random game state with variables relevant to adventurer effect*/
void generate_random_gamestate(int player, struct gameState *G){
    // have a total number of cards to distribute, the hand must have at least one care (adventurer)
    int total = rand_between(1,500);
    int num_deck = rand_between(0, total - 1);
    int num_hand = rand_between(1, total - num_deck);
    int num_disc = rand_between(0,(total - num_deck - num_hand));
    int num_played = total - num_deck - num_hand - num_disc;
#if (DEBUG == 1)
    printf("num_deck: %d\nnum_hand: %d\nnum_disc: %d\n sum: %d\n total: %d\n",
                 num_deck, num_hand, num_disc,(num_deck+num_hand+num_disc+num_played), total);
#endif  
    // distribute cards into deck, hand and discard (random cards between 0 and 26 inclusive)

    int i;
    G->deckCount[player] = num_deck;
    for (i=0; i < num_deck; i++){
        G->deck[player][i] = rand_between(0, 26);
    }

    G->handCount[player] = num_hand;
    for (i=0; i < num_hand; i++){
        G->hand[player][i] = rand_between(0, 26);
    }

    G->discardCount[player] = num_disc;
    for (i=0; i < num_disc; i++){
        G->discard[player][i] = rand_between(0, 26);
    }

    G->playedCardCount = num_played;
    for (i=0; i < num_played; i++){
        G->playedCards[i] = rand_between(0, 26);
    }

    G->hand[G->whoseTurn][0] = smithy;
}


int main () {
    //seed the random generator for my rand_between function with seconds since epoch
    srand(time(NULL));
    // keep track of failure cases for final report
    int fail = 0; 
    // initialize a game state (pre randomization)
    struct gameState G;

    // this will be overwritten...
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);

    int total_cards; //variable for comparing total cards allocated for test
    int possible; // With random generation of cards there may not be enough cards in deck + discard 
    //variables to build random call signature. 
    int choice1;
    int choice2;
    int choice3;
    int handPos;
    int bonus;

    int hand_count_pre;
    int deck_count_pre;
    int discard_count_pre;
    int played_count_pre; 
    int total_pre;

    // execute random testing
    int i = NUM_TESTS; 
    while(i > 0){
        generate_random_gamestate(0, &G);
        hand_count_pre = G.handCount[0];
        deck_count_pre = G.deckCount[0];
        discard_count_pre = G.discardCount[0];
        played_count_pre = G.playedCardCount;
        total_pre = G.handCount[0] + G.deckCount[0] + G.discardCount[0] + G.playedCardCount;
        
#if (DEBUG == 1)
        printHand(0,&G);
        printf("Hand Count: %d\n", G.handCount[0]);
        printDiscard(0,&G);
        printf("Discard Count: %d\n", G.discardCount[0]);
        printDeck(0,&G);
        printf("Deck Count: %d\n", G.deckCount[0]);
        printPlayed(0,&G);
        printf("Played Count: %d\n", G.playedCardCount);
#endif        
        int choice1 = rand_between(-500,500);
        int choice2 = rand_between(-500,500);
        int choice3 = rand_between(-500,500);
        int handPos = 0;
        int bonus = rand_between(-500,500);
        int ret = cardEffect(smithy, choice1,choice2,choice3,&G,0,bonus);
        
#if (DEBUG == 1)
        printHand(0,&G);
        printf("Hand Count: %d\n", G.handCount[0]);
        printDiscard(0,&G);
        printf("Discard Count: %d\n", G.discardCount[0]);
        printDeck(0,&G);
        printf("Deck Count: %d\n", G.deckCount[0]);
        printPlayed(0,&G);
        printf("Played Count: %d\n", G.playedCardCount);   
        printf("hand: %d, deck: %d, discard: %d, played: %d, total: %d \n",hand_count_pre, deck_count_pre, discard_count_pre, played_count_pre, total_pre);
        printf("hand: %d, deck: %d, discard: %d, played: %d, total: %d \n",G.handCount[0], G.deckCount[0], G.discardCount[0], G.playedCardCount,
                                                                         G.handCount[0] + G.deckCount[0] + G.discardCount[0] + G.playedCardCount);
#endif    
        if (ret != 0){
            fail++;
            printf("FAIL: non zero return value for card effect");
        }
        if (total_pre != (G.handCount[0] + G.deckCount[0] + G.discardCount[0] + G.playedCardCount)){
            fail++;
            printf("FAIL: Total pre: %d\n total post: %d\n", total_pre, (G.handCount[0] + G.deckCount[0] + G.discardCount[0] + G.playedCardCount));
        }
        if (G.playedCardCount - played_count_pre != 1){
            fail++;
            printf("FAIL: %d cards played.\n", G.playedCardCount - played_count_pre);
        }
        possible = G.deckCount[0] + G.discardCount[0];
        if (possible >= 3){
            if (G.handCount[0] - (hand_count_pre - 1) != 3){
                fail++;
                printf("FAIL: %d cards drawn\n", G.handCount[0] - (hand_count_pre - 1));
            }
            if ((deck_count_pre - G.deckCount[0]) + (discard_count_pre - G.discardCount[0]) != 3){
                fail++;
                printf("FAIL: Diff of deck count: %d, diff of discard count: %d\n", deck_count_pre - G.deckCount[0], discard_count_pre - G.discardCount[0]);
            }
        }
        else if (possible < 3){
            if (G.handCount[0] - (hand_count_pre - 1) != possible){
                fail++;
                printf("FAIL: %d cards drawn\n", G.handCount[0] - (hand_count_pre - 1));
            }
            if ((deck_count_pre - G.deckCount[0]) + (discard_count_pre - G.discardCount[0]) != possible){
                fail++;
                printf("FAIL: Diff of deck count: %d, diff of discard count: %d\n", deck_count_pre - G.deckCount[0], discard_count_pre - G.discardCount[0]);
            }     
        }

        i--;  
    }

    if (fail == 0) {
        printf("%d Random Tests Pass.\n",NUM_TESTS);
    } else{
        printf("%d Test Failures.\n", fail);
    }

    return 0;
}
