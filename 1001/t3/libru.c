#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libru.h"
#include "liblista.h"

pessoa_t *gera_pessoa(int ticket){
    pessoa_t *pessoa;
    pessoa = (pessoa_t *) malloc(sizeof(pessoa_t));
    pessoa->ticket = ticket;
    pessoa->mascara =  rand() %2;
    pessoa->vacinado =  rand() %2;
    if(rand() % 2 == 1)
        pessoa->dinheiro = 3.8;
    else
        pessoa->dinheiro = 1.3;

    return pessoa;
}

data_t *cria_dados(){
    data_t *novos_dados;
    novos_dados = (data_t *) malloc(sizeof(data_t));
    novos_dados->dinheiro_mascaras = 0;
    novos_dados->dinheiro_refeicoes = 0;
    novos_dados->dinheiro_total = 0;
    
    return novos_dados;
}

void aleat(int min, int max, int *valor){
    srand(time(NULL));
    *valor = (rand() % (max - min + 1)) + min;
    
}

void enche_pilha(pilha_t* pilha){
    while(pilha_tamanho(pilha) != pilha->nelem)
        push(pilha, 1);
}

void popula_conjunto(pessoa_t *todas_pessoas[]){
    int i;
    for(i = 0; i < MAX_PESSOAS; i++){
        pessoa_t *nova_pessoa;
        nova_pessoa = gera_pessoa(i+1);
        todas_pessoas[i] = nova_pessoa;
    }
}

void popula_fila(fila_t *fila_pessoas){
    int i;
    for(i = 0; i < MAX_PESSOAS; i++){
        queue(fila_pessoas, i+1);
    }
}

pessoa_t *proximo(fila_t *fila_pessoas, pessoa_t *todas_pessoas[]){
    int ticket;
    pessoa_t *pessoa;

    dequeue(fila_pessoas, &ticket);
    pessoa = todas_pessoas[ticket-1];

    return pessoa;
}

int pega_ticket(pessoa_t *pessoa){
    return pessoa->ticket;
}

int eh_vacinado(pessoa_t *pessoa){
    return pessoa->vacinado;
}

void insere_ticket(lista_t *tickets_nao_usados, int ticket){
    lista_insere_ordenado(tickets_nao_usados, ticket);
}

int usa_mascara(pessoa_t *pessoa){
    return pessoa->mascara;
}

float saldo(pessoa_t *pessoa){
    return pessoa->dinheiro;
}

void compra_refeicao(pessoa_t *pessoa, pilha_t* refeicoes){
    pessoa->dinheiro = pessoa->dinheiro - 1.3;
    pop(refeicoes);
}

void adiciona_contador(data_t *dados_ru, int indicador){
    if(indicador == 0)
        dados_ru->dinheiro_refeicoes++;
     else 
         dados_ru->dinheiro_mascaras++;
    
}

int tem_mascara(pilha_t *mascaras){
    if(pilha_tamanho(mascaras) > 0)
        return 1;
    return 0;
}

void compra_mascara(pessoa_t *pessoa, pilha_t *mascaras){
    pessoa->dinheiro = pessoa->dinheiro - 2.5;
    pessoa->mascara = 1;
    pop(mascaras);
}

void volta_pra_fila(pessoa_t *pessoa, fila_t *fila_pessoas){
    queue(fila_pessoas, pessoa->ticket);
}

void imprime_dados(data_t *dados_ru, lista_t *tickets_nao_usados){
    dados_ru->dinheiro_total = dados_ru->dinheiro_refeicoes*1.30 + dados_ru->dinheiro_mascaras*2.50;
    printf("Dinheiro total arrecadado: %.2f\n", dados_ru->dinheiro_total);
    printf("Dinheiro de refeicoes: %.2f\n", dados_ru->dinheiro_refeicoes*1.3);
    printf("Dinheiro de mascaras: %.2f\n", dados_ru->dinheiro_mascaras*2.5);
    printf("Quantidade de tickets nao utilizados: %d\n", lista_tamanho(tickets_nao_usados));
    printf("Lista de tickets nao utilizados: ");
    lista_imprime(tickets_nao_usados);
}

void pessoas_destroi(pessoa_t *todas_pessoas[]){
    int i;
    for(i = 0; i < MAX_PESSOAS; i++)
        free(todas_pessoas[i]);
}

void dados_destroi(data_t *dados_ru){
    free(dados_ru);
}