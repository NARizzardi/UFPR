#include <stdio.h>
#include <stdlib.h>
#include "hashfunctions.h"


int main(){
    int hashtable[COL][M];
    entries_t *entradas; 
    entradas = cria_entrada_list();
    int table;
    int value; char action;
    init_table(hashtable);
    fscanf(stdin, "%c %d", &action, &value);
    getc(stdin);
    while (!feof(stdin)) {
        if (action == 'i') {
            table = include_key(value, hashtable );
            if(table != 0)
                insere_valor(value, entradas, table);
        } else {
            remove_key(value, hashtable);
            remove_valor(value, entradas);
        }
        fscanf(stdin, "%c %d", &action, &value);
        getc(stdin);
    }
    print_table(entradas, hashtable);
    free(entradas);
    return 0;
}
