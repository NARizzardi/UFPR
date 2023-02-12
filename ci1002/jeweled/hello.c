#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "liballegro.h"
#include "libjeweled.h"

#define KEY_SEEN     1
#define KEY_RELEASED 2
#define FPS 60
#define SCREEN_W 1080
#define SCREEN_H 640

typedef struct game {
    int mapa[8][8];
    int score;
} game_t;

game_t *novo_jogo(){
    game_t *jogo;
    jogo = (game_t *) malloc(sizeof(game_t));
    jogo->score = 0;
    
    srand(clock());
    int i, j;
    for(i = 7; i >= 0; i--){
        for(j = 7; j >= 0; j--){
            jogo->mapa[i][j] = (rand() % 4) + 1;
            printf("| %d | - ", jogo->mapa[i][j]);
        }
        printf("\n");
    }

    return jogo;
}

void draw_grid(game_t* jogo, ALLEGRO_BITMAP* jewel1, ALLEGRO_BITMAP* jewel2, ALLEGRO_BITMAP* jewel3, ALLEGRO_BITMAP* jewel4){
    int i, j;
    int r = 0;
    for(i = 60; i <= 560; i += 70){
    int g = 0;
        for(j = 60; j <= 560; j += 70){
            switch (jogo->mapa[r][g]){
                case 1:
                    al_draw_bitmap(jewel1, i, j, 0);
                    break;
                case 2:
                    al_draw_bitmap(jewel2, i, j, 0);
                    break;
                case 3:
                    al_draw_bitmap(jewel3, i, j, 0);
                    break;
                case 4:
                    al_draw_bitmap(jewel4, i, j, 0);
                    break;
            }
            //al_draw_filled_rectangle(i, j, i+60, j+60, al_map_rgba_f(r, g , 0.5, 0.5));
            g++;
        }
        r++;
        
    }
}


int main()
{

    game_t *jogo;
    jogo = novo_jogo();

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    char egg[5];
    start_allegro();
    
    ALLEGRO_BITMAP* jewel1 = al_load_bitmap("./resources/jewel1.png");
    ALLEGRO_BITMAP* jewel2 = al_load_bitmap("./resources/jewel2.png");
    ALLEGRO_BITMAP* jewel3 = al_load_bitmap("./resources/jewel3.png");
    ALLEGRO_BITMAP* jewel4 = al_load_bitmap("./resources/jewel4.png");
    ALLEGRO_BITMAP* background = al_load_bitmap("./resources/background.bmp");
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_display();

    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    
    al_set_registers(queue, disp, timer);   

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    float x, y;
    x = 100;
    y = 100;
    int help = -1;
    al_hide_mouse_cursor(disp);
    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                x = event.mouse.x;
                y = event.mouse.y;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			    printf("\nclicou em (%d, %d)", event.mouse.x, event.mouse.y);
                break;
		    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			    printf("\nsoltou em (%d, %d)", event.mouse.x, event.mouse.y);
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_F1)
                    help *= -1;
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_grid(jogo, jewel1, jewel2, jewel3, jewel4);
            al_draw_line(720, 0, 720, 640, al_map_rgb_f(1, 0, 0), 1);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 100, -1, "%d",help);
            al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}