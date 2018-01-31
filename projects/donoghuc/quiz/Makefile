CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)
	./testme
	
all:
	testme

clean:
	rm -f testme
