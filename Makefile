#
# Eric Beets (beets) & Jack David (jackd)
#

CC=gcc
FLAGS= -Wall
OUTPUT = 537ps

$(OUTPUT): 537ps.o
	$(CC) $(FLAGS) -o $@ $^

537ps.o: 537ps.h 537ps.c
	$(CC) $(FLAGS) -c $^

clean:
	rm -f $(OUTPUT) *.o

test:
	./$(OUTPUT)
