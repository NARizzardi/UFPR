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

    printf("----------------------------------------------------\n\n");
    /* INSERCAO DE UM ELEMENTO APENAS NOS CONJUNTOS */
    printf("Inserindo o elemento \"0\" em dois conjuntos\n\n");
    printf("Inserindo o elemento \"0\" no conjunto A\n");
    if(insere(0, conj_a))
        printf("Elemento inserido com sucesso no conjunto A\n\n");
    printf("Inserindo o elemento \"0\" no conjunto B\n");
    if(insere(0, conj_b))
        printf("Elemento inserido com sucesso no conjunto B\n\n");


    printf("----------------------------------------------------\n\n");
    /* VERIFICANDO SE OS CONJUNTOS ESTAO VAZIOS */
    printf("Verificando se os conjuntos estao vazios\n\n");
    printf("Verificando se o conjunto A esta vazio ou nao\n");
    if(eh_vazio(conj_a) == 0){
        printf("O conjunto A nao esta vazio, sua cardinalidade eh %d\n\n", cardinalidade(conj_a));
    } else {
        printf("O conjunto A esta vazio\n\n");
    }
    printf("Verificando se o conjunto B esta vazio ou nao\n");
    if(eh_vazio(conj_b) == 0){
        printf("O conjunto B nao esta vazio, sua cardinalidade eh %d\n\n", cardinalidade(conj_b));
    } else {
        printf("O conjunto B esta vazio\n\n");
    }
    printf("Verificando se o conjunto C esta vazio ou nao\n");
    if(eh_vazio(conj_c) == 0){
        printf("O conjunto C nao esta vazio, sua cardinalidade eh %d\n\n", cardinalidade(conj_c));
    } else {
        printf("O conjunto C esta vazio\n\n");
    }

    printf("----------------------------------------------------\n\n");
    /* INSERCAO DOS DEMAIS ELEMENTOS NOS CONJUNTOS */
    printf("Inserindo os demais elementos nos tres conjuntos\n\n");
    printf("Inserindo elementos pares desornenados no conjunto A: \n\n");
    for(insercao = 40; insercao > 2; insercao-=2){
        insere(insercao, conj_a);
    }

    printf("Inserindo elementos impares desornenados no conjunto B: \n\n");
    for(insercao = 21; insercao > 3; insercao-=2){
        insere(insercao, conj_b);
    }

    printf("Inserindo multiplos de tres desornenados no conjunto C: \n\n");
    for(insercao = 27; insercao > 3; insercao-=3){
        insere(insercao, conj_c);
    }
    

    printf("----------------------------------------------------\n\n");
    /* VERIFICANDO A CARDINALIDADE DOS CONJUNTOS NOVAMENTE */
    printf("Verificando a cardinalidade dos conjuntos novamente\n\n");
    printf("O conjunto A possui cardinalidade %d\n\n", cardinalidade(conj_a));
    printf("O conjunto B possui cardinalidade %d\n\n", cardinalidade(conj_b));
    printf("O conjunto C possui cardinalidade %d\n\n", cardinalidade(conj_c));


    printf("----------------------------------------------------\n\n");
    /* TENTATIVA DE INSERIR UM ELEMENTO A MAIS*/
    printf("Tentando ultrapassar o tamanho maximo do conjunto\n\n");
    elemento = 10;
    if(insere(elemento, conj_a) == -1){
        printf("Tamanho maximo do conjunto A ja alcancado\n\n");
    }  

    printf("----------------------------------------------------\n\n");
    /* TENTATIVA DE REMOVER UM ELEMENTO DE CADA CONJUNTO*/
    printf("Vamos remover um elemento de cada conjunto, sem perder a ordenacao\n\n");
    elemento = 0;
    if(retira(elemento, conj_a) == 1){
        printf("Elemento %d removido com sucesso do conjunto A\n\n", elemento);
    } else {
        printf("O elemento %d nao fazia parte do conjunto A\n\n", elemento);
    }

    if(retira(elemento, conj_b) == 1){
        printf("Elemento %d removido com sucesso do conjunto B\n\n", elemento);
    } else {
        printf("O elemento %d nao fazia parte do conjunto B\n\n", elemento);
    }

    if(retira(elemento, conj_c) == 1){
        printf("Elemento %d removido com sucesso do conjunto C\n\n", elemento);
    } else {
        printf("O elemento %d nao fazia parte do conjunto C\n\n", elemento);
    }

    
    printf("----------------------------------------------------\n\n");
    /* TENTATIVA DE INSERIR UM ELEMENTO JA PERTENCENTE*/
    printf("Tentando adicionar um elemento que ja fazia parte\n\n");
    elemento = 10;
    if(insere(elemento, conj_a) == 0){
        printf("Elemento %d ja faz parte do conjunto A \n\n", elemento);
    }



    printf("----------------------------------------------------\n\n");
    /* DESTRUIR UM CONJUNTO QUE NAO VAMOS MAIS UTILIZAR*/
    printf("Vamos remover o conjunto B pois nao utilizaremos ele mais\n\n");
    destroi_conjunto(conj_b);


    
    printf("----------------------------------------------------\n\n");
    /* VAMOS CRIAR O CONJUNTO DE UNIAO ENTRE A E C*/
    printf("Vamos criar o conjunto de uniao entre os conjuntos A e C\n\n");
    printf("Conjunto A\n");
    imprime(conj_a);
    printf("Conjunto C\n");
    imprime(conj_c);
    
    conj_uniao_ac = cria_uniao(conj_a, conj_c);
    if(conj_uniao_ac != 0){
        printf("Conjunto uniao de A e C\n");
        imprime(conj_uniao_ac);
    } else {
        printf("Nao foi possivel criar a uniao entre A e C");
    }


    printf("----------------------------------------------------\n\n");
    /* VAMOS CRIAR O CONJUNTO DE INTERSECCAO ENTRE A E C*/
    printf("Vamos criar o conjunto de interseccao entre os conjuntos A e C\n\n");
    printf("Conjunto A\n");
    imprime(conj_a);
    printf("Conjunto C\n");
    imprime(conj_c);
    conj_intersec_ac = cria_interseccao(conj_a, conj_c);
    if(conj_intersec_ac != 0){
        printf("Conjunto interseccao de A e C\n");
        imprime(conj_intersec_ac);
    } else {
        printf("Nao foi possivel criar a interseccao entre A e C");
    }


    printf("----------------------------------------------------\n\n");
    /* VAMOS CRIAR O CONJUNTO DE DIFERENCA ENTRE A E C*/
    printf("Vamos criar o conjunto de diferenca entre os conjuntos A e C\n\n");
    printf("Conjunto A\n");
    imprime(conj_a);
    printf("Conjunto C\n");
    imprime(conj_c);
    conj_diff_ac = cria_diferenca(conj_a, conj_c);
    if(conj_diff_ac != 0){
        printf("Conjunto diferenca de A e C\n");
        imprime(conj_diff_ac);
    } else {
        printf("Nao foi possivel criar a diferenca entre A e C");
    }

    printf("----------------------------------------------------\n\n");
    /* VAMOS CRIAR UM CONJUNTO PARA VER SE ESTA CONTIDO OU NAO*/
    printf("Vamos criar um conjunto D e ver se ele esta contido em A e C\n\n");
    max_tam = 4;
    conj_d= cria_conjunto(max_tam);
    if(conj_d != 0){
        printf("Conjunto B criado com sucesso\n\n");
    } else {
        printf("Nao foi possivel criar o conjunto A\n\n\n");
    }
    for(insercao = 22; insercao > 15; insercao-=2){
        insere(insercao, conj_d);
    }
    if(contido(conj_d, conj_a) == 1){
        printf("O conjunto D esta contido em A\n");
    } else {
        printf("O conjunto D nao esta contido em A\n");
    }
    imprime(conj_d);
    imprime(conj_a);

    if(contido(conj_d, conj_c) == 1){
        printf("O conjunto D esta contido em C\n");
    } else {
        printf("O conjunto D nao esta contido em C\n");
    }
    imprime(conj_d);
    imprime(conj_c);


    printf("----------------------------------------------------\n\n");
    /* VAMOS CRIAR UM CONJUNTO PARA VER SE ELE E IGUAL OU NAO*/
    printf("Vamos criar um conjunto B e ver se ele eh igual a A ou C\n\n");
    max_tam = 20;
    conj_b = cria_conjunto(max_tam);
    if(conj_b != 0){
        printf("Conjunto B criado com sucesso\n\n");
    } else {
        printf("Nao foi possivel criar o conjunto A\n\n\n");
    }
    for(insercao = 40; insercao > 2; insercao-=2){
        insere(insercao, conj_b);
    }

    if(sao_iguais(conj_a, conj_b) == 1){
        printf("O conjunto A e o conjunto B sao iguais\n\n");
    } else {
        printf("O conjunto A e o conjunto B nao sao iguais\n\n");
    }
    imprime(conj_a);
    imprime(conj_b);

    if(sao_iguais(conj_c, conj_b) == 1){
        printf("O conjunto C e o conjunto B sao iguais\n\n");
    } else {
        printf("O conjunto C e o conjunto B nao sao iguais\n\n");
    }
    imprime(conj_c);
    imprime(conj_b);


    /* LIBERAR TODOS OS ESPACOS ALOCADOS DURANTE A EXECUCAO DO PROGRAMA */    
    destroi_conjunto(conj_a);
    destroi_conjunto(conj_b);
    destroi_conjunto(conj_c);
    destroi_conjunto(conj_d);
    destroi_conjunto(conj_diff_ac);
    destroi_conjunto(conj_intersec_ac);
    destroi_conjunto(conj_uniao_ac);
    return 0;
}

/* valgrind --leak-check=full --track-origins=yes ./tp4 */