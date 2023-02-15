#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

void must_init(bool test, const char *description){
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
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codec");
    must_init(al_reserve_samples(10), "audio samples");
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

void draw_home_screen(ALLEGRO_FONT* title_font, ALLEGRO_FONT* font, ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *spacing, float x, float y){
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_filled_rectangle(205, 235, 765, 283, al_map_rgba(237, 153, 68, 160));
    al_draw_textf(title_font, al_map_rgb(0, 0, 0), 485, 230, -1, "PUFFLES AND JEWELS");
    if(x >= 415 && x <= 550 && y >= 310 && y <= 350){
            al_draw_filled_rectangle(415, 310, 550, 350, al_map_rgba(250, 166, 81, 220));
            al_draw_filled_rectangle(415, 360, 550, 400, al_map_rgb(237, 153, 68));
            al_draw_filled_rectangle(415, 410, 550, 450, al_map_rgb(237, 153, 68));
    } else if(x >= 415 && x <= 550 && y >= 360 && y <= 400){
            al_draw_filled_rectangle(415, 310, 550, 350, al_map_rgb(237, 153, 68));
            al_draw_filled_rectangle(415, 360, 550, 400, al_map_rgba(250, 166, 81, 220));
            al_draw_filled_rectangle(415, 410, 550, 450, al_map_rgb(237, 153, 68));
    } else if(x >= 415 && x <= 550 && y >= 410 && y <= 450){
            al_draw_filled_rectangle(415, 310, 550, 350, al_map_rgb(237, 153, 68));
            al_draw_filled_rectangle(415, 360, 550, 400, al_map_rgb(237, 153, 68));
            al_draw_filled_rectangle(415, 410, 550, 450, al_map_rgba(250, 166, 81, 220));
    } else {
        al_draw_filled_rectangle(415, 310, 550, 350, al_map_rgb(237, 153, 68));
        al_draw_filled_rectangle(415, 360, 550, 400, al_map_rgb(237, 153, 68));
        al_draw_filled_rectangle(415, 410, 550, 450, al_map_rgb(237, 153, 68));
    }
    al_draw_textf(font, al_map_rgb(0, 0, 0), 480, 320, -1, "Novo Jogo");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 480, 370, -1, "Como Jogar");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 480, 420, -1, "Sair");
}

void draw_scenario(ALLEGRO_FONT* font, ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *spacing, float x, float y, int score, int goal, int highscore){
    
    al_draw_bitmap(background, 0, 0, 0);


    al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 285, -1, "High Score:");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 305, -1, "%d", highscore);
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 345, -1, "Pontuação atual:");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 365, -1, "%d", score);
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 405, -1, "Próxima fase em:");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 800, 425, -1, "%d pontos", (goal) - score);
    //al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));
    if(x >= 900 && x <= 1050 && y >= 20 && y <= 80){
        al_draw_filled_rectangle(900, 20, 1050, 80, al_map_rgba(250, 166, 81, 220));
    } else {
        al_draw_filled_rectangle(900, 20, 1050, 80, al_map_rgb(237, 153, 68));
    }
    if(x >= 900 && x <= 1050 && y >= 570 && y <= 630){
        al_draw_filled_rectangle(900, 570, 1050, 630, al_map_rgba(250, 166, 81, 220));
    } else {
        al_draw_filled_rectangle(900, 570, 1050, 630, al_map_rgb(237, 153, 68));
    }
    al_draw_textf(font, al_map_rgb(0, 0, 0), 975, 42, -1, "AJUDA");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 975, 590, -1, "SAIR");
    
}

