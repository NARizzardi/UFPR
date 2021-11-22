#include <stdlib.h>
#include <stdio.h>
#include "libconjunto.h"


int main(){

    conjunto_t *conj_a, *conj_b, *conj_c, *conj_d;
    conjunto_t *conj_uniao_ac, *conj_diff_ac, *conj_intersec_ac;

    int insercao;
    int max_tam = 20;
    int elemento = 0;
    /* CRIACAO DE CONJUNTOS */
    printf("Criacao de tres conjuntos para futura manipulacao e uma tentativa falha de criar um conjunto\n\n");
    printf("Tentativa de criar o conjunto A, com tamanho maximo de %d: \n", max_tam);
    conj_a = cria_conjunto(max_tam);
    if(conj_a != 0){
        printf("Conjunto A criado com sucesso\n\n");
    } else {
        printf("Nao foi possivel criar o conjunto A\n\n\n");
    }
    max_tam = 10;
    printf("Tentativa de criar o conjunto B, com tamanho maximo de %d: \n", max_tam);
    conj_b = cria_conjunto(max_tam);
    if(conj_b != 0){
        printf("Conjunto B criado com sucesso\n\n");
    } else {
        printf("Nao foi possivel criar o conjunto B\n\n\n");
    }

    max_tam = 8;
    printf("Tentativa de criar o conjunto C, com tamanho maximo de %d: \n", max_tam);
    conj_c = cria_conjunto(max_tam);
    if(conj_c != 0){
        printf("Conjunto C criado com sucesso\n\n");
    } else {
        printf("Nao foi possivel criar o conjunto C\n\n\n");
    }

    printf("Tentativa de criar o conjunto D: \n");
    conj_d = cria_conjunto(-1);
    if(conj_d != 0){
        printf("Conjunto D criado com sucesso\n\n");
    } else {
        printf("Nao foi possivel criar o conjunto D\n\n");
    }

    
    return 0;
}

/* valgrind --leak-check=full --track-origins=yes ./tp4 */