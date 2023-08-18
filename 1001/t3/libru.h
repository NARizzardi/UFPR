#include "libfila.h"
#include "liblista.h"
#include "libpilha.h"

#define MAX_PESSOAS 1000

typedef struct pessoa {
    int ticket;
    int vacinado;
    int mascara;
    float dinheiro;
} pessoa_t;


typedef struct data {
    float dinheiro_total;
    int dinheiro_refeicoes;
    int dinheiro_mascaras;
} data_t;

data_t *cria_dados();

void aleat(int min, int max, int *valor);

void enche_pilha(pilha_t* pilha);

void popula_conjunto(pessoa_t *todas_pessoas[]);

void popula_fila(fila_t *fila_pessoas);

pessoa_t *proximo(fila_t *fila_pessoas, pessoa_t *todas_pessoas[]);

int pega_ticket(pessoa_t *pessoa);

int eh_vacinado(pessoa_t *pessoa);

void insere_ticket(lista_t *tickets_nao_usados, int ticket);

int usa_mascara(pessoa_t *pessoa);

float saldo(pessoa_t *pessoa);

void compra_refeicao(pessoa_t *pessoa, pilha_t* refeicoes);

void adiciona_contador(data_t *dados_ru, int indicador);

int tem_mascara(pilha_t *mascaras);

void compra_mascara(pessoa_t *pessoa, pilha_t *mascaras);

void volta_pra_fila(pessoa_t *pessoa, fila_t *fila_pessoas);

void imprime_dados(data_t *dados_ru, lista_t *tickets_nao_usados);

void pessoas_destroi(pessoa_t *todas_pessoas[]);

void dados_destroi(data_t *dados_ru);
