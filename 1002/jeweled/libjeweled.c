#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libjeweled.h"

int gera_doce(){
    return (rand() % 5)+ 1;
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
    int aux = jogo[oldColumn][oldRow].tipo;
    jogo[oldColumn][oldRow].tipo = jogo[newColumn][newRow].tipo;
    jogo[newColumn][newRow].tipo = aux;

    for(int i = 0 ; i < 8; i++){
        for(int j = 0 ; j < 8; j++){
            // checa linha e coluna
            if(i < 6 && j < 6){
                if((jogo[i][j].tipo == jogo[i+1][j].tipo && jogo[i][j].tipo == jogo[i+2][j].tipo) 
                || (jogo[i][j].tipo == jogo[i][j+1].tipo && jogo[i][j].tipo == jogo[i][j+2].tipo))
                    return 1;
            } else if(i < 6 && j >= 6){ //checa coluna
                if((jogo[i][j].tipo == jogo[i+1][j].tipo && jogo[i][j].tipo == jogo[i+2][j].tipo))
                    return 1;
            } else if(i >= 6 && j < 6){ //checa linha
                if(jogo[i][j].tipo == jogo[i][j+1].tipo && jogo[i][j].tipo == jogo[i][j+2].tipo)
                    return 1;
            }
        }
    }

    aux = jogo[oldColumn][oldRow].tipo;
    jogo[oldColumn][oldRow].tipo = jogo[newColumn][newRow].tipo;
    jogo[newColumn][newRow].tipo = aux;
    return 0;
}

int troca_pecas(jewel_t** jogo, int oldColumn, int oldRow, int newColumn, int newRow){
    int pontos = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(i<= 5 && j <= 5){
                //checa coluna
                if(jogo[i][j].tipo == jogo[i][j+1].tipo && jogo[i][j].tipo == jogo[i][j+2].tipo){
                    jogo[i][j].ativo = 0;
                    jogo[i][j+1].ativo = 0;
                    jogo[i][j+2].ativo = 0;
                    int coluna = j+3;
                    pontos += 10;
                    while(coluna < 8 && jogo[i][coluna].tipo == jogo[i][coluna-1].tipo){
                        pontos += 10;
                        jogo[i][coluna].ativo = 0;
                        coluna++;
                    }
                }
                //checa linha
                if(jogo[i][j].tipo == jogo[i+1][j].tipo && jogo[i][j].tipo == jogo[i+2][j].tipo){
                    jogo[i][j].ativo = 0;
                    jogo[i+1][j].ativo = 0;
                    jogo[i+2][j].ativo = 0;
                    int linha = i+3;
                    pontos += 10;
                    while(linha < 8 && jogo[linha][j].tipo == jogo[linha-1][j].tipo){
                        pontos += 10;
                        jogo[linha][j].ativo = 0;
                        linha++;
                    }
                }
            }
            if(i > 5 && j <= 5){
                //checa coluna
                if(jogo[i][j].tipo == jogo[i][j+1].tipo && jogo[i][j].tipo == jogo[i][j+2].tipo){
                    jogo[i][j].ativo = 0;
                    jogo[i][j+1].ativo = 0;
                    jogo[i][j+2].ativo = 0;
                    int coluna = j+3;
                    pontos += 10;
                    while(coluna < 8 && jogo[i][coluna].tipo == jogo[i][coluna-1].tipo){
                        pontos += 10;
                        jogo[i][coluna].ativo = 0;
                        coluna++;
                    }
                }
            }

            if(i <= 5 && j > 5){
                //checa linha
                if(jogo[i][j].tipo == jogo[i+1][j].tipo && jogo[i][j].tipo == jogo[i+2][j].tipo){
                    jogo[i][j].ativo = 0;
                    jogo[i+1][j].ativo = 0;
                    jogo[i+2][j].ativo = 0;
                    int linha = i+3;
                    pontos += 10;
                    while(linha < 8 && jogo[linha][j].tipo == jogo[linha-1][j].tipo){
                        pontos += 10;
                        jogo[linha][j].ativo = 0;
                        linha++;
                    }
                }
            }
        }
    }
    return pontos;
}

