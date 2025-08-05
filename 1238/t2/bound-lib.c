#include "bound-lib.h"

int *OptX, OptCusto, numDecidas = 0;

/*
    Metodo ingenuo de busca, só para testar modelagem e se meu código tava funfando xd
*/
void semBound(int personagemAtual, int numeroDePersonagens, int numeroDeAtores, int numeroDeGrupos,
              int **matrizAtorPersonagem, int **matrizAtorGrupo, int *custoAtor, int *alocacaoPersonagem)
{
    ++numDecidas;

    if (personagemAtual == numeroDePersonagens)
    {
        // Verificar grupos
        int gruposCobertos[numeroDeGrupos];
        for (int i = 0; i < numeroDeGrupos; i++)
            gruposCobertos[i] = 0;

        int atoresUsados[numeroDeAtores];
        for (int i = 0; i < numeroDeAtores; i++)
            atoresUsados[i] = 0;

        for (int p = 0; p < numeroDePersonagens; p++)
        {
            int ator = alocacaoPersonagem[p];
            atoresUsados[ator] = 1;
            for (int g = 0; g < numeroDeGrupos; g++)
            {
                if (matrizAtorGrupo[ator][g] == 1)
                {
                    gruposCobertos[g] = 1;
                }
            }
        }

        // Verificar se todos os grupos foram cobertos
        for (int g = 0; g < numeroDeGrupos; g++)
        {
            if (gruposCobertos[g] == 0)
                return; // Grupo não coberto, descarta
        }

        // Calcula custo
        int custo = 0;
        for (int i = 0; i < numeroDeAtores; i++)
        {
            if (atoresUsados[i])
                custo += custoAtor[i];
        }

        if (OptCusto == -1 || custo < OptCusto)
        {
            OptCusto = custo;
            for (int p = 0; p < numeroDePersonagens; p++)
            {
                OptX[p] = alocacaoPersonagem[p];
            }
        }
        return;
    }

    // Testa todos os atores que podem fazer este personagem
    // solução parcial em alocacaoPersonagem
    for (int a = 0; a < numeroDeAtores; a++)
    {
        if (matrizAtorPersonagem[a][personagemAtual] == 1)
        {
            alocacaoPersonagem[personagemAtual] = a;
            semBound(personagemAtual + 1, numeroDePersonagens, numeroDeAtores, numeroDeGrupos,
                     matrizAtorPersonagem, matrizAtorGrupo, custoAtor, alocacaoPersonagem);
            alocacaoPersonagem[personagemAtual] = -1; // tira da solução parcial
        }
    }
}

void branchAndBound(int personagemAtual, int numeroDePersonagens, int numeroDeAtores, int numeroDeGrupos,
                    int **matrizAtorPersonagem, int **matrizAtorGrupo, int *custoAtor, int *alocacaoPersonagem, Config_t *config)
{

    ++numDecidas;

    if (personagemAtual == numeroDePersonagens)
    {
        // Verificar grupos
        int gruposCobertos[numeroDeGrupos];
        for (int i = 0; i < numeroDeGrupos; i++)
            gruposCobertos[i] = 0;

        for (int p = 0; p < numeroDePersonagens; p++)
        {
            int ator = alocacaoPersonagem[p];
            if (ator != -1)
            {
                for (int g = 0; g < numeroDeGrupos; g++)
                {
                    if (matrizAtorGrupo[ator][g] == 1)
                    {
                        gruposCobertos[g] = 1;
                    }
                }
            }
        }

        // Verificar se todos os grupos foram cobertos
        for (int g = 0; g < numeroDeGrupos; g++)
        {
            if (gruposCobertos[g] == 0 && config->corteViabilidade)
                return; // Grupo não coberto, descarta
        }

        // Calcula custo
        int custo = 0;
        for (int p = 0; p < numeroDePersonagens; p++)
        {
            int ator = alocacaoPersonagem[p];
            if (ator != -1)
                custo += custoAtor[ator];
        }

        if (OptCusto == -1 || custo < OptCusto)
        {
            OptCusto = custo;
            for (int p = 0; p < numeroDePersonagens; p++)
            {
                OptX[p] = alocacaoPersonagem[p];
            }
        }
        return;
    }

    // Testa todos os atores que podem fazer este personagem
    for (int a = 0; a < numeroDeAtores; a++)
    {
        if (config->corteViabilidade)
        {
            if (matrizAtorPersonagem[a][personagemAtual] != 1)
                continue;

            int atorJaUsado = 0;
            for (int i = 0; i < personagemAtual; i++)
            {
                if (alocacaoPersonagem[i] == a)
                {
                    atorJaUsado = 1;
                    break;
                }
            }
            if (atorJaUsado)
                continue;
        }

        if (config->usarBdada)
        {
            if (Bdada(alocacaoPersonagem, numeroDePersonagens, numeroDeAtores, custoAtor, personagemAtual, config))
            {
                alocacaoPersonagem[personagemAtual] = a;
                branchAndBound(personagemAtual + 1, numeroDePersonagens, numeroDeAtores, numeroDeGrupos,
                               matrizAtorPersonagem, matrizAtorGrupo, custoAtor, alocacaoPersonagem, config);
            }
        }
        else // usar nossa função de bounding
        {
            if (bound(alocacaoPersonagem, numeroDePersonagens, numeroDeAtores, custoAtor, a, matrizAtorPersonagem, config))
            {
                alocacaoPersonagem[personagemAtual] = a;
                branchAndBound(personagemAtual + 1, numeroDePersonagens, numeroDeAtores, numeroDeGrupos,
                               matrizAtorPersonagem, matrizAtorGrupo, custoAtor, alocacaoPersonagem, config);
            }
        }

        alocacaoPersonagem[personagemAtual] = -1;
    }
}

