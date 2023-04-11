CC = gcc
CFLAGS = -g -Wall -ansi

forca: forca.o
	$(CC) forca.o -o forca

forca.o : forca.c 
	$(CC) $(CFLAGS) -c forca.c

clean :
	rm *.o forca

val:
	valgrind --leak-check=full -s ./forca palavras.txt