int get_index(float pos, int direction){
    int index = 0;
    if(direction == 0){ // linha
        if(pos >= 130 && pos < 194)
            return 0;
        else if (pos >= 201 && pos <= 265)
            return 1;
        else if (pos >= 270 && pos <= 334)
            return 2;
        else if (pos >= 341 && pos <= 405)
            return 3;
        else if (pos >= 410 && pos <= 474)
            return 4;
        else if (pos >= 484 && pos <= 548)
            return 5;
        else if (pos >= 551 && pos <= 615)
            return 6;
        else if (pos >= 620 && pos <= 684)
            return 7;
    }
    else { // coluna
        if(pos >= 61 && pos < 125)
            return 0;
        else if (pos >= 132 && pos <= 196)
            return 1;
        else if (pos >= 202 && pos <= 266)
            return 2;
        else if (pos >= 272 && pos <= 336)
            return 3;
        else if (pos >= 342 && pos <= 406)
            return 4;
        else if (pos >= 412 && pos <= 476)
            return 5;
        else if (pos >= 482 && pos <= 546)
            return 6;
        else if (pos >= 552 && pos <= 616)
            return 7;
    }

    return index;
}

void draw_grid(jewel_t** jogo, ALLEGRO_BITMAP* jewel1, ALLEGRO_BITMAP* jewel2, ALLEGRO_BITMAP* jewel3, ALLEGRO_BITMAP* jewel4, ALLEGRO_BITMAP* jewel5, ALLEGRO_BITMAP* jewel6){
    int i, j;
    int linha = 0;
    for(i = 130; i <= 630; i += 70){
    int coluna = 0;
        for(j = 60; j <= 560; j += 70){
            if(jogo[linha][coluna].ativo == 1)
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
                case 5:
                    draw_jewel(jewel5, i, j, 0);
                    break;
            }

            //al_draw_filled_rectangle(i, j, i+60, j+60, al_map_rgba_f(r, g , 0.5, 0.5));
            coluna++;
        }
        linha++;
    }
}

int checa_mapa(jewel_t** jogo){
     for(int i = 0 ; i < 8; i++){
        for(int j = 0 ; j < 8; j++){
            // checa linha e coluna
            if(i < 6 && j < 6){
                if((jogo[i][j].tipo == jogo[i+1][j].tipo && jogo[i][j].tipo == jogo[i+2][j].tipo) 
                || (jogo[i][j].tipo == jogo[i][j+1].tipo && jogo[i][j].tipo == jogo[i][j+2].tipo))
                    return 1;
            } else if(i < 6 && j >= 6){ //checa coluna
                if((jogo[i][j].tipo == jogo[i+1][j].tipo && jogo[i][j].tipo == jogo[i+2][j].tipo))
                    return 1;
            } else if(i >= 6 && j < 6){ //checa linha
                if(jogo[i][j].tipo == jogo[i][j+1].tipo && jogo[i][j].tipo == jogo[i][j+2].tipo)
                    return 1;
            }
        }
    }
    return 0;
}

void atualiza_mapa(jewel_t** jogo){
    //desce as joias pro local correto
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            int coluna = i;
            if(jogo[j][i].ativo == 0){
                while(jogo[j][coluna].ativo == 0 && coluna >= 0){
                    coluna--;
                }
                if(coluna < 0){
                    jogo[j][i].ativo = -1;
                }else{
                    jewel_t *joia = (jewel_t* )malloc(sizeof(jewel_t));
                    *joia = jogo[j][i];
                    jogo[j][i] = jogo[j][coluna];
                    jogo[j][coluna] = *joia;
                }
            }
        }
    }

    int doce;
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            if(jogo[j][i].ativo == -1){
                jogo[j][i].ativo = 1;
                doce = gera_doce();
                while(doce_valido(jogo, i, j, doce) == 0){
                    doce = gera_doce();
                }
                jogo[j][i].tipo = doce;
            }
        }
    }
}

void encerra_jeweled(jewel_t** jogo, int highscore, FILE* highscore_file, char* file_name){
    for(int i = 0; i < 8; i++){
        free(jogo[i]);
    }
        free(jogo);
    highscore_file = freopen(file_name, "w", highscore_file);
    char highscore_string[20];
    sprintf(highscore_string, "%d", highscore);
    fputs(highscore_string, highscore_file);
    fclose(highscore_file);

}