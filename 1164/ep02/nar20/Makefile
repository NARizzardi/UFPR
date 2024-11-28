# Nicolas Andre Rizzardi GRR20206152
# PROGRAMA
    PROG = inversa
    OBJS = inversa.o inversa_functions.o utils.o

# Compilador
    CC = gcc

# Acrescentar onde apropriado as opções para incluir uso da biblioteca LIKWID
    CFLAGS = -O0 -Wall -DLIKWID_PERFMON -I${LIKWID_INCLUDE}
    LFLAGS = -lm -L${LIKWID_LIB} -llikwid

# Lista de arquivos para distribuição. Acrescentar mais arquivos se necessário.
DISTFILES = *.sh *.c *.h LEIAME* Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

all: $(PROG) 

inversa: inversa.o inversa_functions.o utils.o 
	$(CC) inversa.o inversa_functions.o utils.o -o inversa -L${LIKWID_LIB} -llikwid $(LFLAGS)

inversa.o: inversa.c
	$(CC) $(CFLAGS) -c inversa.c

inversa_functions.o: inversa_functions.c
	$(CC) $(CFLAGS) -c inversa_functions.c

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) $(OBJS) core a.out $(DISTDIR) $(DISTDIR).tgz

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
