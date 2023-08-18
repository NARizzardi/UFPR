#include <stdio.h>
#include <stdlib.h>
#include "libpilha.h"


pilha_t *inicializa_pilha(){
    pilha_t *stack;
    if((stack = (pilha_t *)malloc(sizeof(pilha_t)))){
        stack->array = (int *)malloc(sizeof(int));
        stack->last = -1;
        stack->tam=0;
        return stack;
    }
    return NULL;
}

void esvazia_pilha(pilha_t *pilha){
    while(vazia(pilha) == 0)
        desempilha(pilha->array[pilha->last], pilha);
}

int vazia(pilha_t* pilha){
    if(pilha->tam == 0) 
        return 1;
    return 0;
}

void empilha(int valor, pilha_t* pilha){
    pilha->tam++;
    pilha->array = (int *)realloc(pilha->array, pilha->tam*sizeof(int));
    pilha->last++;
    int pos = pilha->last;
    pilha->array[pos] = valor;
    
}

int desempilha(int valor, pilha_t* pilha){
    int pos = pilha->last;
    if(pilha->array[pos] == (valor * -1)){
        int pos = pilha->last;
        pilha->array[pos] = 0;
        pilha->last--;
        pilha->tam--;
        pilha->array = (int *)realloc(pilha->array, pilha->tam*sizeof(int));
        return 1;
    }
    return 0;
}

int tamanho(pilha_t* pilha){
    return pilha->tam;
}

void imprime (pilha_t* pilha){
    if(vazia(pilha) == 1){
        printf("pilha vazia\n");
        return;
    }
    int pos = pilha->last;
    while(pos != -1){
        printf("%d\n", pilha->array[pos]);
        pos--;
    }
}

