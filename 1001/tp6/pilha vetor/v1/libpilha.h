#define MAX 200

typedef struct pilha{
    int *array;
    int last;
    int tam;
} pilha_t;

pilha_t *inicializa_pilha();

void esvazia_pilha(pilha_t *pilha);

int vazia(pilha_t* pilha);

void empilha(int valor, pilha_t* pilha);

int desempilha(int valor, pilha_t* pilha);

int tamanho(pilha_t* pilha);

void imprime (pilha_t* pilha);

