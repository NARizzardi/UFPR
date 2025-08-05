CC = gcc

CFLAGS = -Wall -g

all: escalona

escalona: escalona.o
	$(CC) $(CFLAGS) -o escalona escalona.o

escalona.o: escalona.c
	$(CC) $(CFLAGS) -c escalona.c -o escalona.o

clean:
	rm *.o

purge:
	rm escalona *.o
