#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libjeweled.h"

void novo_jogo(){
    
}

void draw_grid(ALLEGRO_BITMAP* jewel1, ALLEGRO_BITMAP* jewel2, ALLEGRO_BITMAP* jewel3, ALLEGRO_BITMAP* jewel4){
    int i, j;
    int r = 0;

    for(i = 60; i <= 560; i += 70){
    int g = 0;
        for(j = 60; j <= 560; j += 70){
            switch (rand() % 4 + 1){
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
            g++;
        }
        r++;

    }
}

void encerra_jogo();