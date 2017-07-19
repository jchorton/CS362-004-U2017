CFLAGS = -Wall -O0 -ftest-coverage -fprofile-arcs

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)
	./testme

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme
