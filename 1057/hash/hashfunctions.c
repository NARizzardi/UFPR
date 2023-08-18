#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashfunctions.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Funcoes Internas ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int hash_t1 (int key){
    return key % M;
}

int hash_t2 (int key){
    int pos_h2;
    pos_h2 = (int) floor(M * (key * 0.9 - floor(key * 0.9)));
    
    return pos_h2;
}

int find_key (int key, int ht[COL][M]) {
    int h1 = hash_t1(key);
    
    if (ht[0][h1] == -1)
        return -1;
    else if(ht[0][h1] == key)
        return h1;
    else  
        return hash_t2(key);
    
}
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~ Fim das Funcoes Internas ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

array_t *new_arrayt(){
    array_t *newarray;
    
    newarray = (array_t *) malloc(sizeof(array_t));
    
    newarray->tam = 0;

    return newarray;
}

void insere_valor(int valor, array_t *vetor){
    int pos = vetor->tam;
    if(vetor->tam != 00){
            while((valor < vetor->entradas[pos-1]) && (pos > 0)){
                vetor->entradas[pos] = vetor->entradas[pos-1];
                pos--;
            }
    }
    vetor->entradas[pos] = valor;
    vetor->tam++;
}

void remove_valor(int valor, array_t *vetor){
    int i, pos = 0;
    
    while((valor != vetor->entradas[pos]) && (pos !=vetor->tam))
        pos++;

    for(i = pos; i< vetor->tam; i++){
        vetor->entradas[i] = vetor->entradas[i+1];
    }
    vetor->tam--;
}

void init_table(int ht[COL][M]){
    int i, j;
    for(j = 0; j < COL; j++){
        for(i = 0; i < M; i++){
            ht[j][i] = -1;
        }   
    }
}

void include_key(int key, int ht[COL][M] ) {
    int h1 = hash_t1(key);
    if(ht[0][h1] == -1 || ht[0][h1] == -2){
        ht[0][h1] = key;
        return;
    } else if(ht[0][h1] == key)
        return;

    int h2 = hash_t2(ht[0][h1]);
    ht[1][h2] = ht[0][h1];
    ht[0][h1] = key;        
}

int remove_key(int key, int ht[COL][M]) { 
    int pos = find_key(key, ht);
    if(pos == -1)
        return 0;

    if(ht[1][pos] == key){
        ht[1][pos] = -1;
        return 1;
    }
     
    ht[0][pos] = -2;
    return 1;
    
} 

void print_table(array_t *vetor, int ht[COL][M]){
    int i;
    for(i = 0; i < vetor->tam; i++){
        int pos = find_key(vetor->entradas[i], ht);
        if(ht[0][pos] == vetor->entradas[i])
            printf("%d,T1,%d\n", vetor->entradas[i], pos);
        else 
            printf("%d,T2,%d\n", vetor->entradas[i], pos);
    }
}