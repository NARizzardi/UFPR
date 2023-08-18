#include <stdlib.h>
#include <stdio.h>
#include "libfila.h"

/*
 * Cria um nodo com chave elemento e o retorna, se falhar retorna NULL.
*/
nodo_f_t* nodo_cria(int elemento){
    nodo_f_t *nodo;
    if((nodo = (nodo_f_t *)malloc(sizeof(nodo_f_t)))){
        nodo->chave = elemento;
        nodo->prox = NULL;
        return nodo;
    }
    return NULL;
}

/*
 * Cria uma fila vazia e a retorna, se falhar retorna NULL.
*/
fila_t* fila_cria (){
    fila_t *f;
    if((f = (fila_t *)malloc(sizeof(fila_t)))){
        f->fim = f->ini = NULL;
        f->tamanho = 0;
        return f;
    }
    return NULL;
}

/*
 * Remove todos os elementos da fila, libera espaco e devolve NULL.
*/
fila_t* fila_destroi (fila_t* f){
    int elemento;
    while(fila_vazia(f) != 1){
        dequeue(f, &elemento);
    }
    free(f);
    return NULL;
}

/*
 * Retorna 1 se a fila esta vazia e 0 caso contrario.
*/
int fila_vazia (fila_t* f){
    if(fila_tamanho(f) == 0)
        return 1;
    return 0;
}

/*
 * Retorna o tamanho da fila, isto eh, o numero de elementos presentes nela.
*/
int fila_tamanho (fila_t* f){
    return f->tamanho;
}

/*
 * Insere o elemento no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int queue (fila_t* f, int elemento){
    nodo_f_t *nodo;
    if( (nodo = nodo_cria(elemento)) != NULL){
        if(fila_vazia(f) == 1)
            f->ini = nodo;
        else
            f->fim->prox = nodo;

        f->fim = nodo;
        f->tamanho++;
        return 1;
    }
    return 0;
}
    
/*
 * Remove elemento do inicio da fila (politica FIFO) e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int dequeue (fila_t* f, int *elemento){
    
    if(fila_vazia(f) == 1)
        return 0;

    nodo_f_t *inicio;
    *elemento = f->ini->chave;
    inicio = f->ini;
    f->ini = f->ini->prox;
    f->tamanho--;
    free(inicio);
    return 1;   
}

/*
 * Imprime a fila, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a fila estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD fila.
*/
void fila_imprime (fila_t* f){
    if(f->tamanho == 0)
        return;
    nodo_f_t *nodo;
    nodo = f->ini;
    
    while(nodo->prox != NULL){
        printf("%d ", nodo->chave);
        nodo = nodo->prox;
    }
    printf("%d ", nodo->chave);
}