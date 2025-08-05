#include "../include/utils.h"
#include <math.h>

int marcador_inicio(char buffer){
    return (unsigned char)buffer == 0b01111110;
}

unsigned int cria_checksum(unsigned int tipo, unsigned int sequencia, unsigned int tamanho, const char* dados){
    unsigned int checksum = 0;
    checksum += tamanho;
    checksum += sequencia;
    checksum += tipo;
    if(dados && tamanho > 0){
        for(size_t i = 0; i < tamanho; i++){
            checksum += (unsigned char)dados[i];
        }
    }
    return checksum % 256;
}

void remonta_mensagem(mensagem_t *mensagem, const char *buffer){
    unsigned char byte1 = buffer[1];
    unsigned char byte2 = buffer[2];
    unsigned char byte3 = buffer[3];

    mensagem->marcador_inicio = buffer[0];
    mensagem->tamanho = byte1 & 0x7F;
    mensagem->sequencia = ((byte1 >> 7) & 0x01) << 4 | (byte2 & 0x0F);
    mensagem->tipo = (byte2 >> 4) & 0x0F;
    mensagem->checksum = byte3;
    memset(mensagem->dados, 0, TAMANHO_DADOS);

    if (mensagem->tamanho > 0 && mensagem->tamanho <= TAMANHO_DADOS) {
        memcpy(mensagem->dados, &buffer[4], mensagem->tamanho);
        mensagem->dados[mensagem->tamanho] = '\0';
    }
}

mensagem_t *nova_mensagem(){
    mensagem_t *mensagem = (mensagem_t*) malloc(sizeof(mensagem_t));
    if(!mensagem){
        perror("Erro ao alocar memoria para a mensagem.\n");
        return NULL;
    }
    memset(mensagem, 0, sizeof(mensagem_t));
    mensagem->marcador_inicio = 0b01111110;
    return mensagem;
}

void monta_buffer(char *buffer, unsigned int tipo, unsigned int sequencia, const char* dados, unsigned int tamanho) {
    memset(buffer, 0, TAMANHO_BUFFER);
    buffer[0] = 0b01111110;
    buffer[1] = (tamanho & 0x7F) | ((sequencia >> 4) & 0x01) << 7;
    buffer[2] = ((tipo << 4) & 0xF0) | (sequencia & 0x0F);
    buffer[3] = cria_checksum(tipo, sequencia, tamanho, dados);
    if (dados && tamanho > 0) {
        memcpy(&buffer[4], dados, tamanho);
    }
}

int envia_buffer(int soquete, struct sockaddr_ll endereco, const char *buffer, int tamanho_buffer){
    return sendto(soquete, buffer, tamanho_buffer, 0, (struct sockaddr*) &endereco, sizeof(endereco));
}

ssize_t recebe_mensagem(int soquete, char *buffer, struct sockaddr_ll *endereco_remetente){
    socklen_t endereco_size = sizeof(struct sockaddr_ll);
    int bytes_recebidos = recvfrom(soquete, buffer, TAMANHO_BUFFER - 1, 0, (struct sockaddr*)endereco_remetente, &endereco_size);
    if(bytes_recebidos > 0 && marcador_inicio(buffer[0])){
        return bytes_recebidos;
    }
    return -1;
}
