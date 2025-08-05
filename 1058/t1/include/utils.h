#ifndef UTILS_H
#define UTILS_H

#include "raw_socket.h"
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> // <-- ADICIONADO AQUI

// Definições do protocolo
#define ACK 0 
#define NACK 1
#define ACKOK 2
#define TAMANHO 4
#define DADOS 5
#define TEXTOACKNOME 6
#define VIDEOACKNOME 7
#define IMAGEMACKNOME 8
#define ENDOFFILE 9
#define DIREITA 10
#define CIMA 11
#define BAIXO 12
#define ESQUERDA 13
#define ERRO 15

#define INTERFACE "eno1"
#define TAMANHO_BUFFER 131
#define TAMANHO_DADOS 126

// Definições de erro
#define ACCESS_DENIED 0
#define NO_SPACE_LEFT 1

// Struct para REPRESENTAÇÃO LÓGICA da mensagem
struct mensagem {
    unsigned int marcador_inicio;
    unsigned int tamanho;
    unsigned int sequencia;
    unsigned int tipo;
    unsigned int checksum;
    unsigned char dados[TAMANHO_DADOS];
};
typedef struct mensagem mensagem_t;

// Funções utilitárias
int marcador_inicio(char buffer);
unsigned int cria_checksum(unsigned int tipo, unsigned int sequencia, unsigned int tamanho, const char* dados);
int valida_checksum(mensagem_t *mensagem);
mensagem_t *nova_mensagem();

// Funções de protocolo
void monta_buffer(char *buffer, unsigned int tipo, unsigned int sequencia, const char* dados, unsigned int tamanho);
void remonta_mensagem(mensagem_t *mensagem, const char *buffer);
int envia_buffer(int soquete, struct sockaddr_ll endereco, const char *buffer, int tamanho_buffer);
ssize_t recebe_mensagem(int soquete, char *buffer, struct sockaddr_ll *endereco_remetente);

#endif
