# Benjamin Chang
# bchang26

# Flags for the compiler
CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g

# Links files needed to create the executable
word_search: search_functions.o word_search.o
	$(CC) $(CFLAGS) -o word_search search_functions.o word_search.o

# Links files needed to create the test executable
test: test_search_functions.o search_functions.o
	$(CC) $(CFLAGS) -o test test_search_functions.o search_functions.o

# Compiles word_search.c to create word_search.o
word_search.o: word_search.c search_functions.h
	$(CC) $(CFLAGS) -c word_search.c

# Compiles search_functions.c to create search_functions.o
search_functions.o: search_functions.c search_functions.h
	$(CC) $(CFLAGS) -c search_functions.c

# Compiles test_search_functions.c to create test_search_functions.o
test_search_functions.o: test_search_functions.c search_functions.h
	$(CC) $(CFLAGS) -c test_search_functions.c

# Removes all object files and the executable named main
clean:
	rm -f *.o test word_search 
