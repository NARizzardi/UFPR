#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libpilha.h"

/* Funcao do programa, nao da biblioteca que retorna o valor referente ao caracter inserido caso seja valido ou 0 caso invalido */
int valid_char(char c){
    /* Valores positivos para caracteres de abertura */
    /* Valores negativos para caracteres de fechamento */
    
    switch (c){
        case '(':
            return 1;
            break;
        
        case '[':
            return 2;
            break;
        
        case '{':
            return 3;
            break;
        
        case ')':
            return -1;
            break;
        
        case ']':
            return -2;
            break;
        
        case '}':
            return -3;
            break;
        
        default:
            return 0;
            break;
    }
    
}

int main(){
    
    /* Inicializacao das variaveis */
    pilha_t *pilha;
    char *entrada;
    int pos, valor;
    
    /* Inicializacao da pilha */
    pilha = inicializa_pilha();

    /* Alocacao de memoria para a entrada */
    entrada = (char *)malloc((MAX+1) *sizeof(char));
    
    /* Leitura da entrada*/
    fgets(entrada, (MAX+1)*sizeof(entrada), stdin);

    /* Valor inicial par comecar a iteracao da string */
    pos = 0;
    valor = valid_char(entrada[pos]);

    /* Iteracao por toda a string */
    while(pos < strlen(entrada)-1){
        if(valor > 0 ){ /* Se o char for de abertura apenas empilha o valor */
            empilha(valor, pilha);
        } else if(valor < 0){ /* Se o char for de fechamento tenta desempilhar o valor */
            if(desempilha(valor, pilha) == 0){ /* Se nao foi possivel desempilhar o valor ja encerra o codigo e da a saida de erro */
                printf("0\n");
                free(entrada);
                free(pilha->array);
                free(pilha);
                return 0;
            }    
        }
        pos++;
        valor = valid_char(entrada[pos]);
    }

    /* A funcao vazia() ja retorna a saida esperada da funcao */
    printf("%d\n",vazia(pilha));

    /* Liberacao da memoria alocada pelo programa */
    free(entrada);
    free(pilha->array);
    free(pilha);
    return 0;
}