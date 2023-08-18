#include <stdio.h>
#include <stdlib.h>
#include "hashfunctions.h"

int main(){
    int hashtable[COL][M];
    array_t *vetor; 
    vetor = new_arrayt();
    int value; char action;
    init_table(hashtable);
    fscanf(stdin, "%c %d", &action, &value);
    getc(stdin);
    while (!feof(stdin)) {
        if (action == 'i') {
            include_key(value, hashtable);
            insere_valor(value, vetor);
        } else {
            remove_key(value, hashtable);
            remove_valor(value, vetor);
        }
        fscanf(stdin, "%c %d", &action, &value);
        getc(stdin);
    }
    print_table(vetor, hashtable);
    free vetor;
    return 0;
}
