#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include "math.h"
#include <stdio.h>

#define DEBUG 0
#define NUM_TESTS 500

// data structure for keepin track of treasure totals
struct totals{
    int total;
    int hand_treasure;
    int deck_treasure;
    int disc_treasure; 
};

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

// for debuging print out the treasure values
void print_totals(struct totals *T){
    printf("total: %d\n hand_treasure: %d\n deck_treasure: %d\n disc_treasure: %d\n",
        T->total, T->hand_treasure, T->deck_treasure, T->disc_treasure);
}

// this is the number of treasure cards possible for adventurer to find (deck treasure plus discard treasure)
int possible_treasure(struct totals *T){
    return T->deck_treasure + T->disc_treasure;
}

// count the treasure for a given player for use in comparing adventurer effect
void count_treasure(int player, struct gameState *G, struct totals *T){
    T->hand_treasure = 0; 
    T->deck_treasure = 0;
    T->disc_treasure = 0;
    int i;
    for (i=0;i<G->handCount[player];i++){
        if(is_treasure(G->hand[player][i]) == 0){
            T->hand_treasure++;
        }
    }
    for (i=0;i<G->deckCount[player];i++){
        if(is_treasure(G->deck[player][i]) == 0){
            T->deck_treasure++;
        }
    }
    for (i=0;i<G->discardCount[player];i++){
        if(is_treasure(G->discard[player][i]) == 0){
            T->disc_treasure++;
        }
    }

    // printf("%d\n", G->handCount[0]);
    T->total = G->handCount[player] + G->deckCount[player] + G->discardCount[player];
}


/* generate a random game state with variables relevant to adventurer effect*/
void generate_random_gamestate(int player, struct gameState *G){
    // have a total number of cards to distribute, the hand must have at least one card (adventurer)
    int total = rand_between(1,500);
    int num_deck = rand_between(0, total - 1);
    int num_hand = rand_between(1, total - num_deck);
    // int num_disc = total - num_deck - num_hand;
    int num_disc = rand_between(0,(total - num_deck - num_hand));
    int num_played = total - num_deck - num_hand - num_disc;
#if (DEBUG == 1)
    printf("num_deck: %d\nnum_hand: %d\nnum_disc: %d\n sum: %d\n total: %d\n",
                 num_deck, num_hand, num_disc,(num_deck+num_hand+num_disc+num_played), total);
#endif  
    // distribute cards into deck, hand and discard (random cards between 0 and 26 inclusive)
    // fill deck
    int i;
    G->deckCount[player] = num_deck;
    for (i=0; i < num_deck; i++){
        G->deck[player][i] = rand_between(0, 26);
    }
    // fill hand 
    G->handCount[player] = num_hand;
    for (i=0; i < num_hand; i++){
        G->hand[player][i] = rand_between(0, 26);
    }
    // fill discard
    G->discardCount[player] = num_disc;
    for (i=0; i < num_disc; i++){
        G->discard[player][i] = rand_between(0, 26);
    }
    // fill played
    G->playedCardCount = num_played;
    for (i=0; i < num_disc; i++){
        G->playedCards[i] = rand_between(0, 26);
    }
    // set adventurer to hand pos 0
    G->hand[G->whoseTurn][0] = adventurer;


}


