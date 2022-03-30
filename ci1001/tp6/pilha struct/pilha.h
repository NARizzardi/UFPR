typedef struct cell {
    int valor;
    struct cell *prox, *ant;
} cell_t;

typedef struct pilha{
    cell_t *inicio, *fim;
    int tam;
} pilha_t;

pilha_t *inicializa_pilha();

cell_t *new_cell(int valor);

void esvazia_pilha(pilha_t *pilha);

int vazia(pilha_t* pilha);

void empilha(int valor, pilha_t* pilha);

void desempilha(pilha_t* pilha);

int tamanho(pilha_t* pilha);

void imprime (pilha_t* pilha);

