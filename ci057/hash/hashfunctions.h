#define COL 2
#define M 11

typedef struct entry{
    int key;
    int table;
} entry_t;

typedef struct entries{
    entry_t *entrada_list[COL*M];
    int tam;
} entries_t;

entries_t *cria_entrada_list();

void insere_valor(int valor, entries_t *entradas, int table);

void remove_valor(int valor, entries_t *entradas);

void init_table (int ht[COL][M]);

int include_key (int key, int ht[COL][M]);

int remove_key (int key, int ht[COL][M]);

void print_table(entries_t *entradas, int ht[COL][M]);