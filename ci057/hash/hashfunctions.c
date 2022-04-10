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

entry_t *cria_entrada(int valor, int table){
    entry_t *nova_entrada;

    nova_entrada = (entry_t *) malloc(sizeof(entry_t));
    
    nova_entrada->key = valor;
    nova_entrada->table = table;

    return nova_entrada;
}
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~ Fim das Funcoes Internas ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

entries_t *cria_entrada_list(){
    entries_t *nova_lista;
    nova_lista = (entries_t *) malloc(sizeof(entries_t));
    nova_lista->tam = 0;
    
    return nova_lista;
}

void insere_valor(int valor, entries_t *entradas, int table){
    int i, pos;
    entry_t *nova_entrada;
    nova_entrada = cria_entrada(valor, table);
    if(entradas->tam == 0) {
        entradas->entrada_list[0] = nova_entrada;
        entradas->tam++;
        return;
    }

    pos = 0;
    while(valor > entradas->entrada_list[pos]->key && pos < entradas->tam-1){
        pos++;
    }
    pos++;
    for(i = entradas->tam; i >= pos+1; i--){
        entradas->entrada_list[i] = entradas->entrada_list[i-1];
    }   
    
    entradas->entrada_list[pos] = nova_entrada;
    entradas->tam++;
}

void remove_valor(int valor, entries_t *entradas){
    int i, pos;
    
    pos = 0;
    while(entradas->entrada_list[pos]->key != valor){
        pos++;
    }

    for(i = pos; i < entradas->tam - 1; i++)
        entradas->entrada_list[i] = entradas->entrada_list[i+1];
    
    entradas->tam--;
}

void init_table(int ht[COL][M]){
    int i, j;
    for(j = 0; j < COL; j++){
        for(i = 0; i < M; i++){
            ht[j][i] = -1;
        }   
    }
}

int include_key(int key, int ht[COL][M] ) {
    int h1 = hash_t1(key);
    if(ht[0][h1] == -1 || ht[0][h1] == -2){
        ht[0][h1] = key;
        return 1;
    } else if(ht[0][h1] == key)
        return 0;

    int h2 = hash_t2(ht[0][h1]);
    ht[1][h2] = ht[0][h1];
    ht[0][h1] = key;
    return 2;
        
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

void print_table(entries_t *entradas, int ht[COL][M]){
    int i;
    for(i = 0 ; i <  entradas->tam; i++){
        int pos = find_key(entradas->entrada_list[i]->key, ht);
        printf("%d,T%d,%d\n", entradas->entrada_list[i]->key, entradas->entrada_list[i]->table, pos);
    }
}