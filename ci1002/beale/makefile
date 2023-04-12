CC = gcc
CFLAGS = -g -Wall -std=c99

	objects = beale.o bealeFunctions.o codify.o decodify.o keyfile.o

all: beale.o bealeFunctions.o codify.o decodify.o keyfile.o
	$(CC) $(CFLAGS)  beale.o bealeFunctions.o codify.o decodify.o keyfile.o -o beale

beale.o : beale.c 
	$(CC) $(CFLAGS) -c beale.c

bealeFunctions.o : bealeFunctions.c 
	$(CC) $(CFLAGS) -c bealeFunctions.c

codify.o : codify.c 
	$(CC) $(CFLAGS) -c codify.c

decodify.o : decodify.c 
	$(CC) $(CFLAGS) -c decodify.c

keyfile.o : keyfile.c 
	$(CC) $(CFLAGS) -c keyfile.c

clean :
	-rm -f $(objects)

purge: 
	-rm -f $(objects) beale