int main () {
    //seed the random generator for my rand_between function with seconds since epoch
    srand(time(NULL));
    // keep track of failure cases for final report
    int fail = 0; 
    int fail_non_zero = 0;
    int fail_total_cards = 0;
    int fail_played_cards = 0;
    int fail_treasure = 0;
    int fail_hand_count = 0;
    int fail_decrement_dec_disc = 0; 
    // initialize a game state (pre randomization)
    struct gameState G;
    struct totals T_pre;
    struct totals T_post;
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
    int ret; 
    // variables to track the pre-card effect game state
    int hand_count_pre;
    int disc_deck_pre;
    int played_pre;

    // execute random testing iterations
    int i = NUM_TESTS; 
    while(i > 0){
        // generate a random game state and log the pre-conditions
        generate_random_gamestate(0, &G);
        count_treasure(0, &G, &T_pre);
        hand_count_pre = G.handCount[0];
        disc_deck_pre = G.discardCount[0] + G.deckCount[0];
        played_pre = G.playedCardCount; 
        
        // print out a detailed snapshot of game state if in debug mode 
#if (DEBUG == 1)
        print_totals(&T_pre);
        printHand(0,&G);
        printf("Hand Count: %d\n", G.handCount[0]);
        printDiscard(0,&G);
        printf("Discard Count: %d\n", G.discardCount[0]);
        printDeck(0,&G);
        printf("Deck Count: %d\n", G.deckCount[0]);
        printPlayed(0,&G);
        printf("Played Count: %d\n", G.playedCardCount);
#endif       
        // assign random inputs (choose random in range +/- 500) 
        choice1 = rand_between(-500,500);
        choice2 = rand_between(-500,500);
        choice3 = rand_between(-500,500);
        handPos = 0;
        bonus = rand_between(-500,500);
        // call the card effect function 
        ret = cardEffect(adventurer, choice1,choice2,choice3,&G,handPos,bonus);
        count_treasure(0, &G, &T_post);
        // print out post-effect state for debug mode 
#if (DEBUG == 1)
        print_totals(&T_post);
        printHand(0,&G);
        printf("Hand Count: %d\n", G.handCount[0]);
        printDiscard(0,&G);
        printf("Discard Count: %d\n", G.discardCount[0]);
        printDeck(0,&G);
        printf("Deck Count: %d\n", G.deckCount[0]);
        printPlayed(0,&G);
        printf("Played Count: %d\n", G.playedCardCount);   
#endif    
        // first test case is if function returns non zero value
        if (ret != 0){
            fail++;
            fail_non_zero++;
#if (DEBUG == 1)
            printf("FAIL: non zero return value for card effect");
#endif
        }
        // now check that the total number of cards did not change (no cards lost or gained)
        if (T_pre.total != T_post.total){
            fail++;
            fail_total_cards++;
#if (DEBUG == 1)
            printf("FAIL: Total pre: %d\n total post: %d\n", T_pre.total, T_post.total);
#endif
        }
        // check that card played count is incremented 
        if (G.playedCardCount - played_pre != 1){
            fail++;
            fail_played_cards++;
#if (DEBUG == 1)
            printf("FAIL: %d cards played.\n", G.playedCardCount - played_pre);
#endif
        }
        // track the number of possible treasure to determine how many possible treasures there are to find
        possible = possible_treasure(&T_pre);
        if (possible >= 2){
            // there are at least two treasure to find
            if (T_post.hand_treasure - T_pre.hand_treasure != 2){
                fail++;
                fail_treasure++;
#if (DEBUG == 1)
                printf("FAIL: Two treasure not gained\n");
#endif
            }
            // make sure hand count is increased by two (with adventurer being discarded)
            if (G.handCount[0] - (hand_count_pre - 1) != 2){
                fail++;
                fail_hand_count++;
#if (DEBUG == 1)
                printf("FAIL: Handcount pre - handcount: %d\n",G.handCount[0] - (hand_count_pre - 1));
#endif
            }
            // check that 2 cards have been removed from discard/deck
            if (disc_deck_pre - (G.discardCount[0] + G.deckCount[0])  != 2){
                fail++;
                fail_decrement_dec_disc++;
#if (DEBUG == 1)
                printf("FAIL: cards not removed from discard or deck\n");
#endif
            }        

        } else {
            // there are either 0 or 1 treasure to find, make sure that amoutn is found
            if ((T_post.hand_treasure - T_pre.hand_treasure) != possible){
                fail++;
                fail_treasure++;
#if (DEBUG == 1)
                printf("FAIL: %d treasure not gained\n", possible);
#endif
            }
            // check that 0 or 1 cards goes in to hand
            if (G.handCount[0] - (hand_count_pre - 1) != possible){
                fail++;
                fail_hand_count++;
#if (DEBUG == 1)
                printf("FAIL: Handcount pre - handcount: %d\n",G.handCount[0] - (hand_count_pre - 1));
#endif
            }
            // check that 0 or 1 cards have been removed from discard/deck
            if (disc_deck_pre - (G.discardCount[0] + G.deckCount[0])  != possible){
                fail++;
                fail_decrement_dec_disc++;
#if (DEBUG == 1)
                printf("FAIL: cards not removed from discard or deck\n");
#endif
            }
        }
        // test conditional to keep while loop going
        i--;  
    }
    // print test results 
    if (fail == 0) {
        printf("%d Random Tests Pass.\n",NUM_TESTS);
    } else{
        printf("Total Tests: %d \n",NUM_TESTS);
        printf("Total test failures: %d\n", fail);
        printf("Non zero cardEffect return: %d\n", fail_non_zero);
        printf("Total cards off after call: %d \n", fail_total_cards);
        printf("Played card not incremented: %d \n", fail_played_cards);
        printf("Treasure not gained: %d \n", fail_treasure);
        printf("Hand count not incremented: %d \n", fail_hand_count);
        printf("Cards nor removed from deck/discard: %d \n", fail_decrement_dec_disc);
    }

    return 0;
}

