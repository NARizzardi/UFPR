#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libpilha.h"
#define MAX 200 /* constante para definir o tamanho maximo da entrada*/

/* Funcao para verificar se o caracter eh de abertura */
int eh_abertura(char c){
    if(c == '(' || c == '[' || c == '{')
        return 1;

    return 0;
}

int main(){
    
    /* Inicializacao das variaveis */
    pilha_t *pilha;
    char *entrada;
    char valor;
    int pos;
    
    /* Inicializacao da pilha */
    pilha = inicializa_pilha();

    /* Alocacao de memoria para a entrada */
    entrada = (char *)malloc((MAX+1) *sizeof(char));
    
    /* Leitura da entrada*/
    fgets(entrada, (MAX+1)*sizeof(entrada), stdin);

       
    /* Iteracao por toda a string */
    for(pos = 0; pos < strlen(entrada)-1; pos++){
        valor = entrada[pos];
        if(eh_abertura(valor) == 1){ /* Se o char for de abertura apenas empilha o valor */
            empilha(valor, pilha);
        } else{ /* Se o char for de fechamento tenta desempilhar o valor */
            if(desempilha(valor, pilha) == 0){ /* Se nao foi possivel desempilhar o valor ja encerra o codigo e da a saida de erro */
                printf("0\n");
                free(entrada);
                free(pilha->array);
                free(pilha);
                return 0;
            }    
        }
        printf("\n");
    }

    /* A funcao vazia() ja retorna a saida esperada da funcao */
    printf("%d\n",vazia(pilha));

    /* Liberacao da memoria alocada pelo programa */
    free(entrada);
    free(pilha->array);
    free(pilha);
    return 0;
}