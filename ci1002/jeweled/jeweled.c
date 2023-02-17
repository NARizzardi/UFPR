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
#define LINESIZE 1024

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
#define FLIP_SOUND_FILE "./resources/audios/flip.ogg"
#define DENIED_SOUND_FILE "./resources/audios/denied.ogg"
#define NEW_GAME_SOUND_FILE "./resources/audios/new_game.ogg"
#define HIGHSCORE_FILE "./resources/highscore.txt"

/* Variaveis do Allegro */
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
ALLEGRO_SAMPLE* denied;
ALLEGRO_SAMPLE* level_done;
ALLEGRO_SAMPLE* new_game;
ALLEGRO_SAMPLE* flip;

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* disp;
ALLEGRO_EVENT event;

unsigned char key[ALLEGRO_KEY_MAX];
bool done = false;
bool redraw = true;

/* Variaveis do jogo */
jewel_t** jogo;
int score;
int level;
int goal;
int highscore;
int pontos;
int jogadas;
int fixedGoal;
FILE *highscore_file;

/* Flags de Controle*/
int pickupFlag = 0;
int menuFlag = 1;
int exitFlag = 0;
int screenstatus = -1;
int flipFlag = 0;
int gameOverFlag = 0;
int levelCompleteFlag = 0;

/* Posicao do Mouse */
float lastx, lasty;
float x, y;

/* Easter Egg */
int count = 0;


void inicializa_allegro(){
    /* Configuracao da biblioteca do Allegro */
    
    start_allegro(); // Inicializacao basica

    timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_display();

    disp = al_create_display(SCREEN_W, SCREEN_H);
    must_init(disp, "display");

    /* Regularizacao das fontes */
    al_init_font_addon();
    al_init_ttf_addon();
    title_font = al_load_font(TITLEFONT_FILE, 60, 1);
    big_font = al_load_font(FONT_FILE, 20, 1);
    mini_font = al_load_font(FONT_FILE, 16, 1);

    al_set_registers(queue, disp, timer);   
}

void carrega_arquivos(){
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
    flip = al_load_sample(FLIP_SOUND_FILE);
    denied = al_load_sample(DENIED_SOUND_FILE);

    //Liga o stream no mixer
    al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
    
    //Define que o stream vai tocar no modo repeat
    al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);

    highscore_file = fopen(HIGHSCORE_FILE, "r");
    char higscore_string[LINESIZE];
    fgets(higscore_string, LINESIZE, highscore_file);
    highscore = atoi(higscore_string);
    
}

