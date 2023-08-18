CC = gcc
CFLAGS = -g -Wall -std=c90

poema: poema.o
	$(CC) poema.o -o poema

poema.o : poema.c 
	$(CC) $(CFLAGS) -c poema.c

clean :
	rm *.o poema

val:
	valgrind --leak-check=full -s ./poema