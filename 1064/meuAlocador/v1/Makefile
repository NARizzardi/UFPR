CC = gcc
CFLAGS = -g -Wall
LDFLAGS = `--libs --cflags`

	objects = main.o alocador.o

all: main.o alocador.o
	$(CC) $(CFLAGS)  main.o alocador.o -o alocador $(LDFLAGS) && rm $(objects)

main.o : main.c 
	$(CC) $(CFLAGS) -c main.c

alocador.o : alocador.c 
	$(CC) $(CFLAGS) -c alocador.c

clean :
	-rm -f $(objects)

purge: 
	-rm -f $(objects) alocador

