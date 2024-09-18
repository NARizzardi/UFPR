CC = gcc
CFLAGS = -g -Wall -no-pie
LFLAGS = -lm

	tolerance = 1e-15

	objects = pi.o floatType.o

all: pi.o floatType.o
	$(CC) $(CFLAGS) pi.o floatType.o -o pi $(LFLAGS) && make clean

pi.o: pi.c floatType.h
	$(CC) $(CFLAGS) -c pi.c $(LFLAGS)

floatType.o: floatType.c
	$(CC) $(CFLAGS) -c floatType.c $(LFLAGS)

run:
	./pi

clean:
	rm -f $(objects)

purge:
	rm -f pi $(objects)