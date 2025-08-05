#include "utils.h"
#include "raw_socket.h"
#include <limits.h>
#include <sys/statvfs.h>


struct tesouro{
    char nome[64];
    unsigned int tamanho;
    unsigned int tipo;
    char coordenadaX;
    char coordenadaY;
    char conteudo;
    short int coletado;
}; 
typedef struct tesouro tesouro_t;

struct mapa {
    int posJogadorX;
    int posJogadorY;
    short int tesourosColetados;
    tesouro_t tesouros[8];
};
typedef struct mapa mapa_t;