CC = gcc
CFLAGS = -g -Wall -std=c99
LDFLAGS = `pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5 --libs --cflags`

	objects = jeweled.o liballegro.o libjeweled.o

all: jeweled.o liballegro.o libjeweled.o
	$(CC) $(CFLAGS)  jeweled.o liballegro.o libjeweled.o -o jeweled $(LDFLAGS)

jeweled.o : jeweled.c 
	$(CC) $(CFLAGS) -c jeweled.c

liballegro.o : liballegro.c 
	$(CC) $(CFLAGS) -c liballegro.c

libjeweled.o : libjeweled.c 
	$(CC) $(CFLAGS) -c libjeweled.c

clean :
	-rm -f $(objects)

purge: 
	-rm -f $(objects) jeweled

