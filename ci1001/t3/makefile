CC = gcc
CFLAGS = -g -Wall -std=c90

ru_na_pandemia: libfila.o liblista.o libpilha.o libru.o ru_na_pandemia.o
	$(CC) $(CFLAGS) libfila.o liblista.o libpilha.o libru.o ru_na_pandemia.o -o ru_na_pandemia

libfila.o : libfila.c
	$(CC) $(CFLAGS) -c libfila.c

liblista.o : liblista.c
	$(CC) $(CFLAGS) -c liblista.c

libpilha.o : libpilha.c
	$(CC) $(CFLAGS) -c libpilha.c

libru.o : libru.c
	$(CC) $(CFLAGS) -c libru.c

ru_na_pandemia.o: ru_na_pandemia.c
	$(CC) $(CFLAGS) -c ru_na_pandemia.c

clean :
	rm *.o ru_na_pandemia

valg:
	valgrind --leak-check=full -s ./ru_na_pandemia

