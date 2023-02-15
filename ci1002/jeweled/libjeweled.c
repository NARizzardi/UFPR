#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libjeweled.h"

int gera_doce(){
    return (rand() % 4)+ 1;
}

int doce_valido(jewel_t** matriz, int x, int y, int doce){
    if(x < 2 && y < 2) // os primeiros dois de linha e coluna
        return 1;
    if(x >= 2 && y < 2)
        if(matriz[x-2][y].tipo == doce && matriz[x-1][y].tipo == doce)
            return 0;
    if(x < 2 && y >= 2)
        if(matriz[x][y-2].tipo == doce && matriz[x][y-1].tipo == doce)
            return 0;
    if(x >= 2 && y >= 2)
        if((matriz[x][y-2].tipo == doce && matriz[x][y-1].tipo == doce) || (matriz[x-2][y].tipo == doce && matriz[x-1][y].tipo == doce))
            return 0;

    return 1;
    
}

jewel_t** novo_jogo(){
    jewel_t** matriz_joia = (jewel_t **)malloc(8 * sizeof(jewel_t*));
    int doce;
    for(int i = 0; i < 8; i++){
        matriz_joia[i] = (jewel_t *)malloc(8 * sizeof(jewel_t));
    }
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                doce = gera_doce();
                matriz_joia[i][j].ativo = 1;
                while(doce_valido(matriz_joia, i, j, doce) == 0){
                    doce = gera_doce();
                }
                matriz_joia[i][j].tipo = doce;
            }
        }
        return matriz_joia;

}

int sao_vizinhos(int oldColumn, int oldRow, int newColumn, int newRow){
    int columnDiff = newColumn - oldColumn;
    int rowDiff = newRow - oldRow;
    if(((columnDiff == 1 || columnDiff == -1) && rowDiff == 0) ||
        ((rowDiff == 1 || rowDiff == -1) && columnDiff == 0))
            return 1;
    return 0;
}

int troca_valida(jewel_t** jogo, int oldColumn, int oldRow, int newColumn, int newRow){
    
}

int troca_pecas(jewel_t** jogo, int oldColumn, int oldRow, int newColumn, int newRow){

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