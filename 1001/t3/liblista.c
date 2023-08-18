#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

/* ********** Funcoes internas ********** */
nodo_l_t* novo_nodo(int elemento){
    nodo_l_t* new_node;

    if((new_node = (nodo_l_t *) malloc(sizeof(nodo_l_t)))){
        new_node->elemento = elemento;
        new_node->prox = NULL;
        return new_node;
    }
    return NULL;
}

void troca(nodo_l_t *a, nodo_l_t *b){
    int tmp = a->elemento;
    a->elemento = b->elemento;
    b->elemento = tmp;
}

void ordena_lista(lista_t *l){
    int trocado;
    nodo_l_t *ptr1;
    nodo_l_t *lptr = NULL;

    do{
        trocado = 0;
        ptr1 = l->ini;
        while(ptr1->prox != lptr){
            if(ptr1->elemento > ptr1->prox->elemento){
                troca(ptr1, ptr1->prox);
                trocado = 1;
            }
            ptr1 = ptr1->prox;
        }
        lptr = ptr1;
    } while(trocado == 1);
}

int eh_primeiro(lista_t *l, int elemento){
    if(l->ini->elemento > elemento)
        return 1;
    return 0;
}

int eh_ultimo(lista_t *l, int elemento){
    nodo_l_t *ultimo;
    ultimo = l->ini;
    while(ultimo->prox)
        ultimo = ultimo->prox;
    if(ultimo->elemento < elemento)
        return 1;
    return 0;
}

/* ********** Funcoes internas ********** */


/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
*/
lista_t* lista_cria (){
    lista_t *nova_lista;
    if((nova_lista = (lista_t *) malloc(sizeof(lista_t)))){
        nova_lista->ini = NULL;
        nova_lista-> tamanho = 0;
        return nova_lista;
    }
    return NULL;
}

/*
 * Remove todos os elementos da lista, libera espaco e retorna NULL.
*/
lista_t* lista_destroi (lista_t* l){
    int elemento;
    while(lista_tamanho(l) != 0){        
        lista_retira_inicio(l, &elemento);
    }
    free(l);
    return NULL;
}

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
*/
int lista_vazia (lista_t* l){
    if(l->tamanho == 0)
        return 1;
    return 0;
}

/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
*/
int lista_tamanho (lista_t* l){
    return l->tamanho;
}

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_insere_inicio (lista_t* l, int elemento){
        nodo_l_t *nodo;
    if((nodo = novo_nodo(elemento))){
        if(lista_vazia(l) == 1)
            l->ini = nodo;
        else
            nodo->prox = l->ini;
        l->ini = nodo;
        l->tamanho++;
        return 1;
    }
    return 0;
}

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_insere_fim (lista_t* l, int elemento){
    nodo_l_t *nodo, *atual;
    
    if((nodo = novo_nodo(elemento))){
        if(lista_vazia(l) == 1)
            l->ini = nodo;
        else{
            atual = l->ini;
            while(atual->prox)
                atual = atual->prox;
            atual->prox = nodo;
        }
        l->tamanho++;
        return 1;
    }
    return 0;
}

/*
 * Insere o elemento na lista garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_insere_ordenado (lista_t* l, int elemento){
    
    nodo_l_t *nodo, *atual;
    
    if((nodo = novo_nodo(elemento))){
        
        if(lista_vazia(l) == 1){
            l->ini = nodo;
            l->tamanho++;
            return 1;
        }

        if(lista_tamanho(l) == 1){
            if(elemento > l->ini->elemento)
                l->ini->prox = nodo;
            else{
                nodo->prox = l->ini;
                l->ini = nodo;
            }
            l->tamanho++;
            return 1;
        } else {
            ordena_lista(l);
            if(eh_ultimo(l, elemento) == 1){
                atual = l->ini;
                while(atual->prox)
                    atual = atual->prox;
                atual->prox = nodo;
                l->tamanho++;
                return 1;
            } else if(eh_primeiro(l, elemento) == 1){
                nodo->prox = l->ini;
                l->ini = nodo;
                l->tamanho++;
                return 1;
            }
            atual = l->ini;
            while(atual->prox->elemento < elemento)
                atual = atual->prox;
            nodo->prox = atual->prox;
            atual->prox = nodo;

        }
        l->tamanho++;
        return 1;
    }
    return 0;
}

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_retira_inicio (lista_t* l, int* elemento){
    if(lista_vazia(l) == 1)
        return 0;
        
    nodo_l_t *nodo;
    *elemento = l->ini->elemento;
    nodo = l->ini;
    l->ini = nodo->prox;
    free(nodo);
    l->tamanho--;
    return 1;
    
}

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_retira_fim (lista_t* l, int* elemento){
        if(lista_vazia(l) == 1)
            return 0;
        nodo_l_t *nodo, *atual;
        atual = l->ini;
        if(lista_tamanho(l) > 1){
        while(atual->prox->prox)
            atual = atual->prox;
        nodo = atual->prox;
        *elemento = nodo->elemento;
        atual->prox = NULL;
        } else {
            nodo = atual;
            l->ini = NULL;
        }
        free(nodo);
        l->tamanho--;

        return 1;
}

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
*/
int lista_retira_elemento (lista_t *l, int *elemento){
    if((lista_pertence(l, *elemento) == 0) || (lista_vazia(l) == 1))
        return 0;
    nodo_l_t *nodo, *atual;
    atual = l->ini;
    if(lista_tamanho(l) == 1) {
        nodo = atual;
        l->ini = NULL;
    } else {
        while(atual->prox->elemento != *elemento)
            atual = atual->prox;
        nodo = atual->prox;
        atual->prox = nodo->prox;
    }
    free(nodo);
    l->tamanho--;

    return 1;
}

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
*/
int lista_pertence (lista_t* l, int elemento){
    nodo_l_t *atual;
    atual = l->ini;
    while(atual){
        if(atual->elemento == elemento)
            return 1;
        atual = atual->prox;
    }
    return 0;
}

/*
 * Imprime a lista, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a lista estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD lista.
*/
void lista_imprime (lista_t* l){
    if(lista_vazia(l) == 1)
        return;
    
    nodo_l_t *atual;
    atual = l->ini;
    while(atual->prox){
        printf("%d ", atual->elemento);
        atual = atual->prox;
    }
    printf("%d ", atual->elemento);
}
