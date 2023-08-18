CC = gcc
CFLAGS = -std=c99 -Wall 

all: lattes

lattes: main.o lib_lattes.o
        $(CC) main.o lib_lattes.o -o lattes

main.o : main.c
        $(CC) $(CFLAGS) -c main.c

lib_lattes.o : lib_lattes.c
        $(CC) $(CFLAGS) -c lib_lattes.c

clean :
        rm *.o lattes

val:
        valgrind --leak-check=full -s ./lattes