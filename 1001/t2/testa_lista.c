#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

int main(){

    lista_t* lista_1;
    lista_t* lista_2;
    int i, elemento, remocao;
    printf("/* Cria as listas */\n");
    lista_1 = lista_cria();
    lista_2 = lista_cria();

    printf("/* Imprime o tamanho das listas para verificar que foram criadas com sucesso */");
    printf("\nlista 1 tamanho: %d\n", lista_tamanho(lista_1));
    printf("lista 2 tamanho: %d\n\n", lista_tamanho(lista_2));

    printf("/* Inserindo elementos no inicio da lista 1 e no fim da lista 2 */\n");
    for(i = 0; i < 3; i++){
        printf("insere %d no inicio\n", i);
        lista_insere_inicio(lista_1, i);
        printf("insere %d no fim\n\n", i);
        lista_insere_fim(lista_2, i);
    }

    printf("/* Primeira impressao das listas */\n");
    printf("lista 1: ");
    lista_imprime(lista_1);
    printf("\n");
    printf("lista 2: ");
    lista_imprime(lista_2);
    printf("\n\n");

    printf("/* Inserindo elementos no inicio da lista 2 e no fim da lista 1 */\n");
    for(i = 7; i < 10; i++){
        printf("insere %d no fim\n", i);
        lista_insere_fim(lista_1, i);
        printf("insere %d no inicio\n\n", i);
        lista_insere_inicio(lista_2, i);
    }
    printf("lista 1: ");
    lista_imprime(lista_1);
    printf("\n");
    printf("lista 2: ");
    lista_imprime(lista_2);
    printf("\n\n");


    printf("/* Testando remocoes */\n");
    printf("/* Removendo um elemento do fim de cada lista */\n");
    if(lista_retira_fim(lista_1, &elemento) == 1)
        printf("Remocao do elemento: %d foi bem sucessida\n", elemento);
    if(lista_retira_fim(lista_2, &elemento) == 1)
        printf("Remocao do elemento: %d foi bem sucessida\n", elemento);

    printf("lista 1: ");
    lista_imprime(lista_1);
    printf("\n");
    printf("lista 2: ");
    lista_imprime(lista_2);
    printf("\n\n");

    printf("/* Removendo um elemento do inicio de cada lista */\n");
    if(lista_retira_inicio(lista_1, &elemento) == 1)
        printf("Remocao do elemento: %d foi bem sucessida\n", elemento);
    if(lista_retira_inicio(lista_2, &elemento) == 1)
        printf("Remocao do elemento: %d foi bem sucessida\n", elemento);

    printf("lista 1: ");
    lista_imprime(lista_1);
    printf("\n");
    printf("lista 2: ");
    lista_imprime(lista_2);
    printf("\n\n");

    printf("/* Removendo um elemento especifico de cada lista */\n");
    remocao = 7;
    if(lista_retira_elemento(lista_1, &remocao) == 1)
        printf("Remocao do elemento: %d da lista 1 foi bem sucessida\n", remocao);
    else
        printf("Remocao do elemento: %d da lista 1 nao foi bem sucessida\n", remocao);

    remocao = 6;
    if(lista_retira_elemento(lista_2, &remocao) == 1)
        printf("Remocao do elemento: %d da lista 2 foi bem sucessida\n", remocao);
    else
        printf("Remocao do elemento: %d da lista 2 nao foi bem sucessida\n", remocao);
        

    printf("lista 1: ");
    lista_imprime(lista_1);
    printf("\n");
    printf("lista 2: ");
    lista_imprime(lista_2);
    printf("\n\n");

    printf("/* Trabalhando agora com ordenacao da lista a partir da insercao ordenada */\n");
    if(lista_insere_ordenado(lista_1, 9) == 1)
        printf("O elemento 9 foi inserido com sucesso na lista 1 apos ela ter sido ordenada\n");
    printf("lista 1: ");
    lista_imprime(lista_1);
    printf("\n\n");

    if(lista_insere_ordenado(lista_2, 6) == 1)
        printf("O elemento 6 foi inserido com sucesso na lista 2 apos ela ter sido ordenada\n");
    printf("lista 2: ");
    lista_imprime(lista_2);
    printf("\n\n");


    printf("/* Encerra o programa liberando o espaco das listas */\n");
    lista_1 = lista_destroi(lista_1);
    lista_2 = lista_destroi(lista_2);

    
    return 0;
}