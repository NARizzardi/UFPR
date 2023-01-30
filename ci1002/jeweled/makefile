CC = gcc
CFLAGS = -g -Wall -std=c99
LDFLAGS = `pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5 --libs --cflags`

	objects = hello.o

all: hello.o
	$(CC) $(CFLAGS)  hello.o -o hello $(LDFLAGS)

hello.o : hello.c 
	$(CC) $(CFLAGS) -c hello.c

clean :
	-rm -f $(objects)

purge: 
	-rm -f $(objects) hello

