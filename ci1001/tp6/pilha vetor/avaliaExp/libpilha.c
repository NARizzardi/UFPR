#include <stdio.h>
#include <stdlib.h>
#include "libpilha.h"

/* **************** Funcoes internas **************** */
/* Funcao interna para a lib pilha de char funcionar */
int eh_fechamento(char c, char fecha){
    if( ( (c == '(') && (fecha == ')')) || ((c == '[') && (fecha == ']')) || ((c == '{') && (fecha == '}')) )
        return 1;

    return 0;
}

/* Funcao interna que trata (ignorando) os casos de erro de entrada */
int eh_valor_valido(char c){
    if((c == ')') || (c == ']') || (c == '}'))
        return 1;

    return 0;
}


/* **************** Funcoes publicas **************** */
/* Funcao que inicializa a pilha definindo os valores iniciais da struct */
pilha_t *inicializa_pilha(){
    pilha_t *stack;
    if((stack = (pilha_t *)malloc(sizeof(pilha_t)))){
        stack->array = (char *)malloc(sizeof(char));
        stack->last = -1;
        stack->tam=0;
        return stack;
    }
    return 0;
}

/* Funcao que esvazia a pilha, removendo todos os seus elementos */
void esvazia_pilha(pilha_t *pilha){
    while(vazia(pilha) == 0)
        desempilha(pilha->array[pilha->last], pilha);
}

/* Funcao que retorna 1 se a pilha for vazia */
int vazia(pilha_t* pilha){
    if(pilha->tam == 0) 
        return 1;
    return 0;
}

/* Funcao que empilha um elemento no topo da pilha */
void empilha(char valor, pilha_t* pilha){
    pilha->tam++;
    pilha->array = (char *)realloc(pilha->array, pilha->tam*sizeof(char)); /* A cada incremento na pilha eh realocado um espaco adicional, mantendo a pilha apenas com o espaco de memoria necessario */
    pilha->last++;
    int pos = pilha->last;
    pilha->array[pos] = valor;
    
}

/* Funcao que tenta desempilhar o elemento no topo da pilha */
int desempilha(char valor, pilha_t* pilha){
    
    /* Condicional exclusivo do trabalho */
    /* Por nao ter o parametro da entrada, se houver valores incorretos na entrada eh aqui que trata o mesmo, ignorando-o */
    if((eh_valor_valido(valor) == 0 ))
        return 1;
    
    if(vazia(pilha) == 1)
        return 0;
    int pos = pilha->last;
    
    if(eh_fechamento(pilha->array[pos], valor) == 1){
        pilha->array[pos] = ' ';
        pilha->last--;
        pilha->tam--;
        pilha->array = (char *)realloc(pilha->array, pilha->tam*sizeof(char));/* A cada decremento na pilha realoca o espaco necessario, ocupando apenas o espaco de memoria necessario */
        return 1;
    }
    return 0;
}


/* Funcao que retorna o tamanho da pilha */
int tamanho(pilha_t* pilha){
    return pilha->tam;
}

/* Funcao que imprime a pilha do elemento mais ao topo ate a base da pilha */
/* Se a pilha nao tiver elementos imprime o aviso de que a pilha esta vazia */
void imprime (pilha_t* pilha){
    if(vazia(pilha) == 1){
        printf("pilha vazia\n");
        return;
    }
    int pos = pilha->last;
    while(pos != -1){
        printf("%c ", pilha->array[pos]);
        pos--;
    }
}

