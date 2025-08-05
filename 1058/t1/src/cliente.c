#include "../include/cliente.h"
#include <sys/statvfs.h>
#include <sys/select.h>
#include <net/if.h>

int mensagem_valida(char *movimento){
  if(strlen(movimento) != 1){ 
    printf("\nEntrada inválida. Use um dos números [0-3].\n");
    return 0;
  }
  if(movimento[0] > '3' || movimento[0] < '0'){
    printf("\nEntrada inválida. Use um dos números [0-3].\n");
    return 0;
  }
  return 1;
}

unsigned int pega_tipo(char movimento){
  switch(movimento){
    case '0': return DIREITA;
    case '1': return CIMA;
    case '2': return BAIXO;
    case '3': return ESQUERDA;
  }
  return -1;
}

mapa_t *gera_mapa(){
    mapa_t *mapa = malloc(sizeof(mapa_t));
    if (!mapa) {
        perror("malloc mapa");
        return NULL;
    }
    mapa->posJogadorX = 0;
    mapa->posJogadorY = 0;
    mapa->tesourosColetados = 0;
    for(int i = 0; i < 8; i++) {
        mapa->tesouros[i].coletado = 0;
        mapa->tesouros[i].coordenadaX = -1; 
        mapa->tesouros[i].coordenadaY = -1;
    }
    return mapa;     
} 

int pos_tesouro(int x, int y, mapa_t *mapa){
  for(int i = 0; i < 8; i++){
    if(mapa->tesouros[i].coletado && mapa->tesouros[i].coordenadaX == x && mapa->tesouros[i].coordenadaY == y) {
      return 1;
    }
  }
  return 0;
}

void imprime_mapa(mapa_t *mapa){
  printf("\n--- MAPA DO TESOURO ---\n");
  printf("+");
  for(int i = 0; i < 8; i++){
    printf("---+");
  }
  printf("\n");
  
  for(int i = 7; i >= 0; i--){ // Y
    printf("|");
    for(int j = 0; j < 8; j++){ // X
      if(j == mapa->posJogadorX && i == mapa->posJogadorY)
        printf(" J |");
      else if(pos_tesouro(j, i, mapa))
        printf(" T |");
      else
        printf("   |");
    }
    printf("\n+");
    for(int j = 0; j < 8; j++){
      printf("---+");
    }
    printf("\n");
  }
  printf("Tesouros coletados: %d\n", mapa->tesourosColetados);
}

void move_jogador(mapa_t *mapa, int x, int y){
    mapa->posJogadorX = x;
    mapa->posJogadorY = y;
}

void salva_tesouro(mapa_t *mapa, int tipo, int indice_tesouro){
    int posx = mapa->posJogadorX;
    int posy = mapa->posJogadorY;
    switch (tipo)
    {
    case DIREITA:
        posx++;
        break;
    case ESQUERDA:
        posx--;
        break;
    case CIMA:
        posy++;
        break;
    case BAIXO:
        posy--;
    break;
    default:
        break;
    }
    move_jogador(mapa, posx, posy);
    mapa->tesouros[indice_tesouro-1].coletado = 1;
    mapa->tesouros[indice_tesouro-1].coordenadaX = posx;
    mapa->tesouros[indice_tesouro-1].coordenadaY = posy;
    mapa->tesourosColetados++;
}

void recebe_arquivo(int soquete, struct sockaddr_ll endereco_servidor, const char* dados_anuncio, mapa_t *mapa, int sequencia_ack) {
    char nome_arquivo[64];
    unsigned int tamanho_arquivo;
    
    if (sscanf(dados_anuncio, "%s %u", nome_arquivo, &tamanho_arquivo) != 2) {
        fprintf(stderr, "Erro ao ler anúncio do arquivo.\n");
        return;
    }
    printf("Recebendo arquivo '%s' (%u bytes).\n", nome_arquivo, tamanho_arquivo);
    
    char buffer_envio[TAMANHO_BUFFER];
    monta_buffer(buffer_envio, ACK, 0, NULL, 0);
    envia_buffer(soquete, endereco_servidor, buffer_envio, TAMANHO_BUFFER);

    FILE* f_saida = fopen(nome_arquivo, "wb");
    if (!f_saida) {
        perror("fopen arquivo de saida");
        return;
    }

    char buffer_recebido[TAMANHO_BUFFER];
    mensagem_t msg_arquivo;
    unsigned int proxima_seq_esperada = 1;
    size_t bytes_recebidos_total = 0;

    while(1) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(soquete, &fds);
        struct timeval timeout = { .tv_sec = 5, .tv_usec = 0 };

        if (select(soquete + 1, &fds, NULL, NULL, &timeout) > 0) {
            struct sockaddr_ll addr_temp;
            if (recebe_mensagem(soquete, buffer_recebido, &addr_temp) > 0) {
                if (addr_temp.sll_pkttype == PACKET_OUTGOING) continue;
                
                remonta_mensagem(&msg_arquivo, buffer_recebido);
                if (msg_arquivo.tipo == DADOS && msg_arquivo.sequencia == proxima_seq_esperada) {
                    printf("Recebido pacote de dados #%u com %u bytes.\n", proxima_seq_esperada, msg_arquivo.tamanho);
                    fwrite(msg_arquivo.dados, 1, msg_arquivo.tamanho, f_saida);
                    bytes_recebidos_total += msg_arquivo.tamanho;
                    
                    monta_buffer(buffer_envio, ACK, proxima_seq_esperada, NULL, 0);
                    envia_buffer(soquete, endereco_servidor, buffer_envio, TAMANHO_BUFFER);
                    proxima_seq_esperada = (proxima_seq_esperada + 1) % 32;
                } else if(msg_arquivo.tipo == DADOS && msg_arquivo.sequencia == proxima_seq_esperada) {
                    monta_buffer(buffer_envio, ACK, proxima_seq_esperada, NULL, 0);
                    envia_buffer(soquete, endereco_servidor, buffer_envio, TAMANHO_BUFFER);
                } else if (msg_arquivo.tipo == ENDOFFILE && msg_arquivo.sequencia == proxima_seq_esperada) {
                    monta_buffer(buffer_envio, ACK, proxima_seq_esperada, NULL, 0);
                    envia_buffer(soquete, endereco_servidor, buffer_envio, TAMANHO_BUFFER);
                    break; 
                }
            }
        } else {
            printf("Timeout esperando por pacote de dados. A transferência pode ter falhado.\n");
        }
    }

    fclose(f_saida);
    printf("Transferência concluída. Arquivo %s. Total de %zu bytes recebidos.\n", nome_arquivo, bytes_recebidos_total);

    pid_t pid = fork();
    if (pid == 0) {
        char *ext = strrchr(nome_arquivo, '.');
        if (ext && strcmp(ext, ".mp4") == 0) {
            execlp("mpv", "mpv", nome_arquivo, (char*)NULL);
        } else {
            execlp("xdg-open", "xdg-open", nome_arquivo, (char*)NULL);
        }
        
        perror("Falha ao abrir o arquivo");
        _exit(1);
    }
}

