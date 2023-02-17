#include "liballegro.h"

typedef struct jewel {
    int tipo;
    int ativo;
} jewel_t;

jewel_t** novo_jogo();

int get_index(float pos, int direction);

int sao_vizinhos(int oldColumn, int oldRow, int newColumn, int newRow);

int troca_valida(jewel_t** jogo, int oldColumn, int oldRow, int newColumn, int newRow);

int troca_pecas(jewel_t** jogo, int oldColumn, int oldRow, int newColumn, int newRow);

int checa_mapa(jewel_t** jogo);

void atualiza_mapa(jewel_t** jogo);

int verifica_jogo();

void draw_grid(jewel_t** jogo, ALLEGRO_BITMAP* jewel1, ALLEGRO_BITMAP* jewel2, ALLEGRO_BITMAP* jewel3, ALLEGRO_BITMAP* jewel4, ALLEGRO_BITMAP* jewel5, ALLEGRO_BITMAP* jewel6);

void encerra_jeweled(jewel_t** jogo, int highscore, FILE *highscore_file, char* file_name);
