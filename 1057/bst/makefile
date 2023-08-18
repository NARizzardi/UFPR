CC = gcc
CFLAGS = -g -Wall -std=c90

programa: main.o bst.o
	$(CC) main.o bst.o -o programa 

main.o : main.c 
	$(CC) $(CFLAGS) -c main.c

bst.o : bst.c
	$(CC) $(CFLAGS) -c bst.c

clean :
	rm *.o programa

valg:
	valgrind --leak-check=full ./programa