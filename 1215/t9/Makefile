CC = gcc
CFLAGS = -Wall -g


ppos: main.o queue.o ppos_core.o
	$(CC) $(CFLAGS) -o ppos main.o queue.o ppos_core.o

main.o: main.c queue.c
	$(CC) $(CFLAGS) -c main.c -o main.o

ppos_core.o: ppos_core.c
	$(CC) $(CFLAGS) -c ppos_core.c -o ppos_core.o

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c -o queue.o	

clean:
	rm *.o

purge:
	rm ppos *.o
