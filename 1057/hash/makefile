CC = gcc
CFLAGS = -g -Wall -std=c90

myht: hash.o hashfunctions.o 
	$(CC) hash.o hashfunctions.o -o myht -lm

hashfunctions.o : hashfunctions.c 
	$(CC) $(CFLAGS) -c hashfunctions.c

hash.o : hash.c 
	$(CC) $(CFLAGS) -c hash.c

clean :
	rm *.o myht

valg:
	valgrind --leak-check=full -s ./myht
