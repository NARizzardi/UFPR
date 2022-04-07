#include "libpilha.h"
#include <stdlib.h>

/* Cria e retorna uma nova pilha com capacidade de nelem elementos. 
 * Retornal NULL(0) em caso de erro de alocação */
pilha_t* inicializa_pilha(int nelem){
    pilha_t *pilha;

    if((pilha = (pilha_t *)malloc(sizeof(pilha_t)))){
        if((pilha->elems = (char *)malloc(nelem * sizeof(char)))){
            pilha->nelem = nelem;
            pilha->topo = -1;
            return pilha;
        }
        
        return NULL;
    }
    return NULL;
}

/* Insere o char elem na pilha. Retorna o número de elementos na pilha 
 * em caso de sucesso e -1 em caso de pilha cheia */
int push(pilha_t* pilha, char elem){
    if(pilha->nelem <= pilha->topo+1)
        return -1;
    pilha->topo++;
    pilha->elems[pilha->topo] = elem;
    pilha->nelem++;
    return pilha->nelem;
}

/* Remove e retorna um elemento da pilha. Em caso de pilha vazia retorna 0 */
char pop(pilha_t* pilha){
    if(pilha_vazia(pilha) == 1)
        return 0;
    char c = pilha->elems[pilha->topo];
    pilha->elems[pilha->topo] = ' ';
    pilha->nelem--;
    pilha->topo--;
    return c;
}
 
/* Similar ao Pop, mas retorna sem remover */
char topo(pilha_t* pilha){
    return pilha->elems[pilha->topo];
}

/* return 1 se pilha vazia, 0 em outros casos */ 
int pilha_vazia(pilha_t* pilha){
    if(pilha->nelem == 0)
        return 1;
    return 0;
}

/* desaloca memoria de pilha_t */
void destroi_pilha(pilha_t* pilha){
    free(pilha->elems);
    free(pilha);
}