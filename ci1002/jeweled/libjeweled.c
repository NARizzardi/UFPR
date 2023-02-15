#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libjeweled.h"

int gera_doce(){
    return (rand() % 4)+ 1;
}

jewel_t** novo_jogo(){
    jewel_t** matriz_joia = (jewel_t **)malloc(9 * sizeof(jewel_t*));
    for(int i = 0; i < 9; i++){
        matriz_joia[i] = (jewel_t *)malloc(9 * sizeof(jewel_t));
    }
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                matriz_joia[i][j].ativo = 1;
                matriz_joia[i][j].tipo = gera_doce();
            }
        }
        return matriz_joia;

}


void draw_grid(jewel_t** jogo, ALLEGRO_BITMAP* jewel1, ALLEGRO_BITMAP* jewel2, ALLEGRO_BITMAP* jewel3, ALLEGRO_BITMAP* jewel4){
    int i, j;
    int linha = 0;
    for(i = 130; i <= 630; i += 70){
    int coluna = 0;
        for(j = 60; j <= 560; j += 70){
            switch (jogo[linha][coluna].tipo){
                case 1:
                    draw_jewel(jewel1, i, j, 0);
                    break;
                case 2:
                    draw_jewel(jewel2, i, j, 0);
                    break;
                case 3:
                    draw_jewel(jewel3, i, j, 0);
                    break;
                case 4:
                    draw_jewel(jewel4, i, j, 0);
                    break;
            }
            //al_draw_filled_rectangle(i, j, i+60, j+60, al_map_rgba_f(r, g , 0.5, 0.5));
            coluna++;
        }
        linha++;

    }
}

void encerra_jogo();