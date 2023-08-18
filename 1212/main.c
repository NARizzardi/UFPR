#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

int buscaBinaria(int* vetor, int ini, int fim, int valor){
    if(fim < ini){
        return -1;
    }
    int pos = (fim + ini) / 2;
    if(valor > vetor[pos]){
        return buscaBinaria(vetor, pos + 1, fim, valor);
    } else if(valor < vetor[pos]){
        return buscaBinaria(vetor, ini, pos, valor);
    } else {
        return pos;
    }

}

int main(int argc, char* argv[]){ 
    int *vetor; 
    vetor = (int *)malloc(SIZE * sizeof(int)); 
    int value = 0;
    for(int i = 0; i < SIZE; i ++){ 
        vetor[i] = value;
        value ++;
    }
    int pos = buscaBinaria(vetor, 0, SIZE-1, atoi(argv[1]));
    printf("pos: %d", pos);
    free(vetor);
    return 0; 
} 
