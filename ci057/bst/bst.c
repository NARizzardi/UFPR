#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

bstree_t *inicializa_bst(){
    bstree_t *new_tree;
    if((new_tree = (bstree_t *) malloc(sizeof(bstree_t)))){
        new_tree->altura = 0;
        new_tree->root = NULL;
        return new_tree;
    }
    return NULL;
}

tnode_t *cria_nodo(int valor){
    tnode_t *nodo;
    if((nodo = (tnode_t *) malloc(sizeof(tnode_t)))){
        nodo->father = NULL;
        nodo->left = NULL;
        nodo->right = NULL;
        nodo->value = valor;
        return nodo;
    }
    return NULL;
}

tnode_t *inclusao_raiz(){}

void imprime_nodo(){}

void em_ordem(){}

void pre_ordem(){}

void pos_ordem(){}

int conta_nodos(){}

int altura(){}

tnode_t *busca_binaria(){}

tnode_t *minimo(){}

tnode_t *sucessor(){}

tnode_t *maximo(){}

tnode_t *antecessor(){}

void ajusta_no_pai(){}

tnode_t *exclusao(){}