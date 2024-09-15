CC = gcc
CFLAGS = -g -Wall -no-pie
LFLAGS = -lm

	tolerance = 1e-15

	objects = pi.o floatType.o

all: pi.o floatType.o
	$(CC) $(CFLAGS) $(LFLAGS) pi.o floatType.o -o pi

pi.o: pi.c floatType.h
	$(CC) $(CFLAGS) $(LFLAGS) -c pi.c

floatType.o: floatType.c
	$(CC) $(CFLAGS) $(LFLAGS) -c floatType.c

run:
	./pi $(tolerance)

clean:
	rm -f $(objects)

purge:
	rm -f pi $(objects)