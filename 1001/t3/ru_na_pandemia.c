#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"
#include "liblista.h"
#include "libpilha.h"
#include "libru.h"


int main(){

    data_t *dados_ru;
    fila_t *fila_pessoas;
    lista_t *tickets_nao_usados;
    pilha_t *mascaras, *refeicoes;
    pessoa_t *pessoa, *todas_pessoas[MAX_PESSOAS];
    int qtde_mascaras, qtde_refeicoes, ticket;

    /*0. Inicialize a lista de dados*/
    dados_ru = cria_dados();

    /*1. Gere uma pilha de mascaras cuja quantidade deve ser definida por aleat(1,100) */
    aleat(1, 100, &qtde_mascaras);
    mascaras = pilha_cria(qtde_mascaras);
    enche_pilha(mascaras);

    /*2.  Gere uma pilha de refeicoes cuja quantidade deve ser definida por aleat(500,1000) */
    aleat(500, 1000, &qtde_refeicoes);
    refeicoes = pilha_cria(qtde_refeicoes);
    enche_pilha(refeicoes);
    
    /*3. Defina e gere uma estrutura de dados para representar um conjunto de 1000 (mil) pessoas */
    popula_conjunto(todas_pessoas);

    /*4.  Crie uma fila vazia de atendimentos (armazena os tickets das pessoas) */
    fila_pessoas = fila_cria();
    popula_fila(fila_pessoas);

    /*5.  Crie uma lista ligada simples vazia de tickets nao-atendidos */
    tickets_nao_usados = lista_cria();
    
    /* Enquanto houver refeicoes ou houver fila */
    while(qtde_refeicoes > 0 && fila_vazia(fila_pessoas) != 1){
        pessoa = proximo(fila_pessoas, todas_pessoas);
        ticket = pega_ticket(pessoa);
        /* Senao vacinada */
        if(eh_vacinado(pessoa) != 1){
            /* ticket e colocado em uma lista ligada simples de tickets nao-utilizados com politica de insercaao ordenada ascendente */
            insere_ticket(tickets_nao_usados, ticket);
        } else { /* Se vacinada */
            /* Se usa mascara */
            if(usa_mascara(pessoa)){
                if(saldo(pessoa) > 1.3){
                    /* Paga 1,30 */
                    compra_refeicao(pessoa, refeicoes);
                    /* Adiciona um contador no dado dinheiro_refeicoes*/
                    adiciona_contador(dados_ru, 0);
                    /* Ganha uma refeicao da pilha */
                }
                /* Senao */
                    /* Vai embora sem comer */
             } else {/* Se nao usa mascara */
                /* Se ainda houver mascaras*/
                if(tem_mascara(mascaras)){
                    /* Paga 2,50 em uma mascara */
                    if(saldo(pessoa) > 2.5){
                        compra_mascara(pessoa, mascaras);
                        /* Adiciona um contador no dado dinheiro_mascaras*/
                        adiciona_contador(dados_ru, 1);
                        /* Volta para o final da fila*/
                        volta_pra_fila(pessoa, fila_pessoas);
                    }
                } else{/* Se nao houver mascaras */
                    /* Coloca ticket na lista de nao utilizados */
                    insere_ticket(tickets_nao_usados, ticket);
                    /* Vai embora sem comer */
                }
            }
        }
    /* Fim do laco de repeticao */
    }

    /* Destruir fila de pessoas */
    fila_destroi(fila_pessoas);

    imprime_dados(dados_ru, tickets_nao_usados);

    lista_destroi(tickets_nao_usados);
    pilha_destroi(mascaras);
    pilha_destroi(refeicoes);
    pessoas_destroi(todas_pessoas);
    dados_destroi(dados_ru);

    /* Limpa tudo para finalizar o programa*/
    return 0;
}