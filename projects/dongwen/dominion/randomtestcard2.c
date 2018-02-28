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
    // generate random amount of coins 
    G->coins = rand(0,500);
    // place steward in hand position 0
    G->hand[G->whoseTurn][0] = steward;
}


int main () {
    //seed the random generator for my rand_between function with seconds since epoch
    srand(time(NULL));
    // keep track of failure cases for final report
    int fail = 0; 
    int fail_non_zero = 0;
    int fail_trashed = 0;
    int fail_drawn = 0;
    int fail_coins = 0; 
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
    int ret;

    // variables to store pre card effect state 
    int hand_count_pre;
    int deck_count_pre;
    int discard_count_pre;
    int played_count_pre; 
    int total_pre;
    int coins_pre; 

    // execute random testing
    int i = NUM_TESTS; 
    while(i > 0){
        // generate game state and store variables of interest
        generate_random_gamestate(0, &G);
        hand_count_pre = G.handCount[0];
        deck_count_pre = G.deckCount[0];
        discard_count_pre = G.discardCount[0];
        played_count_pre = G.playedCardCount;
        total_pre = G.handCount[0] + G.deckCount[0] + G.discardCount[0] + G.playedCardCount;
        coins_pre = G.coins;
        
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
        // generate a random choice (+2 treasure, draw 2, trash 2)
        choice1 = rand_between(0,2);
        // if choice is 0 the player wants to trash two cards, must be careful in how those are randomly chosen
        if (choice1 == 0){
            // there are enough cards in hand to trash two, pick two disticnt onces to trash
            if (G.handCount[0] > 3){
                choice2 = rand_between(1,G.handCount[0] - 1);
                choice3 = rand_between(1,G.handCount[0] - 1);
                while (choice3 == choice2){
                    // printf("Here\n");
                    choice3 = rand_between(1,G.handCount[0] - 1);
                }
            }
            // there are exactly enough to trash two, in pos 1 and 2, nothing random here. 
            if (G.handCount[0] == 3){
                choice2 = 1;
                choice3 = 2;
            }
            // there is only one card to trash (not including steward)
            if (G.handCount[0] == 2){
                choice1 = 1;
                choice2 = 1;
            }
            // there is only the steward card
            if (G.handCount[0] == 1){
                choice1 = 0;
                choice2 = 0;
            }
        // if choice1 is not 0 these are arbitrary, assign random
        } else{
            choice2 = rand_between(-500,500);
            choice3 = rand_between(-500,500);         
        }
        // assign a random bonus and call cardeffect with stward
        handPos = 0;
        bonus = rand_between(-500,500);
        ret = cardEffect(steward, choice1,choice2,choice3,&G,0,bonus);
        
#if (DEBUG == 1)
        printf("choice1: %d\n",choice1);
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
        // check that cardeffect returns 0
        if (ret != 0){
            fail++;
            fail_non_zero++;
#if (DEBUG == 1)
            printf("FAIL: non zero return value for card effect");
#endif
        }
        // case where two cards are trashed, if possible, check that correct number of cards have left the nand. 
        if (choice1 == 0){
            possible = hand_count_pre;
            if (possible >= 3){
                if((hand_count_pre - 1) - G.handCount[0] != 2){
                    fail++;
                    fail_trashed++;
#if (DEBUG == 1)
                    printf("FAIL: two cards not trashed on choice 0: %d\n", hand_count_pre - (G.handCount[0] - 1));
#endif
                }
            }
            if (possible == 2){
                if((hand_count_pre - 1) - G.handCount[0] != 1){
                    fail++;
                    fail_trashed++;
#if (DEBUG == 1)
                    printf("FAIL: one card not trashed on choice 0 and 1 possible: %d\n", hand_count_pre - (G.handCount[0] - 1));
#endif
                }                
            }

        }
        // case where two cards are drawn, check that possible cards have been drawn
        if (choice1 == 1){
            possible = deck_count_pre + discard_count_pre;
            if (possible >= 2){
                if(G.handCount[0] - (hand_count_pre - 1) != 2){
                    fail++;
                    fail_drawn++;
#if (DEBUG == 1)
                    printf("FAIL: two cards not drawn on choice 1: %d\n", G.handCount[0] - hand_count_pre );
#endif
                }                
            } else{
                if(G.handCount[0] - (hand_count_pre - 1) != possible){
                    fail++;
                    fail_drawn++;
#if (DEBUG == 1)
                    printf("FAIL: %d cards not drawn on choice 1: %d\n",possible, G.handCount[0] - hand_count_pre );
#endif
                }    
            }


        }
        // case where want two more coins, check that the two coins are added to whatever the bonus and prevoius state was. 
        if (choice1 == 2){
            if((G.coins + bonus) - (coins_pre + bonus) != 2){
                fail++;
                fail_coins++;
#if (DEBUG == 1)
                printf("FAIL: two coins not added on choice 2: %d\n", (G.coins + bonus) - (coins_pre + bonus));
#endif
            }
        }

        i--;  
    }
    // print final test info. 
    if (fail == 0) {
        printf("%d Random Tests Pass.\n",NUM_TESTS);
    } else{
        printf("Total Tests: %d \n",NUM_TESTS);
        printf("Total test failures: %d\n", fail);
        printf("Non zero cardEffect return: %d\n", fail_non_zero);
        printf("Cards not trashed: %d \n", fail_trashed);
        printf("Cards not drawn: %d \n", fail_drawn);
        printf("Coins not awarded: %d \n", fail_coins);

    }

    return 0;
}
