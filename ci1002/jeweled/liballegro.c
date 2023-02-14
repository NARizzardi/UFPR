#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void start_allegro(){
    must_init(al_init(), "allegro");
    must_init(al_init_image_addon(), "image");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_primitives_addon(), "primitives");
}

void al_set_display(){
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
}

void al_set_registers(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp, ALLEGRO_TIMER* timer){
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
}

void draw_scenario(ALLEGRO_FONT* font, ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *spacing, float x, float y){
    int posx = 60, posy = 60;
    int distancia = 64;
    int highscore = 1337;
    int score = 300;
    int level = 2;
    al_draw_bitmap(background, 0, 0, 0);

    al_draw_line(720, 0, 720, 640, al_map_rgb_f(1, 0, 0), 1);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 290, -1, "High Score:");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 310, -1, "%d", highscore);
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 350, -1, "Pontuação atual:");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 370, -1, "%d", score);
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 410, -1, "Próxima fase em:");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 430, -1, "%d pontos", (level * 1000) - score);
    al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));
    al_draw_filled_rectangle(900, 20, 1050, 80, al_map_rgb(237, 153, 68));
    al_draw_textf(font, al_map_rgb(0, 0, 0), 975, 47.5, -1, "PAUSE");
    
}

void draw_help_secction(ALLEGRO_FONT* font, ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *spacing){
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_line(324, 213, 324, 480, al_map_rgb_f(0, 0, 0), 5);
    al_draw_line(680, 213, 680, 480, al_map_rgb_f(0, 0, 0), 5);
    al_draw_line(324, 213, 680, 213, al_map_rgb_f(0, 0, 0), 5);
    al_draw_line(324, 480, 680, 480, al_map_rgb_f(0, 0, 0), 5);
    al_draw_filled_rectangle(324, 213, 680, 480, al_map_rgba(0, 94, 171, 180));
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 223, -1, "Use o seu mouse para arrastar uma joia");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 238, -1, "Você pode trocar uma jóia com sua adjacente");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 253, -1, "E juntar pelo menos três jóias iguais");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 278, -1, "A pontuação se dá assim:");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 293, -1, "3 joias - 10 pontos");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 308, -1, "4 joias - 20 pontos");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 323, -1, "5 joias - 30 pontos");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 348, -1, "Como o jogo acaba:");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 363, -1, "Não havendo mais movimentos");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 378, -1, "Concluindo a fase");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 393, -1, "Fechando o jogo :)");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 418, -1, "Para concluir a fase você deve fazer"); 
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 433, -1, "1000 x nº da fase atual pontos."); 
    al_draw_textf(font, al_map_rgb(0, 0, 0), 502, 458, -1, "Boa sorte!"); 
    
}

void draw_jewel(ALLEGRO_BITMAP* jewel, float x, float y, int flags){
    al_draw_line(x, y, x, y+64, al_map_rgb(207, 123, 40), 3);
    al_draw_line(x+64, y, x+64, y+64, al_map_rgb(207, 123, 40), 3);
    al_draw_line(x, y, x+64, y, al_map_rgb(207, 123, 40), 3);
    al_draw_line(x, y+64, x+64, y+64, al_map_rgb(207, 123, 40), 3);
    al_draw_filled_rectangle(x, y, x+64, y+64, al_map_rgba(0, 94, 171, 100));
    al_draw_bitmap(jewel, x, y, 0);
}