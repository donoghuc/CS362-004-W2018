#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include "math.h"
#include <stdio.h>

struct totals{
    int total;
    int hand_treasure;
    int deck_treasure;
    int disc_treasure; 
}

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

/* generate a random game state with variables relevant to adventurer effect*/
int generate_random_gamestate(int player, struct gameState *G, struct totals *T){
    // have a total number of cards to distribute, the hand must have at least one care (adventurer)
    int total = rand_between(1,15);
    int num_deck = rand_between(0, total - 1);
    int num_hand = rand_between(1, total - num_deck);
    int num_disc = total - num_deck - num_hand;
    printf("num_deck: %d\nnum_hand: %d\nnum_disc: %d\n sum: %d\n total: %d\n", num_deck, num_hand, num_disc,(num_deck+num_hand+num_disc), total);
    // distribute cards into deck, hand and discard (random cards between 0 and 26 inclusive)
    int i;
    G->deckCount[player] = num_deck;
    for (i=0; i < num_deck; i++);
        G->deck[player][i] = rand_between(0, 26);
        if(is_treasure(G->deck[player][i]) == 0){
            T->deck_treasure++; 
        }

    G->handCount[player] = num_hand;
    for (i=0; i < num_hand; i++);
        G->hand[player][i] = rand_between(0, 26);

    G->discardCount[player] = num_disc;
    for (i=0; i < num_disc; i++);
        G->discard[player][i] = rand_between(0, 26);

    G->hand[G->whoseTurn][player] = adventurer;

    T->total = total;
}


int main () {
    //seed the random generator for my rand_between function with seconds since epoch
    srand(time(NULL));
    // keep track of failure cases for final report
    int fail = 0; 
    // initialize a game state (pre randomization)
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);
    int total_cards; //variable for comparing total cards allocated for test

    // execute random testing
    int i = 10; 
    while(i >= 0){
        total_cards = generate_random_gamestate(0, &G);
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