void executa_jogo(){

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
                        if(x >= 415 && x <= 550){
                            if(y >= 310 && y <= 350){
                                al_set_audio_stream_playing(music,0);
                                al_play_sample(new_game, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                                jogo = novo_jogo();
                                menuFlag = 0;
                                screenstatus = 0;
                                score = 0;
                                level = 1;
                                jogadas = 35 * level;
                                fixedGoal = 1000 * level;
                                goal = fixedGoal;
                            } if(y >= 360 && y <= 400){
                                //enter help mode
                                screenstatus = 1;
                            }if(y >= 410 && y <= 450){
                                //exit game
                                done = true;
                            }
                        }
                        break;
                    case 1: // Logica do menu de ajuda
                        if(x >= 670 && x <= 690 && y >= 200 && y <= 220){
                            if(menuFlag == 1){
                                screenstatus = -1;
                            } else {
                                screenstatus = 0;
                            }
                        }
                        break;
                    default:
                        // Se o jogador pede ajuda
                        if(x >= 900 && x <= 1050 && y >= 20 && y <= 80) {
                            screenstatus = 1;
                            count = 0;
                        }
                        // Area do jogo
                        if(x >= 130 && x <= 684 && y >= 60 && y <= 616){
                            if(exitFlag == 0 && gameOverFlag == 0){
                                    //O jogador acabou de pegar uma joia
                                    lastx = x;
                                    lasty = y;
                                    pickupFlag = 1;
                            }
                            count = 0;
                        }
                        // Easter egg
                        if(x >= 855 && x <= 948 && y >= 156 && y <= 233) {
                            count++;
                            if(count >= 18){
                                al_play_sample(flip, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                                flipFlag = 1;
                            }
                        }

                        // Se o usuario quer sair
                        if(x >= 900 && x <= 1050 && y >= 570 && y <= 630) {
                            exitFlag = 1;
                            count = 0;
                        }
                        // Volta pro menu inicial
                        if(exitFlag == 1 && x >= 540 && x <= 640 && y >= 345 && y <= 385){
                            al_set_audio_stream_playing(music,1);
                            al_rewind_audio_stream(music);
                            screenstatus = -1;
                            menuFlag = 1;
                            flipFlag = 0;
                            exitFlag = 0;
                            level = 1;
                        }
                        // Se o jogador não tem mais movimentos disponiveis
                        if(levelCompleteFlag == 1 && x >= 380 && x <= 640 && y >= 345 && y <= 385){
                            level++;
                            fixedGoal = fixedGoal + (750*level);
                            goal = fixedGoal - score;
                            levelCompleteFlag = 0;
                            jogadas = 35 * level;
                            jogo = novo_jogo();
                        }
                        // Se o jogador não tem mais movimentos disponiveis
                        if(gameOverFlag == 1 && x >= 380 && x <= 640 && y >= 345 && y <= 385){
                            al_set_audio_stream_playing(music,1);
                            al_rewind_audio_stream(music);
                            screenstatus = -1;
                            menuFlag = 1;
                            flipFlag = 0;
                            gameOverFlag = 0;
                            level = 1;
                        }
                        // Volta pro jogo
                        if(exitFlag == 1 && x >= 380 && x <= 480 && y >= 345 && y <= 385){
                            exitFlag = 0;
                        }
                        break;
                }
                break;

            // Soltar o clique do mouse (arrastar)
		    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if(screenstatus == 0 && exitFlag == 0){
                    if(pickupFlag == 1){
                        int oldColumn = get_index(lastx, 0);
                        int oldRow  = get_index(lasty, 1);
                        int newColumn = get_index(x, 0);
                        int newRow  = get_index(y, 1);

                        if(sao_vizinhos(oldColumn, oldRow, newColumn, newRow) == 1){                        
                            if(troca_valida(jogo, oldColumn, oldRow, newColumn, newRow) == 1){
                                jogadas--;
                                al_play_sample(match, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                                while(checa_mapa(jogo) == 1){
                                    pontos = troca_pecas(jogo, oldColumn, oldRow, newColumn, newRow);
                                    score += pontos;
                                    goal -= pontos;
                                    atualiza_mapa(jogo);
                                }

                                if(score >= fixedGoal){
                                    al_play_sample(level_done, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                                    levelCompleteFlag = 1;
                                }
                            } else {
                                al_play_sample(denied, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                            }
                            
                        }   

                        if(score > highscore){
                            highscore = score;
                        }
                        if(jogadas == 0){
                            gameOverFlag = 1;
                        }
                        lastx = lasty = 0;
                        pickupFlag = 0;
                    }
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
                        draw_scenario(big_font, disp, flip_background, spacing, x, y, score, goal, highscore, jogadas); // Mapa do jogo 
                    } else {
                        draw_scenario(big_font, disp, background, spacing, x, y, score, goal, highscore, jogadas); // Mapa do jogo 
                    }
                    draw_grid(jogo, jewel1,  jewel2,  jewel3,  jewel4, jewel5, jewel6); // Joias do jogo
                    if(exitFlag == 1){
                        draw_exit_confirmation(big_font, mini_font, disp, background, spacing, x, y); // Tela de saída do jogo
                    }
                    if(levelCompleteFlag == 1){
                        draw_level_complete_confirmation(big_font, mini_font, disp, background, spacing, x, y); // Tela de fase concluida
                    }
                    if(gameOverFlag == 1){
                        draw_game_over_confirmation(big_font, mini_font, disp, background, spacing, x, y); // Tela de fim do jogo
                    }
                    break;
            }
            
            

            al_flip_display();

            redraw = false;
        }
    }

}

void encerra_allegro(){
    
    destroy_bitmaps(jewel1, jewel2, jewel3, jewel4, jewel5, jewel6, background, flip_background, spacing, logo);

    destroy_samples(flip, denied, match, level_done, new_game, music);

    destroy_fonts(big_font, mini_font);

    destroy_basics(queue, disp, timer);
}

int main(){

    /* Inicialização do jogo*/
    inicializa_allegro();
    memset(key, 0, sizeof(key));
    carrega_arquivos();
    
    /* Configuracoes do jogo */
    srand(time(NULL));
    /* Fim das configuracoes do jogo */

    /* Rodando o jogo */
    executa_jogo();
    
    /* Finalizando o jogo */
    encerra_allegro();
    encerra_jeweled(jogo, highscore, highscore_file, HIGHSCORE_FILE);
    return 0;
}