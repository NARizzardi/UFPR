#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main(){
    pilha_t *pilha;
    
    pilha = inicializa_pilha();
    
    free(pilha);
    return 0;
}