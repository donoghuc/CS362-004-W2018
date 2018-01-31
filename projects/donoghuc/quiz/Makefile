CFLAGS = -Wall -fpic -coverage -lm

build_testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

run_testme: testme
	./testme
	
test_cov: testme
	gcov testme.c 
	cat testme.c.gcov

clean:
	rm -f testme testme.gcda testme.gcno testme.c.gcov
