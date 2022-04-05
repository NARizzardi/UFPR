#ifndef _LIBpilha_t_H
#define _LIBpilha_t_H

typedef struct {
    char *elems;   /* espaco armazenamento dos elementos */
    int nelem;     /* qtde elementos */
    int topo;      /* elelemento do topo da pilha */
} pilha_t;

/* Cria e retorna uma nova pilha com capacidade de nelem elementos. 
 * Retornal NULL(0) em caso de erro de alocação */
pilha_t* inicializa_pilha(int nelem);

/* Insere o char elem na pilha. Retorna o número de elementos na pilha 
 * em caso de sucesso e -1 em caso de pilha cheia */
int push(pilha_t* pilha, char elem);

/* Remove e retorna um elemento da pilha. Em caso de pilha vazia retorna 0 */
char pop(pilha_t* pilha);
 
/* Similar ao Pop, mas retorna sem remover */
char topo(pilha_t* pilha);  

/* return 1 se pilha vazia, 0 em outros casos */ 
int pilha_vazia(pilha_t* pilha);

/* desaloca memoria de pilha_t */
void destroi_pilha(pilha_t* pilha);

#endif