void draw_help_secction(ALLEGRO_FONT* big_font, ALLEGRO_FONT* mini_font, ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *spacing, float x, float y){
    al_draw_bitmap(background, 0, 0, 0);
    
    al_draw_filled_rectangle(324, 213, 680, 480, al_map_rgba(0, 94, 171, 180));
    al_draw_line(324, 213, 324, 480, al_map_rgb_f(0, 0, 0), 5);
    al_draw_line(680, 213, 680, 480, al_map_rgb_f(0, 0, 0), 5);
    al_draw_line(321, 213, 683, 213, al_map_rgb_f(0, 0, 0), 5);
    al_draw_line(321, 480, 683, 480, al_map_rgb_f(0, 0, 0), 5);

    al_draw_line(670, 200, 670, 220, al_map_rgb_f(0, 0, 0), 4);
    al_draw_line(690, 200, 690, 220, al_map_rgb_f(0, 0, 0), 4);
    al_draw_line(668, 200, 692, 200, al_map_rgb_f(0, 0, 0), 4);
    al_draw_line(668, 220, 692, 220, al_map_rgb_f(0, 0, 0), 4);
    if(x >= 670 && x <= 690 && y >= 200 && y <= 220){
        al_draw_filled_rectangle(670, 200, 690, 220, al_map_rgba(250, 0, 0, 100));
    } else {
        al_draw_filled_rectangle(670, 200, 690, 220, al_map_rgba(250, 0, 0, 180));
    }
    al_draw_textf(big_font, al_map_rgb(0, 0, 0), 680, 200, -1, "X");

    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 223, -1, "Use o seu mouse para arrastar uma joia");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 238, -1, "Você pode trocar uma jóia com sua adjacente");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 253, -1, "E juntar pelo menos três jóias iguais");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 278, -1, "A pontuação se dá assim:");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 293, -1, "3 joias - 10 pontos");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 308, -1, "4 joias - 20 pontos");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 323, -1, "5 joias - 30 pontos");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 348, -1, "Como o jogo acaba:");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 363, -1, "Não havendo mais movimentos");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 378, -1, "Concluindo a fase");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 393, -1, "Fechando o jogo :)");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 418, -1, "Para concluir a fase você deve fazer"); 
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 433, -1, "1000 x no da fase atual pontos."); 
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 458, -1, "Boa sorte!"); 
    
}

void draw_exit_confirmation(ALLEGRO_FONT* big_font, ALLEGRO_FONT* mini_font, ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *spacing, float x, float y){
    
    //card box
    al_draw_filled_rectangle(324, 213, 680, 368, al_map_rgba(0, 94, 171, 220));
    al_draw_line(324, 213, 324, 368, al_map_rgb_f(0, 0, 0), 5);
    al_draw_line(680, 213, 680, 368, al_map_rgb_f(0, 0, 0), 5);
    al_draw_line(321, 213, 683, 213, al_map_rgb_f(0, 0, 0), 5);
    al_draw_line(321, 368, 683, 368, al_map_rgb_f(0, 0, 0), 5);
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 263, -1, "Você tem certeza que deseja sair?");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 502, 298, -1, "Seu progresso não será salvo");

    if(x >= 380 && x <= 480 && y >= 345 && y <= 385){
        al_draw_filled_rectangle(380, 345, 480, 385, al_map_rgba(50, 50, 50, 255));
    } else {
        al_draw_filled_rectangle(380, 345, 480, 385, al_map_rgba(0, 0, 0, 255));
    }
    if(x >= 540 && x <= 640 && y >= 345 && y <= 385){
        al_draw_filled_rectangle(540, 345, 640, 385, al_map_rgba(250, 50, 50, 255));
    } else {
        al_draw_filled_rectangle(540, 345, 640, 385, al_map_rgba(250, 0, 0, 255));
    }

    al_draw_line(540, 345, 540, 385, al_map_rgb_f(0, 0, 0), 3);
    al_draw_line(640, 345, 640, 385, al_map_rgb_f(0, 0, 0), 3);
    al_draw_line(538, 345, 642, 345, al_map_rgb_f(0, 0, 0), 3);
    al_draw_line(538, 385, 642, 385, al_map_rgb_f(0, 0, 0), 3);

    al_draw_textf(mini_font, al_map_rgb(255, 255, 255), 430, 355, -1, "Voltar");
    al_draw_textf(mini_font, al_map_rgb(0, 0, 0), 590, 355, -1, "Sair");
}

void draw_jewel(ALLEGRO_BITMAP* jewel, float x, float y, int flags){
    al_draw_line(x, y, x, y+64, al_map_rgb(207, 123, 40), 3);
    al_draw_line(x+64, y, x+64, y+64, al_map_rgb(207, 123, 40), 3);
    al_draw_line(x, y, x+64, y, al_map_rgb(207, 123, 40), 3);
    al_draw_line(x, y+64, x+64, y+64, al_map_rgb(207, 123, 40), 3);
    al_draw_filled_rectangle(x, y, x+64, y+64, al_map_rgba(0, 94, 171, 100));
    al_draw_bitmap(jewel, x, y, 0);
}