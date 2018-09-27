#
# Eric Beets (beets) & Jack David (jackd)
#

CC=gcc
WFLAGS= -Wall -Wextra
EXE = 537ps

$(EXE): 537ps.o processPrinting.o
	$(CC) $(WFLAGS) -o $@ $^

537ps.o: 537ps.h 537ps.c
	$(CC) $(WFLAGS) -c $^

processPrinting.o: processPrinting.h processPrinting.c
	$(CC) $(WFLAGS) -c $^

clean:
	rm -f $(EXE) *.o

test:
	./$(EXE)
