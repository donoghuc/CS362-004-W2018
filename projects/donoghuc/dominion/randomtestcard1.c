#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include "math.h"
#include <stdio.h>

#define DEBUG 1

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
    int num_disc = total - num_deck - num_hand;
#if (DEBUG == 1)
    printf("num_deck: %d\nnum_hand: %d\nnum_disc: %d\n sum: %d\n total: %d\n",
                 num_deck, num_hand, num_disc,(num_deck+num_hand+num_disc), total);
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
    int possible; // With random generation of cards there may not be two treasure to possibly add
    //variables to build random call signature. 
    int choice1;
    int choice2;
    int choice3;
    int handPos;
    int bonus;

    int hand_count_pre;
    int deck_count_pre;
    int discard_count_pre;

    // execute random testing
    int i = 10; 
    while(i >= 0){
        generate_random_gamestate(0, &G);
        hand_count_pre = G.handCount[0];
        deck_count_pre = G.deckCount[0];
        discard_count_pre = G.discardCount[0];
        
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
#endif    
        if (ret != 0){
            fail++;
            printf("FAIL: non zero return value for card effect");
        }
        // possible = possible_treasure(&T_pre);
        // if (possible >= 2){
        //     if (T_pre.total != T_post.total){
        //         fail++;
        //         printf("FAIL: Total pre: %d\n total post: %d\n", T_pre.total, T_post.total);
        //     }
        //     if (T_post.hand_treasure - T_pre.hand_treasure != 2){
        //         fail++;
        //         printf("FAIL: Two treasure not gained\n");
        //     }
        //     if (G.hand[0][0] == adventurer){
        //         fail++;
        //         printf("FAIL: adventurer not discarded\n");
        //     }
        //     if (G.handCount[0] - hand_count_pre != 2){
        //         fail++;
        //         printf("FAIL: Handcount pre - handcount: %d\n",G.handCount[0] - hand_count_pre);
        //     }
        //     if (disc_deck_pre - (G.discardCount[0] + G.deckCount[0])  != 2){
        //         fail++;
        //         printf("FAIL: cards not removed from discard or deck\n");
        //     }
            

        // } else {
        //     if (T_pre.total != T_post.total){
        //         fail++;
        //         printf("FAIL: Total pre: %d\n total post: %d\n", T_pre.total, T_post.total);
        //     }
        //     if ((T_post.hand_treasure - T_pre.hand_treasure) != possible){
        //         fail++;
        //         printf("FAIL: %d treasure not gained\n", possible);
        //     }
        //     if (G.hand[0][0] == adventurer){
        //         fail++;
        //         printf("FAIL: adventurer not discarded\n");
        //     }

        //     if (G.handCount[0] - hand_count_pre != possible){
        //         fail++;
        //         printf("FAIL: Handcount pre - handcount: %d\n",G.handCount[0] - hand_count_pre);
        //     }
        //     if (disc_deck_pre - (G.discardCount[0] + G.deckCount[0])  != possible){
        //         fail++;
        //         printf("FAIL: cards not removed from discard or deck\n");
        //     }
        // }

        i--;  
    }

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