CC = gcc
CFLAGS = -g -Wall -std=c90

programa: main.o pilha.o
	$(CC) main.o pilha.o -o programa 

main.o : main.c 
	$(CC) $(CFLAGS) -c main.c

pilha.o : pilha.c
	$(CC) $(CFLAGS) -c pilha.c

clean :
	rm *.o programa

valg:
	valgrind --leak-check=full ./programa