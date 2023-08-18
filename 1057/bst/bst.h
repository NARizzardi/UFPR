typedef struct node{
    struct node *father;
    struct node *left;
    struct node *right;
    int value;
} tnode_t;

typedef struct bstree{
    int altura;
    tnode_t *root;
} bstree_t;


bstree_t *inicializa_bst();

tnode_t *cria_nodo(int valor);

tnode_t *inclusao_raiz();

void imprime_nodo();

void em_ordem();

void pre_ordem();

void pos_ordem();

int conta_nodos();

int altura();

tnode_t *busca_binaria();

tnode_t *minimo();

tnode_t *sucessor();

tnode_t *maximo();

tnode_t *antecessor();

void ajusta_no_pai();

tnode_t *exclusao();

