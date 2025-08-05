#include <stdlib.h>

#define MAX 99999
typedef struct
{
  int corteOtimalidade, corteViabilidade, usarBdada;
} Config_t;

void semBound(int personagemAtual, int numeroDePersonagens, int numeroDeAtores, int numeroDeGrupos,
              int **matrizAtorPersonagem, int **matrizAtorGrupo, int *custoAtor, int *alocacaoPersonagem);

void branchAndBound(int personagemAtual, int numeroDePersonagens, int numeroDeAtores, int numeroDeGrupos,
                    int **matrizAtorPersonagem, int **matrizAtorGrupo, int *custoAtor, int *alocacaoPersonagem, Config_t *config);

int Bdada(int *atoresEscolhidos, int numeroDePerso, int numeroDeAtores, int *custoAtor, int personagemAtual, Config_t *config);

int minimoCusto(int *atoresRestantes, int numeroDeAtores, int *custoAtor);

int *getAtoresRestantes(int *alocacaoPersonagem, int numeroDePersonagens, int numeroDeAtores, Config_t *config);

int bound(int *atoresEscolhidos, int numeroDePerso, int numeroDeAtores, int *custoAtor, int personagemAtual, int **matrizAtorPersonagem, Config_t *config);

int **submatriz(int **matrizAtorPersonagem, int *atoresEscolhidos, int numeroDeAtores, int *papeisRestantes, int qtdPapeisRestantes, int *custoAtor);

int *getPapeisRestantes(int *alocacaoPersonagem, int numeroDePerso, int personagemAtual, int *qtdPapeisRestantes);