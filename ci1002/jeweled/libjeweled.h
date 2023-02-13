#include "liballegro.h"

typedef struct jewel {
    int tipo;
    int score;
} jewel_t;

void novo_jogo();

void troca_pecas();

void dropa_pecas();

int verifica_jogo();

void encerra_jogo();