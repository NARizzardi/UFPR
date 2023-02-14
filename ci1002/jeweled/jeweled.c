#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "liballegro.h"
#include "libjeweled.h"


/* config vars */
#define KEY_SEEN     1
#define KEY_RELEASED 2
#define FPS 60
#define SCREEN_W 1080
#define SCREEN_H 640
#define TYPES 4

/* jewels enum */
#define GREEN 1
#define ORANGE 2
#define PURPLE 3
#define YELLOW 4
#define GOLDEN 5
#define RAINBOW 6

/* resources paths */
#define JEWEL1_FILE "./resources/images/jewel1.png"
#define JEWEL2_FILE "./resources/images/jewel2.png"
#define JEWEL3_FILE "./resources/images/jewel3.png"
#define JEWEL4_FILE "./resources/images/jewel4.png"
#define JEWEL5_FILE "./resources/images/jewel5.png"
#define JEWEL6_FILE "./resources/images/jewel6.png"
#define BACKGROUND_FILE "./resources/images/background2.bmp"
#define SPACING_FILE "./resources/images/spacing.bmp"
#define FONT_FILE "./resources/fonts/TurmaDaMonica.ttf"
#define TITLEFONT_FILE "./resources/fonts/TurmaDaMonica.ttf"

/* declare global vars*/
ALLEGRO_BITMAP* jewel1;
ALLEGRO_BITMAP* jewel2;
ALLEGRO_BITMAP* jewel3;
ALLEGRO_BITMAP* jewel4;
ALLEGRO_BITMAP* jewel5;
ALLEGRO_BITMAP* jewel6;
ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* spacing;
ALLEGRO_FONT* big_font;
ALLEGRO_FONT* mini_font;
ALLEGRO_FONT* title_font;

int score = 0;
int highscore[10];

int main()
{
    srand(time(NULL));
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

    
    al_init_font_addon();
    al_init_ttf_addon();
    title_font = al_load_font(TITLEFONT_FILE, 60, 1);
    big_font = al_load_font(FONT_FILE, 20, 1);
    mini_font = al_load_font(FONT_FILE, 16, 1);

    
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
    int screenstatus = -1;
    int menuFlag = 1;
    int exitFlag = 0;
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
                switch(screenstatus){
                    case -1:
                        if(event.mouse.x >= 415 && event.mouse.x <= 550){
                            if(event.mouse.y >= 310 && event.mouse.y <= 350){
                                //generate new game
                                menuFlag = 0;
                                screenstatus = 0;
                            } if(event.mouse.y >= 360 && event.mouse.y <= 400){
                                //enter help mode
                                screenstatus = 2;
                            }if(event.mouse.y >= 410 && event.mouse.y <= 450){
                                //exit game
                                done = true;
                            }
                        }

                        //main menu logic goes here
                        break;
                    case 1:
                        //pause menu logic goes here
                        break;
                    case 2:
                        //help menu logic goes here
                        if(event.mouse.x >= 670 && event.mouse.x <= 690 && event.mouse.y >= 200 && event.mouse.y <= 220)
                            if(menuFlag == 1)
                                screenstatus = -1;
                            else 
                                screenstatus = 0;
                        break;
                    default:
                        //if user clicks on help button
                        if(event.mouse.x >= 900 && event.mouse.x <= 1050 && event.mouse.y >= 20 && event.mouse.y <= 80) 
                            screenstatus = 2;
                        
                        //gaming area
                        if(event.mouse.x >= 60 && event.mouse.x <= 560 && event.mouse.y >= 60 && event.mouse.y <= 560)
                            //makes the gem logic going here
                            printf("you picked a gem here x:%d, y:%d", event.mouse.x, event.mouse.y);
                        
                        //if user clicks on exit button
                        if(event.mouse.x >= 900 && event.mouse.x <= 1050 && event.mouse.y >= 570 && event.mouse.y <= 630) 
                            exitFlag = 1;
                        
                        //if user confirms he wants to exit the game
                        if(exitFlag == 1 && event.mouse.x >= 300 && event.mouse.x <= 500 && event.mouse.y >= 570 && event.mouse.y <= 630){
                            done = true;
                            }
                        break;
                }
                printf("\nclicou em (%d, %d)", event.mouse.x, event.mouse.y);
                break;
		    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if(screenstatus == 0){
                    printf("\nyou dropped a gem here: (%d, %d)", event.mouse.x, event.mouse.y);
                }
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_F1){
                    if(screenstatus == 2){
                        if(menuFlag == 1){
                            screenstatus = -1;
                        } else {
                            screenstatus = 0;   
                        }
                    }else{
                        screenstatus = 2;
                    }
                }
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
            switch(screenstatus){
                case -1:
                    draw_home_screen(title_font, big_font, disp, background, spacing, x, y);
                    break;
                case 1:
                    //draw_pause_screen();
                    printf("pausou");
                    screenstatus = 0;
                    break;
                case 2:
                    draw_help_secction(big_font, mini_font, disp, background, spacing);
                    break;
                default:
                    draw_scenario(big_font, disp, background, spacing, x, y);
                    //draw_grid(jewel1,  jewel2,  jewel3,  jewel4);
                    if(exitFlag == 1)
                        draw_exit_confirmation(big_font, mini_font, disp, background, spacing, x, y);
                    break;
            }
            
            

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_font(big_font);
    al_destroy_font(mini_font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}