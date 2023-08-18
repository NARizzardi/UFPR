/* 
 * Programa para testar balanceamento de expressoes com parenteses
 * Usa uma pilha de char conforme definido em libpilha.h
 * Feito por Marcos Castilho em 30/03/2022
 * Refeito por Marcos Castilho em 01/04/2022 apos criticas severas
 * e justas dos outros profs e alunos da turma na aula do dia 31/03/2022.
 * A pior critica foi a do uso do scanf para ler a string e o main
 * que tinha ficado muito longo. A culpa foi totalmente minha, embora
 * o scanf eu usei teatralmente pois sabia que o Gregio iria criticar. :-)
*/

#include <string.h>
#include <stdlib.h> /* necessaria para usar o exit, que ficou feio... */

/*
 * status de saida
 *
0: sucesso!
1: Falha na alocacao da pilha
2: Pilha cheia
3: Pilha ficou vazia antes da hora
4: Tipo dos parenteses nao bate
5: caracter invalido
6: Expressao acabou sem fechar algum parenteses
 *
*/

#include <stdio.h>
#include "libpilha.h"

/* retorna 1 se o parenteses eh do tipo abre, 0 caso contrario */
int eh_tipo_abre (char c)
{
    /* 
     * Eu teria que pensar mais para um código que tivesse mais tipos
     * de abre "parenteses", como foram so 3 eu fiz assim.
     * pensei em usar o tipo SET do pascal, mas nao achei um 
     * equivalente em C para fazer o mesmo em "alto nivel".
     * Este monte de if-the-else me parere ruim em todo caso.
     */
    if ((c == '(') || (c == '{') || (c == '['))
        return 1;
    return 0;
}

/* retorna 1 se o parenteses eh do tipo fecha, 0 caso contrario */
int eh_tipo_fecha (char c)
{
    /* vide comentarios na funcao eh_tipo_abre */
    if ((c == ')') || (c == '}') || (c == ']'))
        return 1;
    return 0;
}

/* retorna 1 se tipo do parentes fechado casa com o aberto, 0 caso contrario */
int abre_fecha_compativeis (char topo, char c)
{
    /* 
     * Tenho certeza que tem jeito melhor de fazer isso, mas na pressa
     * fiz assim... Acho que a versao do Albini eh melhor, mas talvez
     * tenha jeito melhor ainda do que a do Albini
     * O problema eh sempre o mesmo, se tiver mais tipos de "abre" e
     * "fecha" meu program eh pesssimo.
    */
    if ((topo == '(') && (c == ')'))
        return 1;
    else if ((topo == '{') && (c == '}'))
        return 1;
    else if ((topo == '[') && (c == ']'))
        return 1;

    return 0;
}

/* imprime msg na tela, destroi a pilha e retorna status de saida cod_aborta */
void aborta (struct pilha *p, char *msg, int cod_aborta)
{
    /* Como eu me preocupei em retornar os exit_status para cada erro
     * eu precisei desta funcao para nao repetir codigo no main.
     * Eu precisaria de mais tempo para pensar em um jeito melhor.
     * Acho que eu extrapolei o enunciado que tinha que responder
     * "sim" ou "nao", mas eu exagerei e o codigo acabou complicado
     * e teve a necessidade disso.
     * Tabmem como disse o Bona, o uso do exit fora do main me parece
     * ruim.
*/
    printf ("Erro %s\n", msg);
    destroi_pilha (p);
    exit (cod_aborta);
}

int main (void)
{
    struct pilha *p;
    char *exp;
    char c, topo;
    int i;

    /* eu fiz a entrada com scanf para dar a oportunidade do Gregio
     * me criticar, mas tambem porque queria saber porque nao usar.
     * Os outros tres professores tem muito mais experiencia em C 
     * do que eu.
     * Depois das broncas, eu resolvi usar o fgets, mas sei que
     * ainda estou sujeito a criticas.
     * O Gregio, que eh especialista em seguranca, fez BEM 
     * diferente. Nao sei se gosto da solucao dele para prog1,
     * mas com certeza deve fazer diferenca para frente.
    */
    /* le a entrada e troca \n por \0 */
    fgets (exp, MAX, stdin) ;
    exp[strcspn (exp, "\n")] = '\0' ;

    /* 
     * O restante do codigo eu fiz algumas alteracoes para evitar
     * linhas de codigo adicionais, troquei os then-elses por 
     * algo como "elses-then", isto eh, neguei a condicao e inverti
     * os codigos com relacao ao programa original, isto economizou
     * algumas linhas de codigo e alguns abre e fecha chaves
    */
    if (! (p = inicializa_pilha (MAX)))
        aborta (p, "Falha na alocacao da pilha", 1);

    /* aqui eu troquei meu while por um for, nada relevante... */
    for (i = 0; (c = exp[i]) != '\0'; i++)
    {
        if (! eh_tipo_abre (c))
        {
            if (! eh_tipo_fecha (c))
                aborta (p, "caracter invalido!", 5);
            if (pilha_vazia (p))
                aborta (p, "Pilha ficou vazia antes da hora!", 3);

            /* se nao deu aborta entao tem que ver se abre casa com fecha */
            topo = pop (p);
            if (! abre_fecha_compativeis (topo, c))
                aborta (p, "Tipo dos parenteses nao bate!", 4);
        }
        else
            if (! push (p, c))
                aborta (p, "Pilha cheia", 2);
    }

    /* se chegou aqui so falta testar se a pilha esta vazia ou nao 
     * se estiver eh porque deu certo, senao faltou fechar parenteses */
    if (pilha_vazia (p))
    {
        printf ("Parenteses balanceados!!!\n");
        return 0;
    }

    aborta (p, "Expressao acabou sem fechar algum parenteses!!!", 6);
}


/*
 * Mas o importante a obervar, independemente do codigo dos 4 profs,
 * eh que todos usaram corretamente a libpilha, nenhum de nos
 * acessa o vetor diretamente, todos usamos as chamadas das funcoes:
 * push, pop, cria, destroi, pilha_vazia, etc.
 *
 * Depois, todos nos usamos boas praticas de programacao, os nossos 
 * libpilha.h sao praticamente os mesmos, o uso de comentarios foi
 * sempre moderado e assim por diante.
 *
 * Os estilos de programacao sao diferentes, mas os codigos sao
 * bastante bons, todos eles, em geral. Pode fazer melhor? Sim
 * quase sempre pode se fazer melhor.
 *
 * Finalmente, como eu ja disse, eu exagerei sobre o enunciado,
 * o codigo para responder "sim" ou "nao" poderia ficar mais
 * simples, talvez conforme os codigos dos outros tres profs
 * que se mantiveram no enunciado, eu que extrapolei porque
 * queria mostrar como fazer status de saida.
*/