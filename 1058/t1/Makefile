CC = gcc

CFLAGS = -Wextra -g

all: servidor cliente

servidor: objects/servidor.o objects/raw_socket.o objects/utils.o
	$(CC) $(CFLAGS) -o servidor objects/servidor.o objects/raw_socket.o objects/utils.o

cliente: objects/cliente.o objects/raw_socket.o objects/utils.o
	$(CC) $(CFLAGS) -o cliente objects/cliente.o objects/raw_socket.o objects/utils.o

objects/servidor.o: src/servidor.c include/servidor.h include/utils.h
	$(CC) $(CFLAGS) -c src/servidor.c -o objects/servidor.o

objects/cliente.o: src/cliente.c include/cliente.h include/utils.h
	$(CC) $(CFLAGS) -c src/cliente.c -o objects/cliente.o

objects/raw_socket.o: src/raw_socket.c include/raw_socket.h
	$(CC) $(CFLAGS) -c src/raw_socket.c -o objects/raw_socket.o

objects/utils.o: src/utils.c include/utils.h include/utils.h
	$(CC) $(CFLAGS) -c src/utils.c -o objects/utils.o

clean:
	rm objects/*.o

purge:
	rm servidor cliente objects/*.o