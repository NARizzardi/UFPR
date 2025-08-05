CC = gcc
CFLAGS = -Wall -g -std=c99

carga: carga.o
	$(CC) $(CFLAGS) -o carga carga.o

carga.o: carga.c
	$(CC) $(CFLAGS) -c carga.c -o carga.o

clean:
	rm *.o

purge:
	rm carga *.o
