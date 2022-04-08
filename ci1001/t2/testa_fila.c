#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

int main() {
    fila_t *fila1, *fila2; /* Declaração de 2 filas para teste */
    int elemento; /* Variavel que recebe os elementos removidos das filas */
    int count; /* contador para os loops */

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Testando a criacao das filas..\n");
    printf("\n");

    fila1 = fila_cria ();
    printf("O endereço da primeira fila eh: %p\n", &fila1);
    fila2 = fila_cria ();
    printf("O endereço da primeira fila eh: %p\n", &fila2);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inserindo elementos nas filas...\n");
    printf("\n");

    for (count = 1; count <= 6; count++) {
        if (queue (fila1, count*2)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d foi inserido corretamente na fila 1, o tamanho atual da fila é: %d\n", count*2, fila_tamanho (fila1));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da fila 1 é: %d\n", count*2, fila_tamanho (fila1));
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 6; count++) {
        if (queue (fila2, count*3)) /* inserindo numeros multiplos de 3 */
            printf("O numero %d foi inserido corretamente na fila 2, o tamanho atual da fila é: %d\n", count*3, fila_tamanho (fila2));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da fila 2 é: %d\n", count*3, fila_tamanho (fila2));
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Retirando elementos das filas...\n");
    printf("\n");

    for (count = 1; count <= 7; count++) {
        if (dequeue (fila1, &elemento)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido da fila 1! O tamanhao da fila eh: %d\n", elemento, fila_tamanho (fila1));
        else printf("Nao foi possivel remover o numero, fila 1 zerada\n");
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 7; count++) {
        if (dequeue (fila2, &elemento)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido da fila 2! O tamanhao da fila eh: %d\n", elemento, fila_tamanho (fila2));
        else printf("Nao foi possivel remover o numero, fila 2 zerada\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Preenchendo as filas novamente...\n");
    printf("\n");

    for (count = 1; count <= 6; count++) {
        if (queue (fila1, count*2)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d foi inserido corretamente na fila 1, o tamanho atual da fila é: %d\n", count*2, fila_tamanho (fila1));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da fila 1 é: %d\n", count*2, fila_tamanho (fila1));
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 6; count++) {
        if (queue (fila2, count*3)) /* inserindo numeros multiplos de 3 */
            printf("O numero %d foi inserido corretamente na fila 2, o tamanho atual da fila é: %d\n", count*3, fila_tamanho (fila2));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da fila 2 é: %d\n", count*3, fila_tamanho (fila2));
    }

    printf("Liberando a memoria utilizada pela fila 1...\n");
    fila1 = fila_destroi (fila1);
    printf("fila 1 corretamente liberada, apontando para: %p\n", fila1);
    printf("Liberando a memoria utilizada pela fila 2...\n");
    fila2 = fila_destroi (fila2);
    printf("fila 2 corretamente liberada, apontando para: %p\n", fila2);

    printf("\n");
    printf("FIM DO TESTE\n");
    printf("------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------\n");
    return 0;
}