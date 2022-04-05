#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libpilha.h"

/* Funcao do programa, nao da biblioteca que retorna o valor referente ao caracter inserido caso seja valido ou 0 caso invalido */
int valid_char(char c){
    /* Valores positivos para caracteres de abertura */
    /* Valores negativos para caracteres de fechamento */
    
    switch (c){
        case '(':
            return 1;
            break;
        
        case '[':
            return 2;
            break;
        
        case '{':
            return 3;
            break;
        
        case ')':
            return -1;
            break;
        
        case ']':
            return -2;
            break;
        
        case '}':
            return -3;
            break;
        
        default:
            return 0;
            break;
    }
    
}

int main(){
    
    /* Inicializacao das variaveis */
    pilha_t *pilha;
    char *entrada;
    int pos, valor, nelems;
    scanf("%d", &nelems);
    /* Inicializacao da pilha */
    pilha = inicializa_pilha(nelems);
    for(pos = 0; pos < 10; pos++){
        if(push(pilha, '(') != -1){
            printf("insercao feita\n");
        } else {
            printf("pilha cheia\n");
            return 0;
        }
    }
    destroi_pilha(pilha);
    return 0;
}
