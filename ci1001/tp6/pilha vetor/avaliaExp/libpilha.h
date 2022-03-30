typedef struct pilha{
    char *array; /* Vetor de chars de abertura */
    int last; /* Posicao do ultimo elemento da pilha */
    int tam; /* Tamanho da pilha */
} pilha_t;


/* Funcao que inicializa a pilha definindo os valores iniciais da struct e retorna a pilha criada */
/* Retorna 0 em caso de erro na inicializacao*/
pilha_t *inicializa_pilha();

/* Funcao que esvazia a pilha, removendo todos os seus elementos */
/* Nao possui retorno */
void esvazia_pilha(pilha_t *pilha);

/* Funcao que retorna 1 se a pilha for vazia */
/* Retorna 0 caso o tamanho da pilha nao seja 0 */
int vazia(pilha_t* pilha);

/* Funcao que empilha um elemento no topo da pilha */
/* Nao possui retorno */
void empilha(char valor, pilha_t* pilha);

/* Funcao que tenta desempilhar o elemento no topo da pilha */
/* Retorna 0 caso a pilha esteja vazia, ou o par de abertura e fechamento nao bata */
int desempilha(char valor, pilha_t* pilha);

/* Funcao que retorna o tamanho da pilha */
int tamanho(pilha_t* pilha);

/* Funcao que imprime a pilha do elemento mais ao topo ate a base da pilha */
/* Se a pilha nao tiver elementos imprime o aviso de que a pilha esta vazia */
/* Nao possui retorno */
void imprime (pilha_t* pilha);

