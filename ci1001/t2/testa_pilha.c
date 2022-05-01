#include <stdio.h>
#include <stdlib.h>
#include "libpilha.h"

int main(){

    
    pilha_t *pilha_1;
    pilha_t *pilha_2;
    int i;

    printf("/* Cria as pilhas */\n");
    pilha_1 = pilha_cria(5);
    pilha_2 = pilha_cria(7);

    printf("/* Popula as duas pilhas */\n");
    for(i = 1; i <= 6; i++){
        
        if(push(pilha_1, i) != -1)
            printf("Elemento %d inserido na pilha 1\n", i);
        else
            printf("Pilha 1 cheia\n");
        
        if(push(pilha_2, i) != -1)
            printf("Elemento %d inserido na pilha 2\n\n", i);
        else
            printf("Pilha 2 cheia\n");
    }

    printf("/* Primeira impressao das duas pilhas */\n");
    printf("Pilha 1: ");
    pilha_imprime(pilha_1);
    printf("\nTamanho pilha 1: %d\n", pilha_tamanho(pilha_1));
    printf("Pilha 2: ");
    pilha_imprime(pilha_2);
    printf("\nTamanho pilha 2: %d\n\n", pilha_tamanho(pilha_2));

    printf("/* Pop das duas pilhas */\n");
    printf("Elemento %d removido da pilha 1\n", pop(pilha_1));
    printf("Elemento %d removido da pilha 2\n\n", pop(pilha_2));

     printf("/* Impressao das duas pilhas pós pop*/\n");
    printf("Pilha 1: ");
    pilha_imprime(pilha_1);
    printf("\nTamanho pilha 1: %d\n", pilha_tamanho(pilha_1));
    printf("Pilha 2: ");
    pilha_imprime(pilha_2);
    printf("\nTamanho pilha 2: %d\n\n", pilha_tamanho(pilha_2));


    printf("/* Ver topo das duas pilhas */\n");
    printf("Elemento %d eh o topo da pilha 1\n", pilha_topo(pilha_1));
    printf("Elemento %d eh o topo da pilha 2\n\n", pilha_topo(pilha_2));

     printf("/* Impressao das duas pilhas pós pop*/\n");
    printf("Pilha 1: ");
    pilha_imprime(pilha_1);
    printf("\nTamanho pilha 1: %d\n", pilha_tamanho(pilha_1));
    printf("Pilha 2: ");
    pilha_imprime(pilha_2);
    printf("\nTamanho pilha 2: %d\n\n", pilha_tamanho(pilha_2));


    printf("/* Desaloca espaco das duas pilhas para finalizar o programa*/\n");
    pilha_destroi(pilha_1);
    pilha_destroi(pilha_2);

    return 0;
}