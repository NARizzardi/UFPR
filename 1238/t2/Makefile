CFLAGS = -Wall -g

EXEC = elenco
OBJS = main.o bound-lib.o

all: $(EXEC)

$(EXEC): $(OBJS)
	gcc $(CFLAGS) -o $(EXEC) $(OBJS)

main.o: main.c bound-lib.h
	gcc $(CFLAGS) -c main.c

bound-lib.o: bound-lib.c bound-lib.h
	gcc $(CFLAGS) -c bound-lib.c

clean:
	rm -rf *.o $(EXEC)

debug: clean
	make CFLAGS="$(CFLAGS) -DDEBUG" all