#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <sys/time.h>
#include <sys/select.h>
#include <time.h>
#include "raw_socket.h"
#include "utils.h"

// Estruturas de dados do servidor
struct tesouro{
    char nome[64];
    unsigned int tamanho;
    unsigned int tipo;
    char coordenadaX;
    char coordenadaY;
    short int coletado;
}; 
typedef struct tesouro tesouro_t;

struct mapa {
    int posJogadorX;
    int posJogadorY;
    short int tesourosColetados;
    tesouro_t tesouros[8];
};
typedef struct mapa mapa_t;

// Estrutura para controle de estado por cliente
typedef struct client_state {
    unsigned char mac_addr[ETH_ALEN];
    unsigned int last_sequence;
    struct client_state *next;
} client_state_t;


// --- Protótipos das Funções do Servidor ---
int verifica_tipo (char buffer);
int move_jogador(mapa_t *mapa, int tipo);
void cria_tesouro(tesouro_t *tesouro, int posX, int posY, int iterador);
int posicao_ocupada(int x, int y, int posx[], int posy[], int total);
mapa_t *gera_mapa(short int flag);
int encontra_tesouro(mapa_t *m);
unsigned int extrai_sequencia_do_buffer(const char *buffer);
client_state_t* find_or_create_client_state(unsigned char *mac_addr);

// CORREÇÃO: Assinatura da função alterada para ser mais auto-contida.
void enviar_tesouro(int soquete, struct sockaddr_ll endereco_cliente, tesouro_t* tesouro);


#endif
