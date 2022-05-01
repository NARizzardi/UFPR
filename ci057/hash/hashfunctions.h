#define COL 2
#define M 11

typedef struct array{
    int entradas[COL*M];
    int tam;
} array_t;

array_t *new_arrayt();

void insere_valor(int valor, array_t *vetor);

void remove_valor(int valor, array_t *vetor);

void init_table (int ht[COL][M]);

void include_key (int key, int ht[COL][M]);

int remove_key (int key, int ht[COL][M]);

void print_table(array_t *vetor, int ht[COL][M]);