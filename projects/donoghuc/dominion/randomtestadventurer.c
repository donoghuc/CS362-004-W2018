#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include "math.h"
#include <stdio.h>

#define DEBUG 0

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

    G->hand[G->whoseTurn][0] = adventurer;


}


int main () {
    //seed the random generator for my rand_between function with seconds since epoch
    srand(time(NULL));
    // keep track of failure cases for final report
    int fail = 0; 
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

    int hand_count_pre;
    int disc_deck_pre;

    // execute random testing
    int i = 100; 
    while(i >= 0){
        generate_random_gamestate(0, &G);
        count_treasure(0, &G, &T_pre);
        hand_count_pre = G.handCount[0];
        disc_deck_pre = G.discardCount[0] + G.deckCount[0];
        
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
        int choice1 = rand_between(-500,500);
        int choice2 = rand_between(-500,500);
        int choice3 = rand_between(-500,500);
        int handPos = rand_between(-500,500);
        int bonus = rand_between(-500,500);
        int ret = cardEffect(adventurer, choice1,choice2,choice3,&G,handPos,bonus);
        count_treasure(0, &G, &T_post);
        
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
        if (ret != 0){
            fail++;
            printf("FAIL: non zero return value for card effect");
        }
        possible = possible_treasure(&T_pre);
        if (possible >= 2){
            if (T_pre.total != T_post.total){
                fail++;
                printf("FAIL: Total pre: %d\n total post: %d\n", T_pre.total, T_post.total);
            }
            if (T_post.hand_treasure - T_pre.hand_treasure != 2){
                fail++;
                printf("FAIL: Two treasure not gained\n");
            }
            if (G.hand[0][0] == adventurer){
                fail++;
                printf("FAIL: adventurer not discarded\n");
            }
            if (G.handCount[0] - hand_count_pre != 2){
                fail++;
                printf("FAIL: Handcount pre - handcount: %d\n",G.handCount[0] - hand_count_pre);
            }
            if (disc_deck_pre - (G.discardCount[0] + G.deckCount[0])  != 2){
                fail++;
                printf("FAIL: cards not removed from discard or deck\n");
            }
            

        } else {
            if (T_pre.total != T_post.total){
                fail++;
                printf("FAIL: Total pre: %d\n total post: %d\n", T_pre.total, T_post.total);
            }
            if ((T_post.hand_treasure - T_pre.hand_treasure) != possible){
                fail++;
                printf("FAIL: %d treasure not gained\n", possible);
            }
            if (G.hand[0][0] == adventurer){
                fail++;
                printf("FAIL: adventurer not discarded\n");
            }

            if (G.handCount[0] - hand_count_pre != possible){
                fail++;
                printf("FAIL: Handcount pre - handcount: %d\n",G.handCount[0] - hand_count_pre);
            }
            if (disc_deck_pre - (G.discardCount[0] + G.deckCount[0])  != possible){
                fail++;
                printf("FAIL: cards not removed from discard or deck\n");
            }
        }

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