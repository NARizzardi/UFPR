#include "liballegro.h"

typedef struct jewel {
    int tipo;
    int ativo;
} jewel_t;

jewel_t** novo_jogo();

void troca_pecas();

void dropa_pecas();

int verifica_jogo();

void draw_grid(jewel_t** jogo, ALLEGRO_BITMAP* jewel1, ALLEGRO_BITMAP* jewel2, ALLEGRO_BITMAP* jewel3, ALLEGRO_BITMAP* jewel4);

void encerra_jogo();
