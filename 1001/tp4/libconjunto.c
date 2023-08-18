#include <stdlib.h>
#include <stdio.h>
#include "libconjunto.h"


/* INICIO DAS FUNCOES LOCAIS DA BIBLIOTECA */

/* retorna a posicao para inserir um novo valor ou remover um valor atual*/
int encontra_pos(int n, conjunto_t *c){
    int pos;
    for(pos = 0; pos < c->card; pos++){
        if(*(c->v+pos) > n){
            return pos;
        }
    }
    return c->card;
}

/* insere o valor no conjunto sem perder a ordenacao do mesmo*/
void insere_ordenado(int n, conjunto_t *c){
    int pos = encontra_pos(n, c);
    int i;
    for(i = c->card-1; i >=pos; i-- ){
        *(c->v+i+1) = *(c->v+i);
    }
    *(c->v+pos) = n;
}

/* retorna 1 se encontra o valor n no conjunto*/
int busca_binaria(int n, conjunto_t *c){
    int inicio, fim, pivo;
    inicio = 0;
    fim = c->card;
    while(inicio < fim){
        pivo = (inicio + fim) / 2;
        if(*(c->v+pivo) == n) 
            return 1;
        if(*(c->v+pivo) < n){
            inicio = pivo + 1;
        } else {
            fim = pivo;
        }
    }
    return 0;
}

/* FINAL DAS FUNCOES LOCAIS DA BIBLIOTECA */


/* cria um conjunto e retorna seu endereço se a operacao foi bem sucedida e 0 caso contrario */
/* o tamanho máximo do conjunto eh max */
conjunto_t * cria_conjunto (int max){
    if(max <1)
        return 0;
    conjunto_t *novo_conjunto;
    novo_conjunto = malloc(sizeof(conjunto_t));
    if(novo_conjunto == NULL){
        return 0;
    } else {
        novo_conjunto->v = (int *) malloc(sizeof(int) * (max + 1));
        if(novo_conjunto->v == NULL){
            free(novo_conjunto);
            return 0;
        }
        novo_conjunto->max = max;
        novo_conjunto->card = 0;
        return novo_conjunto;
    }
}

/* destroi o conjunto c liberando todo espaco previamente alocado a este conjunto */
void destroi_conjunto (conjunto_t *c){
    free(c->v);
    free(c);
}

/* retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario */
int contido (conjunto_t *c1, conjunto_t *c2){
    int i, valor;
    for(i = 0; i < c1->card; i++){
        valor = *(c1->v+i);
        if(pertence(valor, c2) == 0)
            return 0;
    }
    return 1;
}

/* retorna a cardinalidade do conjunto c */
int cardinalidade (conjunto_t *c){
    return c->card;
}

/* retorna 1 se o conjunto c eh vazio e 0 caso contrario   */
int eh_vazio (conjunto_t *c){
    if(cardinalidade(c) == 0)
        return 1;
    return 0;
}

/* retorna 1 se o elemento n pertence ao conjunto c e 0 caso contrario   */
int pertence (int n, conjunto_t *c){
    if(busca_binaria(n, c) == 1)
        return 1;
    return 0;
}

/* retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario */
int sao_iguais (conjunto_t *c1, conjunto_t *c2){
    int i, valorC1, valorC2;
    if(cardinalidade(c1) != cardinalidade(c2))
        return 0;
    for(i = 0; i < c1->card; i++){
        valorC1 = *(c1->v+i);
        valorC2 = *(c2->v+i);
        if(valorC1 != valorC2)
            return 0;
    }
    return 1;
}

/* retorna o endereco do conjunto diferenca entre c1 e c2, nesta ordem  */
/* retorna 0 se a operacao falhou                                       */
conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2){
    
    conjunto_t *diff;
    int i, valor;
    diff = cria_conjunto(c1->max + c2->max);
    if(diff == 0)
        return 0;

    for(i = 0;i < c1->card; i++){
        valor = *(c1->v+i);
        if(pertence(valor, c2) == 0)
            insere(valor, diff);
    }

    if(eh_vazio(diff) == 1){
        destroi_conjunto(diff);
        return 0;
    }
    return diff;
}

/* retorna o endereco do conjunto interseccao entre os conjuntos c1 e c2  */
/* retorna 0 se a operacao falhou                                         */
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2){

    conjunto_t *intersec;
    int i, valor;
    intersec = cria_conjunto(c1->max + c2->max);
    if(intersec == 0)
        return 0;

    for(i = 0;i < c1->card; i++){
        valor = *(c1->v+i);
        if(pertence(valor, c2) == 1)
            insere(valor, intersec);
    }

    for(i = 0;i < c2->card; i++){
        valor = *(c2->v+i);
        if(pertence(valor, c1) == 1)
            insere(valor, intersec);
    }


    if(eh_vazio(intersec) == 1){
        destroi_conjunto(intersec);
        return 0;
    }
    return intersec;
}

/* retorna o endereco do conjunto uniao entre os conjuntos c1 e c2  */
/* retorna 0 se a operacao falhou                                   */
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2){
    conjunto_t *uniao;
    int i;
    uniao = cria_conjunto(c1->max + c2->max);
    if(uniao == 0)
        return 0;
    for(i = 0; i < c1->card; i++){
        insere(*(c1->v+i), uniao);
    }
    for(i = 0; i < c2->card; i++){
        insere(*(c2->v+i), uniao);
    }

    if(eh_vazio(uniao) == 1){
        destroi_conjunto(uniao);
        return 0;
    }
    return uniao;
}

/* insere o elemento n no conjunto c caso ele nao exista                     */
/* retorna 1 se a operacao foi bem sucedida e retorna 0 se tente inserir     */
/* elemento ja existente (conjuntos nao tem repeticao) e -1 se nao ha espaco */
int insere (int n, conjunto_t *c){
    if(c->card == 0){
        *(c->v) = n;
        c->card++;
        return 1;
    } 
    if (c->card == c-> max)
        return -1;
    if(pertence(n, c) == 1)
        return 0;
    
    insere_ordenado(n, c);
    c->card++;
    return 1;

    
    
    
}

/* retira o elemento n do conjunto c caso ele exista */
/* retorna 1 se a operacao foi bem sucedida e retorna 0 se nao existe  */
int retira (int n, conjunto_t *c){
    if(busca_binaria(n, c) == 0){
        return 0;
    }
    int pos = encontra_pos(n, c);
    int i;
    for(i= pos; i<= c->card; i++){
        *(c->v+i-1) = *(c->v+i);
    }
    c->card--;
    return 1;
}

/* imprime os elementos do conjunto sempre em ordem crescente */
/* mesmo que a estrutura interna nao garanta isso             */
void imprime (conjunto_t *c){
    int i;
    for(i = 0; i < c->card-1; i++){
        printf("%d - ", *(c->v+i));
    }
    printf("%d\n\n", *(c->v+i));
}

