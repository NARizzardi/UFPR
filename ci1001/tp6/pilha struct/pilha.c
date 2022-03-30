#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

pilha_t *inicializa_pilha(){
    pilha_t *stack;
    if((stack = (pilha_t *)malloc(sizeof(pilha_t)))){
        stack->inicio = NULL;
        stack->fim = NULL;
        stack->tam=0;
        return stack;
    }
    return NULL;
}

cell_t *new_cell(int valor){
    cell_t *cell;
    if((cell = (cell_t *)malloc(sizeof(cell_t)))){
        cell->prox = NULL;
        cell->ant = NULL;
        cell->valor = valor;
        return cell;
    }
    return NULL;
}

void esvazia_pilha(pilha_t *pilha){
    while(vazia(pilha) == 0)
        desempilha(pilha);
}

int vazia(pilha_t* pilha){
    if(pilha->tam == 0) 
        return 1;
    return 0;
}

void empilha(int valor, pilha_t* pilha){
    cell_t *cell;
    if((cell = new_cell(valor))){
        if(vazia(pilha) == 1){
            pilha->inicio = cell;
        }else{
            pilha->fim->prox = cell;
            cell->ant = pilha->fim;
        }
        pilha->fim = cell;
        pilha->tam++;
    }
}

void desempilha(pilha_t* pilha){
    if(pilha->tam > 1){
        pilha->fim = pilha->fim->ant;
        free(pilha->fim->prox);
        pilha->fim->prox = NULL;
    } else {
        free(pilha->fim);
        pilha->inicio = NULL;
        pilha->fim = NULL;
    }
    pilha->tam--;
}

int tamanho(pilha_t* pilha){
    return pilha->tam;
}

void imprime (pilha_t* pilha){
    if(vazia(pilha) == 1){
        printf("pilha vazia\n");
        return;
    }
    cell_t *cell = pilha->fim;
    while(cell != NULL){
        printf("%d\n", cell->valor);
        cell = cell->ant;
    }
}

