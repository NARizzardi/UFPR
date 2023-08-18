CC = gcc
CFLAGS = -g -Wall -std=c90

programa: main.o libpilha.o
	$(CC) main.o libpilha.o -o programa 

main.o : main.c 
	$(CC) $(CFLAGS) -c main.c

libpilha.o : libpilha.c
	$(CC) $(CFLAGS) -c libpilha.c

clean :
	rm *.o programa

valg:
	valgrind --leak-check=full -s ./programa