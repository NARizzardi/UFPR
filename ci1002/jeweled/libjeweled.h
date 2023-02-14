#include "liballegro.h"

typedef struct jewel {
    int tipo;
    int score;
} jewel_t;

void novo_jogo();

void troca_pecas();

void dropa_pecas();

int verifica_jogo();

void draw_grid(ALLEGRO_BITMAP* jewel1, ALLEGRO_BITMAP* jewel2, ALLEGRO_BITMAP* jewel3, ALLEGRO_BITMAP* jewel4);

void encerra_jogo();
