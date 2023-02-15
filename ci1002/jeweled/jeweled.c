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
#define BACKGROUND_FILE "./resources/images/background.bmp"
#define SPACING_FILE "./resources/images/spacing.bmp"
#define FLIP_FILE "./resources/images/flip_iceberg.bmp"
#define LOGO_FILE "./resources/images/logo.png"
#define FONT_FILE "./resources/fonts/TurmaDaMonica.ttf"
#define TITLEFONT_FILE "./resources/fonts/TurmaDaMonica.ttf"
#define BACKGROUND_SOUND_FILE "./resources/audios/8bit_smooth.ogg"
#define MATCH_SOUND_FILE "./resources/audios/match.ogg"
#define LEVEL_SOUND_FILE "./resources/audios/level_complete.ogg"
#define NEW_GAME_SOUND_FILE "./resources/audios/new_game.ogg"

/* declare global vars */
ALLEGRO_BITMAP* jewel1;
ALLEGRO_BITMAP* jewel2;
ALLEGRO_BITMAP* jewel3;
ALLEGRO_BITMAP* jewel4;
ALLEGRO_BITMAP* jewel5;
ALLEGRO_BITMAP* jewel6;
ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* flip_background;
ALLEGRO_BITMAP* spacing;
ALLEGRO_BITMAP* logo;
ALLEGRO_FONT* big_font;
ALLEGRO_FONT* mini_font;
ALLEGRO_FONT* title_font;
ALLEGRO_AUDIO_STREAM* music;
ALLEGRO_SAMPLE* match;
ALLEGRO_SAMPLE* level_done;
ALLEGRO_SAMPLE* new_game;

jewel_t** jogo;
int score;
int level;
int goal;
int highscore;

