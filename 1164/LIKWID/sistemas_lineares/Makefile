# PROGRAMA
    PROG = perfSL

# Compilador
    CC     = gcc
    CFLAGS = -O0 -Wall
    LFLAGS = -lm

# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

all: perSL.o utils.o
	$(CC) $(CFLAGS) perSL.o utils.o -o $(PROG) $(LFLAGS)

perSL.o: perSL.c utils.h
	$(CC) $(CFLAGS) -c perSL.c $(LFLAGS)

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c $(LFLAGS)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