int Bdada(int *atoresEscolhidos, int numeroDePerso, int numeroDeAtores, int *custoAtor, int personagemAtual, Config_t *config)
{
    if (OptCusto == -1)
        return 1;

    int *atoresRestantes = getAtoresRestantes(atoresEscolhidos, numeroDePerso, numeroDeAtores, config);

    int somaCusto = 0;
    for (int i = 0; i < personagemAtual; i++)
    {
        int ator = atoresEscolhidos[i];
        if (ator != -1)
        {
            somaCusto += custoAtor[ator];
        }
    }

    int vMin = minimoCusto(atoresRestantes, numeroDeAtores, custoAtor);
    int quantosFaltam = numeroDePerso - personagemAtual;

    // Conta quantos atores ainda estão disponíveis
    int disponiveis = 0;
    for (int i = 0; i < numeroDeAtores; i++)
        if (atoresRestantes[i])
            disponiveis++;

    free(atoresRestantes);
    if (config->corteViabilidade)
    {
        if (disponiveis < quantosFaltam)
            return 0; // Não há atores suficientes

        if (vMin == -1)
            return 0; // Não há mais atores disponíveis
    }

    if (somaCusto + quantosFaltam * vMin <= OptCusto)
        return 1;

    return 0;
}

int minimoCusto(int *vet, int num, int *custoAtor)
{
    int min = MAX;
    for (int i = 0; i < num; i++)
    {
        if (vet[i] == 1)
        {
            if (min == -1 || custoAtor[i] < min)
            {
                min = custoAtor[i];
            }
        }
    }
    if (min == MAX)
        return -1;
    return min;
}

/*
    1 : ator disponivel
    0 : ator já foi usado
*/
int *getAtoresRestantes(int *alocacaoPersonagem, int numeroDePersonagens, int numeroDeAtores, Config_t *config)
{
    int *atoresRestantes = malloc(numeroDeAtores * sizeof(int));
    for (int i = 0; i < numeroDeAtores; i++)
        atoresRestantes[i] = 1; // Todos começam como disponíveis

    if (!config->corteViabilidade)
        return atoresRestantes;

    for (int p = 0; p < numeroDePersonagens; p++)
    {
        int ator = alocacaoPersonagem[p];
        if (ator != -1)
        {                              // Só remove se foi alocado
            atoresRestantes[ator] = 0; // ator já foi usado
        }
    }

    return atoresRestantes;
}

int minimo(int *linha, int tamanho)
{
    if(!linha)
        return -1;
    int min = -1;
    for (int i = 0; i < tamanho; i++)
    {
        if (min == -1 || linha[i] < min)
            min = linha[i];
    }

    return min;
}

int *getPapeisRestantes(int *alocacaoPersonagem, int numeroDePerso, int personagemAtual, int *qtdPapeisRestantes)
{
    int *restantes = malloc(numeroDePerso * sizeof(int));
    int count = 0;
    for (int i = personagemAtual; i < numeroDePerso; i++)
    {
        if (alocacaoPersonagem[i] == -1)
        {
            restantes[count++] = i;
        }
    }
    *qtdPapeisRestantes = count;
    return restantes;
}

int **submatriz(int **matrizAtorPersonagem, int *atoresRestantes, int numeroDeAtores, int *papeisRestantes, int qtdPapeisRestantes, int *custoAtor)
{
    // Contar atores disponíveis
    int qtdAtoresDisponiveis = 0;
    for (int i = 0; i < numeroDeAtores; i++)
    {
        if (atoresRestantes[i])
            qtdAtoresDisponiveis++;
    }

    // Aloca matriz
    int **matrizReduzida = malloc(qtdAtoresDisponiveis * sizeof(int *));
    for (int i = 0; i < qtdAtoresDisponiveis; i++)
        matrizReduzida[i] = malloc(qtdPapeisRestantes * sizeof(int));

    int linha = 0;
    for (int a = 0; a < numeroDeAtores; a++)
    {
        if (!atoresRestantes[a])
            continue;

        for (int j = 0; j < qtdPapeisRestantes; j++)
        {
            int papel = papeisRestantes[j];
            if (matrizAtorPersonagem[a][papel] == 1)
                matrizReduzida[linha][j] = custoAtor[a];
            else
                matrizReduzida[linha][j] = MAX;
        }
        linha++;
    }

    return matrizReduzida;
}

int bound(int *atoresEscolhidos, int numeroDePerso, int numeroDeAtores, int *custoAtor, int personagemAtual, int **matrizAtorPersonagem, Config_t *config)
{
    if (OptCusto == -1)
        return 1;

    int qtdPapeisRestantes;
    int *papeisRestantes = getPapeisRestantes(atoresEscolhidos, numeroDePerso, personagemAtual, &qtdPapeisRestantes);
    if (qtdPapeisRestantes == 0)
        return 1;

    int qtAtoresDispo = numeroDeAtores - personagemAtual;
    if (qtAtoresDispo == 0)
        return 0;

    int **matrizReduzida = submatriz(matrizAtorPersonagem, atoresEscolhidos, numeroDeAtores, papeisRestantes, qtdPapeisRestantes, custoAtor);

    int custo = 0;
    for (int i = 0; i < qtAtoresDispo; ++i)
    {
        int min = minimo(matrizReduzida[i], qtdPapeisRestantes);
        if (min == -1)
        {
            free(matrizReduzida);
            return 0;
        }

        custo += min;
    }

    for (int i = 0; i < qtAtoresDispo; i++)
        free(matrizReduzida[i]);
    free(matrizReduzida);
    free(papeisRestantes);

    if (custo <= OptCusto)
        return 1;

    return 0;
}