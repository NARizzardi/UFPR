CC = gcc
CFLAGS = -g -Wall -std=c90

testa_fila: testa_fila.o libfila.o
	$(CC) testa_fila.o libfila.o -o testa_fila 

testa_fila.o : testa_fila.c 
	$(CC) $(CFLAGS) -c testa_fila.c

libfila.o : libfila.c
	$(CC) $(CFLAGS) -c libfila.c

#testa_lista: testa_lista.o liblista.o
#	$(CC) testa_lista.o liblista.o -o testa_lista 

#testa_lista.o : testa_lista.c 
#	$(CC) $(CFLAGS) -c testa_lista.c

#liblista.o : liblista.c
#	$(CC) $(CFLAGS) -c liblista.c

#testa_pilha: testa_pilha.o libpilha.o
#	$(CC) testa_pilha.o libpilha.o -o testa_pilha 

#testa_pilha.o : testa_pilha.c 
#	$(CC) $(CFLAGS) -c testa_pilha.c

#libpilha.o : libpilha.c
#	$(CC) $(CFLAGS) -c libpilha.c

clean :
	rm *.o testa_fila

valg:
	valgrind --leak-check=full -s ./testa_pilha