int main(){
    unsigned int sequencia = 0;
    int soquete = cria_raw_socket(INTERFACE);
    if(soquete < 0) return 1;

    struct sockaddr_ll endereco_servidor = {0};
    endereco_servidor.sll_family = AF_PACKET;
    endereco_servidor.sll_protocol = htons(ETH_P_ALL);
    endereco_servidor.sll_ifindex = if_nametoindex(INTERFACE);
    
    memset(endereco_servidor.sll_addr, 0, ETH_ALEN);

    char buffer_envio[TAMANHO_BUFFER];
    char buffer_recebido[TAMANHO_BUFFER];
    
    mapa_t *mapa = gera_mapa();
    mensagem_t msg_recebida;

    char movimento[10];

    while(1){
        imprime_mapa(mapa);
        do{
            printf("\nQual o seu próximo movimento?\n[0] Direita | [1] Cima | [2] Baixo | [3] Esquerda\n> ");
            scanf("%s", movimento);
        } while(!mensagem_valida(movimento));

        unsigned int tipo = pega_tipo(movimento[0]);
        monta_buffer(buffer_envio, tipo, sequencia, NULL, 0);
        
        int ack_recebido = 0;
        int tentativas = 0;

        do {
            if(envia_buffer(soquete, endereco_servidor, buffer_envio, TAMANHO_BUFFER) < 0) {
                perror("envia_buffer");
                break;
            }
            
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(soquete, &fds);
            struct timeval timeout = { .tv_sec = 2, .tv_usec = 0 };

            if (select(soquete + 1, &fds, NULL, NULL, &timeout) > 0) {
                struct sockaddr_ll endereco_origem = {0};
                if(recebe_mensagem(soquete, buffer_recebido, &endereco_origem) > 0) {
                    
                    if (endereco_origem.sll_pkttype == PACKET_OUTGOING) continue;

                    remonta_mensagem(&msg_recebida, buffer_recebido);
                    int transacao_completa = 0;

                    switch(msg_recebida.tipo){
                        case NACK:
                            if(msg_recebida.sequencia == sequencia) {
                                printf("Recebido NACK do servidor. Retransmitindo...\n");
                                transacao_completa = 1;
                            }
                            break;
                        case ACKOK:
                            if(msg_recebida.sequencia == sequencia) {
                                int pos_x, pos_y, indice_tesouro;
                                int campos_lidos = sscanf((char*)msg_recebida.dados, "%d %d %d", &pos_x, &pos_y, &indice_tesouro);
                                if(campos_lidos >= 2) {
                                    move_jogador(mapa, pos_x, pos_y);
                                    if (campos_lidos == 3 && indice_tesouro != -1) {
                                        if (indice_tesouro >= 0 && indice_tesouro < 8 && !mapa->tesouros[indice_tesouro].coletado) {
                                            mapa->tesouros[indice_tesouro].coletado = 1;
                                            mapa->tesouros[indice_tesouro].coordenadaX = pos_x;
                                            mapa->tesouros[indice_tesouro].coordenadaY = pos_y;
                                            mapa->tesourosColetados++;
                                        }
                                    }
                                    transacao_completa = 1;
                                    sequencia = (sequencia + 1) % 32;
                                }
                            }
                            break;
                        case TEXTOACKNOME:
                        case VIDEOACKNOME:
                        case IMAGEMACKNOME:
                             if(msg_recebida.sequencia == 0) {
                                int indice_tesouro = atoi(msg_recebida.dados);
                                 printf("Você encontrou o tesouro %s!\n", msg_recebida.dados);
                                 recebe_arquivo(soquete, endereco_servidor, (const char*)msg_recebida.dados, mapa, sequencia);
                                 transacao_completa = 1;
                                 sequencia = (sequencia + 1) % 32;
                                 salva_tesouro(mapa, tipo, indice_tesouro);
                             }
                             break;
                        default:
                            printf("Tipo de mensagem inesperado recebido: %d\n", msg_recebida.tipo);
                            break;
                    }
                    if (transacao_completa) {
                        ack_recebido = 1;
                    }

                }
            } else {
                printf("Timeout esperando resposta. Retransmitindo...\n");
                tentativas++;
                if (tentativas >= 5) {
                    printf("Servidor não responde. Tente novamente mais tarde.\n");
                    break;
                }
            }
        } while(!ack_recebido);
    }

    free(mapa);
    close(soquete);
    return 0;
}
