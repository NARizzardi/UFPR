CC = gcc
CFLAGS = -Wextra -g -std=c99


scheduler: scheduler.o queue.o ppos_core.o
	$(CC) $(CFLAGS) -o scheduler scheduler.o queue.o ppos_core.o

schedulerdebug: scheduler.o queue.o db_ppos_core.o
	$(CC) $(CFLAGS) -o scheduler scheduler.o queue.o db_ppos_core.o

scheduler.o: scheduler.c queue.c
	$(CC) $(CFLAGS) -c scheduler.c -o scheduler.o

dispatcher: dispatcher.o queue.o ppos_core.o
	$(CC) $(CFLAGS) -o dispatcher dispatcher.o queue.o ppos_core.o

dispatcherdebug: dispatcher.o queue.o db_ppos_core.o
	$(CC) $(CFLAGS) -o dispatcher dispatcher.o queue.o db_ppos_core.o

dispatcher.o: dispatcher.c queue.h
	$(CC) $(CFLAGS) -c dispatcher.c -o dispatcher.o

1: teste1.o queue.o ppos_core.o
	$(CC) $(CFLAGS) -o teste teste1.o queue.o ppos_core.o

2: teste2.o queue.o ppos_core.o
	$(CC) $(CFLAGS) -o teste teste2.o queue.o ppos_core.o

3: teste3.o queue.o ppos_core.o
	$(CC) $(CFLAGS) -o teste teste3.o queue.o ppos_core.o

debug1: teste1.o queue.o db_ppos_core.o
	$(CC) $(CFLAGS) -o teste teste1.o queue.o ppos_core.o

debug2: teste2.o queue.o db_ppos_core.o
	$(CC) $(CFLAGS) -o teste teste2.o queue.o ppos_core.o

debug3: teste3.o queue.o db_ppos_core.o
	$(CC) $(CFLAGS) -o teste teste3.o queue.o ppos_core.o

teste1.o: teste1.c
	$(CC) $(CFLAGS) -c teste1.c -o teste1.o

teste2.o: teste2.c
	$(CC) $(CFLAGS) -c teste2.c -o teste2.o

teste3.o: teste3.c
	$(CC) $(CFLAGS) -c teste3.c -o teste3.o

ppos_core.o: ppos_core.c
	$(CC) $(CFLAGS) -c ppos_core.c -o ppos_core.o

db_ppos_core.o: ppos_core.c
	$(CC) $(CFLAGS) -DDEBUG -c ppos_core.c -o ppos_core.o

testafila: testafila.o queue.o
	$(CC) $(CFLAGS) -o testafila testafila.o queue.o

testafila.o: testafila.c queue.h
	$(CC) $(CFLAGS) -c testafila.c -o testafila.o	

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c -o queue.o	

clean:
	rm *.o

purge:
	rm teste *.o
