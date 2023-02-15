#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

void start_allegro();

void must_init(bool test, const char *description);

void al_set_display();

void al_set_registers(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp, ALLEGRO_TIMER* timer);

void draw_home_screen(ALLEGRO_FONT* title_font, ALLEGRO_FONT* font, ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *spacing, float x, float y);

void draw_scenario(ALLEGRO_FONT* font, ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *spacing, float x, float y, int score, int goal, int highscore);

void draw_help_secction(ALLEGRO_FONT* big_font, ALLEGRO_FONT* mini_font, ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *spacing, float x, float y);

void draw_exit_confirmation(ALLEGRO_FONT* big_font, ALLEGRO_FONT* mini_font, ALLEGRO_DISPLAY *display,  ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *spacing, float x, float y);

void draw_jewel(ALLEGRO_BITMAP* jewel, float x, float y, int flags);