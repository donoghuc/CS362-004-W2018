CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o interface.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o interface.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o interface.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o interface.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o interface.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o interface.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o interface.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o interface.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o interface.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o interface.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o interface.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 
	echo "====================================" > unittestresults.out
	echo "Running Unit Tests for Assignment-3:" >> unittestresults.out
	echo "====================================" >> unittestresults.out
	echo "unittest1.c: shuffle unit test." >> unittestresults.out
	echo "====================================" >> unittestresults.out
	./unittest1 >> unittestresults.out
	echo "====================================" >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo "shuffle stats" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/shuffle/{n;p; n;p; n;p; n;p}' >> unittestresults.out
	echo "====================================" >> unittestresults.out
	echo "unittest2.c: buyCard unit test." >> unittestresults.out
	echo "====================================" >> unittestresults.out
	./unittest2 >> unittestresults.out
	echo "====================================" >> unittestresults.out
	gcov -b -c  dominion.c >> unittestresults.out
	echo "buyCard stats" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/buyCard/{n;p; n;p; n;p; n;p}' >> unittestresults.out
	echo "====================================" >> unittestresults.out
	echo "unittest3.c: updateCoins unit test." >> unittestresults.out
	echo "====================================" >> unittestresults.out
	./unittest3 >> unittestresults.out
	echo "====================================" >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo "updateCoins stats" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/updateCoins/{n;p; n;p; n;p; n;p}' >> unittestresults.out
	echo "====================================" >> unittestresults.out
	echo "unittest4.c: endTurn unit test." >> unittestresults.out
	echo "====================================" >> unittestresults.out
	./unittest4 >> unittestresults.out
	echo "====================================" >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo "endTurn stats" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/endTurn/{n;p; n;p; n;p; n;p}' >> unittestresults.out
	echo "====================================" >> unittestresults.out
	echo "cardtest1.c: smitthy unit test." >> unittestresults.out
	echo "====================================" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	echo "====================================" >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo "====================================" >> unittestresults.out
	echo "cardtest2.c: adventurer unit test." >> unittestresults.out
	echo "====================================" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	echo "====================================" >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo "====================================" >> unittestresults.out
	echo "cardtest3.c: council_room unit test." >> unittestresults.out
	echo "====================================" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	echo "====================================" >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo "====================================" >> unittestresults.out
	echo "cardtest4.c: great_hall unit test." >> unittestresults.out
	./cardtest4 >> unittestresults.out
	echo "====================================" >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo "====================================" >> unittestresults.out
	cat unittestresults.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o interface.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard1.out: randomtestcard1
	rm -f dominion.c.gcov
	echo "====================================" > randomtestcard1.out
	echo "Running Random Test for Smithy:" >> randomtestcard1.out
	echo "====================================" >> randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	echo "====================================" >> randomtestcard1.out
	gcov -b -c dominion.c >> randomtestcard1.out
	echo "====================================" >> randomtestcard1.out
	echo "Coverage Look" >> randomtestcard1.out
	echo "====================================" >> randomtestcard1.out
	sed -n '953,970p' dominion.c.gcov >> randomtestcard1.out
	echo "====================================" >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.o rngs.o interface.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o interface.o $(CFLAGS)


randomtestcard2.out: randomtestcard2
	rm -f dominion.c.gcov
	echo "====================================" > randomtestcard2.out
	echo "Running Random Test for Steward:" >> randomtestcard2.out
	echo "====================================" >> randomtestcard2.out
	./randomtestcard2 >> randomtestcard2.out
	echo "====================================" >> randomtestcard2.out
	gcov -b -c dominion.c >> randomtestcard2.out
	echo "====================================" >> randomtestcard2.out
	echo "Coverage Look" >> randomtestcard2.out
	echo "====================================" >> randomtestcard2.out
	sed -n '1424,1454p' dominion.c.gcov >> randomtestcard2.out
	echo "====================================" >> randomtestcard2.out

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o interface.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	rm -f dominion.c.gcov
	echo "====================================" > randomtestadventurer.out
	echo "Running Random Test for Adventurer:" >> randomtestadventurer.out
	echo "====================================" >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	echo "====================================" >> randomtestadventurer.out
	gcov -b -c dominion.c >> randomtestadventurer.out
	echo "====================================" >> randomtestadventurer.out
	echo "Coverage Look" >> randomtestadventurer.out
	echo "====================================" >> randomtestadventurer.out
	sed -n '905,950p' dominion.c.gcov >> randomtestadventurer.out
	echo "====================================" >> randomtestadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out \
	randomtestcard1 randomtestcard2 randomtestadventurer

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov \
	*.gcda *.gcno *.so *.out  testDrawCard testDrawCard.exe \
	badTestDrawCard unittest1 unittest2 unittest3 unittest4 cardtest1 \
	cardtest2 cardtest3 cardtest4 unittestresults.out randomtestadventurer \
	randomtestcard2 randomtestcard1
