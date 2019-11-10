CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c 
	gcc -o testme -g testme.c $(CFLAGS)

runtest: testme
	./testme
	gcov -b -f testme.c
	testme.c.gcov

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme testme.exe