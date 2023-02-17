#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

void start_allegro();

void must_init(bool test, const char* description);

void al_set_display();

void al_set_registers(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp, ALLEGRO_TIMER* timer);

void draw_home_screen(ALLEGRO_FONT* title_font, ALLEGRO_FONT* font, ALLEGRO_DISPLAY* display,  ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* spacing, float x, float y);

void draw_scenario(ALLEGRO_FONT* font, ALLEGRO_DISPLAY* display,  ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* spacing, float x, float y, int score, int goal, int highscore, int jogadas);

void draw_help_secction(ALLEGRO_FONT* big_font, ALLEGRO_FONT* mini_font, ALLEGRO_DISPLAY* display,  ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* spacing, float x, float y);

void draw_exit_confirmation(ALLEGRO_FONT* big_font, ALLEGRO_FONT* mini_font, ALLEGRO_DISPLAY* display,  ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* spacing, float x, float y);

void draw_level_complete_confirmation(ALLEGRO_FONT* big_font, ALLEGRO_FONT* mini_font, ALLEGRO_DISPLAY* display,  ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* spacing, float x, float y);

void draw_game_over_confirmation(ALLEGRO_FONT* big_font, ALLEGRO_FONT* mini_font, ALLEGRO_DISPLAY* display,  ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* spacing, float x, float y);

void draw_jewel(ALLEGRO_BITMAP* jewel, float x, float y, int flags);

void destroy_bitmaps(ALLEGRO_BITMAP* jewel1, ALLEGRO_BITMAP* jewel2, ALLEGRO_BITMAP* jewel3, ALLEGRO_BITMAP* jewel4, ALLEGRO_BITMAP* jewel5, ALLEGRO_BITMAP* jewel6, ALLEGRO_BITMAP* background, ALLEGRO_BITMAP* spacing, ALLEGRO_BITMAP* flip_background, ALLEGRO_BITMAP* logo);

void destroy_samples(ALLEGRO_SAMPLE* flip, ALLEGRO_SAMPLE* denied, ALLEGRO_SAMPLE* match, ALLEGRO_SAMPLE* level_done, ALLEGRO_SAMPLE* new_game, ALLEGRO_AUDIO_STREAM* music);

void destroy_fonts(ALLEGRO_FONT* big_font, ALLEGRO_FONT* mini_font);

void destroy_basics(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp, ALLEGRO_TIMER* timer);