#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000 //100,000

int main(int argc, char* argv[]){
    int **matrix = (int **)malloc(sizeof(int *) * SIZE);
    for(int i = 0; i < SIZE; i++){
        matrix[i] = (int *)malloc(sizeof(int) * SIZE);
    }
    int cont = 0;
    if(atoi(argv[1]) == 0){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                    matrix[i][j] = cont;
                    cont++;
            }
        }
    } else {
        for(int j = 0; j < SIZE; j++){
            for(int i = 0; i < SIZE; i++){
                    matrix[i][j] = cont;
                    cont++;
            }
        }
    }

    return 0;
}