int main(){

    /* Configuracao da biblioteca do Allegro */
    
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    start_allegro(); // Inicializacao basica
    

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_display();

    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);
    must_init(disp, "display");

    /* Regularizacao das fontes */
    al_init_font_addon();
    al_init_ttf_addon();
    title_font = al_load_font(TITLEFONT_FILE, 60, 1);
    big_font = al_load_font(FONT_FILE, 20, 1);
    mini_font = al_load_font(FONT_FILE, 16, 1);

    al_set_registers(queue, disp, timer);   

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    /* Carrega os arquivos */
    jewel1 = al_load_bitmap(JEWEL1_FILE);
    jewel2 = al_load_bitmap(JEWEL2_FILE);
    jewel3 = al_load_bitmap(JEWEL3_FILE);
    jewel4 = al_load_bitmap(JEWEL4_FILE);
    jewel5 = al_load_bitmap(JEWEL5_FILE);
    jewel6 = al_load_bitmap(JEWEL6_FILE);
    logo = al_load_bitmap(LOGO_FILE);
    background = al_load_bitmap(BACKGROUND_FILE);
    flip_background = al_load_bitmap(FLIP_FILE);
    spacing = al_load_bitmap(SPACING_FILE);
    music = al_load_audio_stream(BACKGROUND_SOUND_FILE, 4, 1024);
    match = al_load_sample(MATCH_SOUND_FILE);
    level_done = al_load_sample(LEVEL_SOUND_FILE);
    new_game = al_load_sample(NEW_GAME_SOUND_FILE);


    //Liga o stream no mixer
    al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
    
    //Define que o stream vai tocar no modo repeat
    al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);

    /* Fim da configuracao do Allegro */
    
    /* Configuracoes do jogo */
    srand(time(NULL));
    score = 0;
    level = 1;
    goal = 1000 * score;
    highscore = 0;
    /* Fim das configuracoes do jogo */

    /* Flags de Controle*/
    int menuFlag = 1;
    int exitFlag = 0;
    int animationFlag = 0;
    int screenstatus = -1;
    int flipFlag = 0;

    /* Posicao do Mouse */
    float x, y;

    /* Easter Egg */
    int count = 0;

    /* Comeco do jogo */
    al_set_display_icon(disp, logo);
    al_start_timer(timer);

    while(1){
        al_wait_for_event(queue, &event);

        switch(event.type){
            // Timer
            case ALLEGRO_EVENT_TIMER:
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                redraw = true;
                break;

            // Movimentacao do Mouse
            case ALLEGRO_EVENT_MOUSE_AXES:
                x = event.mouse.x;
                y = event.mouse.y;
                break;

            // Clique do mouse
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                switch(screenstatus){
                    case -1: // Logica do Menu Inicial
                        if(event.mouse.x >= 415 && event.mouse.x <= 550){
                            if(event.mouse.y >= 310 && event.mouse.y <= 350){
                                al_set_audio_stream_playing(music,0);
                                al_play_sample(new_game, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                                jogo = novo_jogo();
                                menuFlag = 0;
                                screenstatus = 0;
                            } if(event.mouse.y >= 360 && event.mouse.y <= 400){
                                //enter help mode
                                screenstatus = 1;
                            }if(event.mouse.y >= 410 && event.mouse.y <= 450){
                                //exit game
                                done = true;
                            }
                        }
                        break;
                    case 1: // Logica do menu de ajuda
                        if(event.mouse.x >= 670 && event.mouse.x <= 690 && event.mouse.y >= 200 && event.mouse.y <= 220){
                            if(menuFlag == 1){
                                screenstatus = -1;
                            } else {
                                screenstatus = 0;
                            }
                        }
                        break;
                    default:
                        // Se o jogador pede ajuda
                        if(event.mouse.x >= 900 && event.mouse.x <= 1050 && event.mouse.y >= 20 && event.mouse.y <= 80) {
                            screenstatus = 1;
                            count = 0;
                        }
                        // Area do jogo
                        if(event.mouse.x >= 130 && event.mouse.x <= 664 && event.mouse.y >= 60 && event.mouse.y <= 560){
                            //makes the gem logic going here
                            al_play_sample(level_done, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                            printf("you picked a gem here x:%d, y:%d", event.mouse.x, event.mouse.y);
                            count = 0;
                        }
                        // Easter egg
                        if(event.mouse.x >= 855 && event.mouse.x <= 948 && event.mouse.y >= 156 && event.mouse.y <= 233) {
                            count++;
                            if(count >= 18){
                                flipFlag = 1;
                            }
                        }

                        // Se o usuario quer sair
                        if(event.mouse.x >= 900 && event.mouse.x <= 1050 && event.mouse.y >= 570 && event.mouse.y <= 630) {
                            exitFlag = 1;
                            count = 0;
                        }
                        // Volta pro menu inicial
                        if(exitFlag == 1 && event.mouse.x >= 540 && event.mouse.x <= 640 && event.mouse.y >= 345 && event.mouse.y <= 385){
                            al_set_audio_stream_playing(music,1);
                            screenstatus = -1;
                            flipFlag = 0;
                            exitFlag = 0;
                        }
                        
                        // Volta pro jogo
                        if(exitFlag == 1 && event.mouse.x >= 380 && event.mouse.x <= 480 && event.mouse.y >= 345 && event.mouse.y <= 385){
                            exitFlag = 0;
                        }
                        break;
                }
                printf("\nclicou em (%d, %d)", event.mouse.x, event.mouse.y);
                break;

            // Soltar o clique do mouse (arrastar)
		    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if(screenstatus == 0){
                    printf("\nyou dropped a gem here: (%d, %d)", event.mouse.x, event.mouse.y);
                }
                break;

            // Apertar tecla
            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_F1){
                    if(screenstatus == 1){
                        if(menuFlag == 1){
                            screenstatus = -1;
                        } else {
                            screenstatus = 0;   
                        }
                    }else{
                        screenstatus = 1;
                    }
                }
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;

            // Soltar tecla
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            // Fechar o display
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }
        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            switch(screenstatus){ // Qual tela vai imprimir
                case -1:
                    draw_home_screen(title_font, big_font, disp, background, spacing, x, y); // Menu inicial
                    break;
                case 1:
                    draw_help_secction(big_font, mini_font, disp, background, spacing, x, y); // Seção de ajuda
                    break;
                default:
                    if(flipFlag == 1){
                        draw_scenario(big_font, disp, flip_background, spacing, x, y, score, goal, highscore); // Mapa do jogo 
                    } else {
                        draw_scenario(big_font, disp, background, spacing, x, y, score, goal, highscore); // Mapa do jogo 
                    }
                    draw_grid(jogo, jewel1,  jewel2,  jewel3,  jewel4); // Joias do jogo
                    if(exitFlag == 1){
                        draw_exit_confirmation(big_font, mini_font, disp, background, spacing, x, y); // Tela de saída do jogo
                    }
                    break;
            }
            
            

            al_flip_display();

            redraw = false;
        }
    }

    //stop_allegro(); <- send all "al_destroy here"
    al_destroy_bitmap(jewel1);
    al_destroy_bitmap(jewel2);
    al_destroy_bitmap(jewel3);
    al_destroy_bitmap(jewel4);
    al_destroy_bitmap(jewel5);
    al_destroy_bitmap(jewel6);
    al_destroy_bitmap(background);
    al_destroy_bitmap(flip_background);
    al_destroy_bitmap(spacing);
    al_destroy_bitmap(logo);
    al_destroy_sample(match);
    al_destroy_sample(level_done);
    al_destroy_sample(new_game);
    al_destroy_audio_stream(music);
    al_destroy_font(big_font);
    al_destroy_font(mini_font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}