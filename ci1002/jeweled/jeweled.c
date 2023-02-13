#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "liballegro.h"
#include "libjeweled.h"

#define LINES 8
#define COLS 8
#define TYPES 4

#define KEY_SEEN     1
#define KEY_RELEASED 2
#define FPS 60
#define SCREEN_W 1080
#define SCREEN_H 640

#define GREEN 1
#define ORANGE 2
#define PURPLE 3
#define YELLOW 4
#define GOLDEN 5
#define RAINBOW 6

#define JEWEL1_FILE "./resources/jewel1.png"
#define JEWEL2_FILE "./resources/jewel2.png"
#define JEWEL3_FILE "./resources/jewel3.png"
#define JEWEL4_FILE "./resources/jewel4.png"
#define JEWEL5_FILE "./resources/jewel5.png"
#define JEWEL6_FILE "./resources/jewel6.png"
#define BACKGROUND_FILE "./resources/background2.bmp"
#define SPACING_FILE "./resources/spacing.bmp"

ALLEGRO_BITMAP* jewel1;
ALLEGRO_BITMAP* jewel2;
ALLEGRO_BITMAP* jewel3;
ALLEGRO_BITMAP* jewel4;
ALLEGRO_BITMAP* jewel5;
ALLEGRO_BITMAP* jewel6;
ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* spacing;
ALLEGRO_FONT* font;

int main()
{
    /* ### Configura a biblioteca do Allegro ### */
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    start_allegro();
    

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_display();

    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);
    must_init(disp, "display");

    font = al_create_builtin_font();
    must_init(font, "font");

    
    al_set_registers(queue, disp, timer);   

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    jewel1 = al_load_bitmap(JEWEL1_FILE);
    jewel2 = al_load_bitmap(JEWEL2_FILE);
    jewel3 = al_load_bitmap(JEWEL3_FILE);
    jewel4 = al_load_bitmap(JEWEL4_FILE);
    jewel5 = al_load_bitmap(JEWEL5_FILE);
    jewel6 = al_load_bitmap(JEWEL6_FILE);
    background = al_load_bitmap(BACKGROUND_FILE);
    spacing = al_load_bitmap(SPACING_FILE);

    float x, y;
    x = 100;
    y = 100;
    int help = -1;
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
            if(help == 1){
                draw_help_secction(font, disp, background, spacing);
            } else {
                draw_scenario(font, disp, background, spacing, x, y);
            }
            

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