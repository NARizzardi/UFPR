#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

int main() {

    /* Declaracao das variaveis */
    fila_t* fila_1;
    fila_t* fila_2;
    int elemento;
    int index;
    /* Criacao das filas */
    fila_1 = fila_cria();
    fila_2 = fila_cria();

    printf("/* Imprime o tamanho das filas para verificar que foram criadas com sucesso */");
    printf("\nfila: 1 tamanho: %d\n", fila_tamanho(fila_1));
    printf("fila: 2 tamanho: %d\n", fila_tamanho(fila_2));

    printf("\n\n/* Insere elementos nas filas */\n");
    for(index = 0; index < 15; index++){
        printf("Inserindo elemento: %d na fila: 1\n", index);
        if(queue(fila_1, index) == 0)
            printf("erro ao inserir\n");
    }
    printf("\n\n");
    for(index = 15; index > 0; index--){
        printf("Inserindo elemento: %d na fila: 2\n", index);
        if(queue(fila_2, index) == 0)
            printf("erro ao inserir\n");
    }   
    printf("\n\n/* Imprime as filas apos inserir os elementos */\n");
    fila_imprime(fila_1);     
    printf("\n");
    fila_imprime(fila_2);

    printf("\n\n/* Removendo o primeiro elemento de cada fila */\n");
    if(dequeue(fila_2, &elemento) == 1)
        printf("elemento: %d removido da fila 2\n", elemento);
    if(dequeue(fila_1, &elemento) == 1)
        printf("elemento: %d removido da fila 1", elemento);

    printf("\n\n/* Final do programa liberando espaços de memoria*/\n");
    fila_destroi(fila_1);
    fila_destroi(fila_2);
    return 0;
}