#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bound-lib.h"

#define ATORES m
#define PERSONAGENS n
#define GRUPOS l
#define VALOR v

extern int OptCusto, *OptX, numDecidas;

/*
    Nas matrizes criadas, cada linha é um ator
    0 - nao pode interpretar ou nao faz parte do grupo
    1 - pode interpretar ou faz parte do grupo
     P E R S O N A G E N S / GR U P O S
    A
    T
    O
    R
    E
    S
*/

void imprimeMatriz(char *titulo, int **matriz, int linhas, int colunas)
{
    printf("%s:\n", titulo);
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    clock_t inicio, fim;

    /*
    l (|S| grupos),
    m (|A| atores),
    n (|P| personagens),
    */
    int l, m, n, v;
    scanf("%d %d %d", &l, &m, &n);

    int *custoAtor = malloc(ATORES * sizeof(int));

    // ator - personagem
    int **matrizAtorPersonagem = malloc(ATORES * sizeof(int *) + ATORES * PERSONAGENS * sizeof(int));
    matrizAtorPersonagem[0] = (int *)(matrizAtorPersonagem + ATORES);
    for (int i = 1; i < ATORES; ++i)
        matrizAtorPersonagem[i] = matrizAtorPersonagem[0] + (i * PERSONAGENS);

    // ator-grupo
    int **matrizAtorGrupo = malloc(ATORES * sizeof(int *) + ATORES * GRUPOS * sizeof(int));
    matrizAtorGrupo[0] = (int *)(matrizAtorGrupo + ATORES);
    for (int i = 1; i < ATORES; ++i)
        matrizAtorGrupo[i] = matrizAtorGrupo[0] + (i * GRUPOS);

    for (int i = 0; i < ATORES; ++i)
    {
        for (int j = 0; j < PERSONAGENS; ++j)
            matrizAtorPersonagem[i][j] = 0;
        for (int j = 0; j < GRUPOS; ++j)
            matrizAtorGrupo[i][j] = 0;
    }

    OptCusto = -1;
    OptX = malloc(n * sizeof(int));
    int *alocacaoPersonagem = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        alocacaoPersonagem[i] = -1;

    // leitura
    /*
        v (valor cobrado pelo ator),
        r (número de personagens que o ator pode interpretar),
        e (numero de grupos da sociedade q ele faz parte)
    */
    for (int i = 0; i < ATORES; ++i)
    {
        int r, e;
        scanf("%d %d %d", &v, &r, &e);
        custoAtor[i] = v;

        // personagem que ator pode representa
        for (int j = 0; j < r; ++j)
        {
            int personagem;
            scanf("%d", &personagem);
            matrizAtorPersonagem[i][personagem - 1] = 1;
        }

        // grupos que ator faz parte
        for (int j = 0; j < e; ++j)
        {
            int grupo;
            scanf("%d", &grupo);
            matrizAtorGrupo[i][grupo - 1] = 1;
        }
    }

#ifdef DEBUG
    imprimeMatriz("Personagens que cada ator pode interpretar", matrizAtorPersonagem, ATORES, PERSONAGENS);
    printf("\n");
    imprimeMatriz("Grupo que cada ator faz parte", matrizAtorGrupo, ATORES, GRUPOS);
    printf("\n");

    for (int i = 0; i < ATORES; ++i)
    {
        printf("Custo do ator %d: %d\n", i + 1, custoAtor[i]);
    }
#endif
    Config_t config;
    config.corteOtimalidade = config.corteViabilidade = 1;
    config.usarBdada = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-o") == 0)
            config.corteOtimalidade = 0;

        if (strcmp(argv[i], "-f") == 0)
            config.corteViabilidade = 0;

        if (strcmp(argv[i], "-a") == 0)
            config.usarBdada = 1;
    }

    inicio = clock();
    branchAndBound(0, PERSONAGENS, ATORES, GRUPOS, matrizAtorPersonagem, matrizAtorGrupo, custoAtor, alocacaoPersonagem, &config);
    // semBound(0, PERSONAGENS, ATORES, GRUPOS, matrizAtorPersonagem, matrizAtorGrupo, custoAtor, alocacaoPersonagem);
    fim = clock();
    double tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if (OptCusto == -1)
        printf("INVIAVEL\n");
    else
    {
        for (int i = 0; i < n; ++i)
        {
            if (OptX[i] != -1)
                printf("%d ", OptX[i] + 1);
        }

        printf("\n%d\n", OptCusto);
    }

    fprintf(stderr, "%d %lf\n", numDecidas, tempoGasto);

#ifdef DEBUG
    printf("Custo total: %d\n", OptCusto);
    printf("Atores escolhidos: ");
    for (int i = 0; i < n; ++i)
    {
        if (OptX[i] != -1)
            printf("%d ", OptX[i] + 1);
    }
    printf("\n");
    printf("Alocacao de personagens:\n");
    for (int i = 0; i < n; ++i)
    {
        if (OptX[i] != -1)
            printf("Personagem %d: Ator %d\n", i + 1, OptX[i] + 1);
        else
            printf("Personagem %d: Nenhum ator alocado\n", i + 1);
    }
#endif

    free(OptX);
    free(alocacaoPersonagem);

    free(custoAtor);
    free(matrizAtorPersonagem);
    free(matrizAtorGrupo);
    return 0;
}