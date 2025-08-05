#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "grafo.h"

#define LINESIZE 2048
#define BRANCO 0
#define PRETO 1
struct adjacencia{
  char *v;
  unsigned int peso;
  struct adjacencia *proximo;
};  typedef struct adjacencia adjacencia;

struct vertice {
    char *v;
    int cor;
    unsigned int grau;
    unsigned int estado;
    unsigned int componente;
    adjacencia *cabeca;
    struct vertice *pai;
};  typedef struct vertice vertice;

struct grafo {
  char* nome;
  unsigned int vertices;
  unsigned int arestas;
  unsigned int qtd_componentes;
  vertice *adjacencias;
}; typedef struct grafo grafo;

// ------------------------------------------ PROTOTYPES ------------------------------------------
grafo *novo_grafo(void);
adjacencia *cria_adjacencia(char *vertice_destino, unsigned int peso);
vertice *cria_vertice(char *nome);
int existe_vertice(grafo *g, char *v_escolhido);
void adiciona_adjacencia(vertice *v, char *vertice_destino, unsigned int peso);
void adiciona_vertice(grafo *g, char *vertice_origem, char* vertice_destino, unsigned int peso);
unsigned int destroi_adjacencias(adjacencia *a);
unsigned int destroi_vertice(vertice *v);
void zera_grafo(grafo *g);
void dijkstra(grafo *g, unsigned int origem_idx, unsigned int *dist);
void calcula_componente(grafo *g, vertice *v);
int compara(const void *a, const void *b);
int indice_do_vertice(grafo *g, const char *nome);
void dfs_corte( grafo *g, unsigned int u, int *visitado, int *desc, int *low, int *pai, int *articulacoes, char ***nomes_arestas, unsigned int *qtd_arestas, unsigned int *max_arestas, int *tempo);
int cmp_string(const void *a, const void *b);

grafo *novo_grafo(void){
  grafo *g = (grafo *) malloc(sizeof(grafo));
  if(!g) 
    return NULL;
  g->nome = (char *) malloc(sizeof(char) * LINESIZE);
  strcpy(g->nome, ""); // Inicializa com string vazia
  g->arestas = 0;
  g->vertices = 0;
  g->qtd_componentes = 0;
  g->adjacencias = (vertice *) malloc(sizeof(vertice) * 20000);
  
  return g;
}

adjacencia *cria_adjacencia(char *vertice_destino, unsigned int peso){
  adjacencia *a = (adjacencia *) malloc(sizeof(adjacencia));
  a->v = (char *) malloc(sizeof(char) * LINESIZE);
  strcpy(a->v, vertice_destino);
  a->peso = peso;
  a->proximo = NULL;
  return a;
}

vertice *cria_vertice(char *nome){
  vertice *v = (vertice *) malloc(sizeof(vertice));
  v->v = (char *) malloc(sizeof(char) * LINESIZE);
  v->cabeca = NULL;
  v->grau = 0;
  v->cor = 0;
  v->estado = 0;
  v->componente = 0;
  v->pai = NULL;
  strcpy(v->v, nome);
  return v;
}

int existe_vertice(grafo *g, char *v_escolhido){
  for(unsigned int i = 0; i < g->vertices; i++){
    if(strcmp(g->adjacencias[i].v, v_escolhido) == 0){
      return (int) i;
    }
  }
  return -1;
}

void adiciona_adjacencia(vertice *v, char *vertice_destino, unsigned int peso){
  adjacencia *a = cria_adjacencia(vertice_destino, peso);
  adjacencia *aux = v->cabeca;
  if(v->cabeca == NULL){
    v->cabeca = a;
  } else {
    while(aux->proximo != NULL){
      aux = aux->proximo;
    }
    aux->proximo = a;
  }

  v->grau++;
}

void adiciona_vertice(grafo *g, char *vertice_origem, char* vertice_destino, unsigned int peso){
  if(peso == 0){ // vertice isolado
    if(existe_vertice(g, vertice_origem) < 0){
      vertice *v = cria_vertice(vertice_origem);
      g->adjacencias[g->vertices] = *v;
      free(v); // Libera o ponteiro temporário, mas mantém o conteúdo copiado
      g->vertices++;
    }
  } else { // vertice com aresta
    vertice *origem;
    vertice *destino;

    int existe_origem = existe_vertice(g, vertice_origem);
    int existe_destino = existe_vertice(g, vertice_destino);
    if(existe_origem < 0){
      origem = cria_vertice(vertice_origem);
      g->adjacencias[g->vertices] = *origem;
      free(origem);
      existe_origem = (int) g->vertices;
      g->vertices++;
    }
    if(existe_destino < 0){
      destino = cria_vertice(vertice_destino);
      g->adjacencias[g->vertices] = *destino;
      free(destino);
      existe_destino = (int) g->vertices;
      g->vertices++;
    }

    adiciona_adjacencia(&g->adjacencias[existe_origem], vertice_destino, peso);
    adiciona_adjacencia(&g->adjacencias[existe_destino], vertice_origem, peso);

    g->arestas++;
  }
}

void calcula_componente(grafo *g, vertice *v){
  v->estado = 1;
  vertice **fila = (vertice **) malloc(sizeof(vertice *) * g->vertices);
  int inicio_fila = 0;
  fila[inicio_fila] = v;
  int fim_fila = 1;
  while(inicio_fila < fim_fila){
    vertice *aux = fila[inicio_fila];
    inicio_fila++;
    adjacencia *a = aux->cabeca;
    while(a){
      int indice = existe_vertice(g, a->v);
      vertice *w = &g->adjacencias[indice];
      if(w->estado == 0){
        w->componente = v->componente;
        w->estado = 1;
        fila[fim_fila] = w;
        fim_fila++;
      }
      a = a->proximo;
    }
    v->estado = 2;
  }
  free(fila);
}

void dijkstra(grafo *g, unsigned int origem_idx, unsigned int *dist) {
    unsigned int n = g->vertices;
    int u = -1;
    unsigned int menor;

    int *visitado = calloc(n, sizeof(int));
    if (!visitado) {
        fprintf(stderr, "Erro de alocação.\n");
        exit(1);
    }

    for (unsigned int i = 0; i < n; i++) {
        dist[i] = UINT_MAX;
    }

    dist[origem_idx] = 0;

    while (1) {
        menor = UINT_MAX;
        u = -1;

        for (unsigned int i = 0; i < n; i++) {
            if (!visitado[i] && dist[i] < menor) {
                menor = dist[i];
                u = (int) i;
            }
        }

        if (u == -1) break;

        visitado[u] = 1;

        adjacencia *a = g->adjacencias[u].cabeca;
        while (a != NULL) {
            int v = existe_vertice(g, a->v);
            if (v >= 0 && !visitado[v]) {
                unsigned int alt = dist[u] + a->peso;
                if (alt < dist[v]) {
                    dist[v] = alt;
                }
            }
            a = a->proximo;
        }
    }

    free(visitado);
}

unsigned int destroi_adjacencias(adjacencia *a){
  if(a == NULL) return 1;
  
  if(a->proximo){
    destroi_adjacencias(a->proximo);
  }

  if(a->v) {
    free(a->v);
  }
  free(a);

  return 1;
}

unsigned int destroi_vertice(vertice *v) {
    if (v == NULL) return 1;

    if (v->v) {
        free(v->v);
        v->v = NULL;
    }

    if (v->cabeca) {
        destroi_adjacencias(v->cabeca);
        v->cabeca = NULL;
    }

    return 1;
}

void zera_grafo(grafo *g){
  vertice *v;
  for(unsigned int i = 0; i < g->vertices; i++){
    v = &g->adjacencias[i];
    v->estado = 0;
  }
}

int compara(const void *a, const void *b) {
    const unsigned int va = *(const unsigned int *)a;
    const unsigned int vb = *(const unsigned int *)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int indice_do_vertice(grafo *g, const char *nome) {
    for (unsigned int i = 0; i < g->vertices; i++) {
        if (strcmp(g->adjacencias[i].v, nome) == 0) {
            return (int)i;
        }
    }
    return -1; 
}

void dfs_corte(grafo *g, unsigned int u, int *visitado, int *desc, int *low, int *pai, int *articulacoes, char ***nomes_arestas, unsigned int *qtd_arestas, unsigned int *max_arestas, int *tempo) {
    visitado[u] = 1;
    desc[u] = low[u] = ++(*tempo);

    unsigned int filhos = 0;
    adjacencia *adj = g->adjacencias[u].cabeca;

    while (adj != NULL) {
        int v_tmp = indice_do_vertice(g, adj->v);
        if (v_tmp == -1) {
            fprintf(stderr, "Erro: vertice %s nao encontrado no grafo.\n", adj->v);
            exit(EXIT_FAILURE);
        }
        unsigned int v = (unsigned int) v_tmp;

        if (!visitado[v]) {
            pai[v] = (int) u;
            filhos++;

            dfs_corte(g, v, visitado, desc, low, pai, articulacoes, nomes_arestas, qtd_arestas, max_arestas, tempo);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if (articulacoes != NULL) {
                if ((pai[u] == -1 && filhos > 1) || (pai[u] != -1 && low[v] >= desc[u])) {
                    articulacoes[u] = 1;
                }
            }

            if (nomes_arestas && low[v] > desc[u]) {
                const char *nome1 = g->adjacencias[u].v;
                const char *nome2 = g->adjacencias[v].v;

                const char *primeiro = (strcmp(nome1, nome2) <= 0) ? nome1 : nome2;
                const char *segundo = (primeiro == nome1) ? nome2 : nome1;

                char *aresta = malloc(strlen(primeiro) + strlen(segundo) + 2);
                if (!aresta) {
                    fprintf(stderr, "Erro no malloc.\n");
                    exit(EXIT_FAILURE);
                }
                sprintf(aresta, "%s %s", primeiro, segundo);

                if (*qtd_arestas >= *max_arestas) {
                    *max_arestas *= 2;
                    char **temp = realloc(*nomes_arestas, (*max_arestas) * sizeof(char *));
                    if (!temp) {
                        fprintf(stderr, "Erro no realloc.\n");
                        exit(EXIT_FAILURE);
                    }
                    *nomes_arestas = temp;
                }
                (*nomes_arestas)[(*qtd_arestas)++] = aresta;
            }

        } else if (v != (unsigned int) pai[u]) {
            low[u] = (low[u] < desc[v]) ? low[u] : desc[v];
        }

        adj = adj->proximo;
    }
}

int cmp_string(const void *a, const void *b) {
    const char * const *str_a = (const char * const *)a;
    const char * const *str_b = (const char * const *)b;
    return strcmp(*str_a, *str_b);
}

// --------------------------------------- FUNÇÕES EXTERNAS ---------------------------------------

grafo *le_grafo(FILE *f){
  grafo *g = novo_grafo();

  char *entrada = (char *) malloc(sizeof(char) * LINESIZE);
  char *vertice_origem = (char *) malloc(sizeof(char) * LINESIZE);
  char *vertice_destino = (char *) malloc(sizeof(char) * LINESIZE);
  char *token;


  while(fgets(entrada, LINESIZE, f) != NULL){
    if((entrada[0] == '/' && entrada[1] == '/')) continue;

    entrada[strcspn(entrada, "\n")] = 0;

    int only_whitespace = 1;
    for (char *p = entrada; *p; p++) {
        if (!isspace((unsigned char)*p)) {
            only_whitespace = 0;
            break;
        }
    }
    if (only_whitespace) continue;

      if(!strcmp(g->nome, "")) {
        strcpy(g->nome, entrada);
        continue;
      }
      if (strstr(entrada, "--") == NULL) {
        adiciona_vertice(g, entrada, NULL, 0);
      } else {
        unsigned int peso = 1;
        token = strtok(entrada, " ");
        strcpy(vertice_origem, token);
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        strcpy(vertice_destino, token);
        token = strtok(NULL, " ");
        if (token != NULL) {
          peso = (unsigned int) atoi(token);
          if(peso == 0) peso = 1;
        }
        adiciona_vertice(g, vertice_origem, vertice_destino, peso);
      }
      if(g->vertices % 100 == 0) {
        g->adjacencias = (vertice *) realloc(g->adjacencias, sizeof(vertice) * (g->vertices + 100));
      }

  }

  free(entrada);
  free(vertice_origem);
  free(vertice_destino);

  return g;
}

char *nome(grafo *g){
  return g->nome;
}

unsigned int n_vertices(grafo *g){
  return g->vertices;
}

unsigned int n_arestas(grafo *g){
  return g->arestas;
}

unsigned int n_componentes(grafo *g){
  for(unsigned int i = 0; i < g->vertices; i++){
    vertice *v = &g->adjacencias[i];
    if(v->estado == 0){
      v->componente = ++g->qtd_componentes;
      calcula_componente(g, v);
    }
  }
  zera_grafo(g);
  return g->qtd_componentes;
}

unsigned int bipartido(grafo *g){
  if(g->vertices < 2)
    return 0;
  vertice *v;
  adjacencia *nodo;
  for(unsigned int i = 0; i < g->vertices; i++){
    v = &g->adjacencias[i];
    if(v->cor == 0) v->cor = -1;
    if(v->grau > 0){
      nodo = v->cabeca;
      for(unsigned int j = 0; j < v->grau; j++){
        int indice = existe_vertice(g, nodo->v);
        vertice *aux = &g->adjacencias[indice];
        if(aux->estado == 0){
          if(aux->cor == 0){
            aux->cor = v->cor * (-1);
          }else if(aux->cor == v->cor){
            zera_grafo(g);
            return 0;
          }
        }
        nodo = nodo->proximo;
      }
    }
    v->estado = 1;
  }

  return 1;
}

char *diametros(grafo *g) {
    unsigned int qtd_componentes = g->qtd_componentes;

    unsigned int *diametros_componentes = calloc(qtd_componentes, sizeof(unsigned int));
    if (!diametros_componentes) {
        fprintf(stderr, "Erro de alocação\n");
        exit(1);
    }

    unsigned int *dist = malloc(g->vertices * sizeof(unsigned int));
    if (!dist) {
        fprintf(stderr, "Erro de alocação\n");
        free(diametros_componentes);
        exit(1);
    }

    for (unsigned int i = 0; i < g->vertices; i++) {
        vertice *v = &(g->adjacencias[i]);

        dijkstra(g, i, dist);

        unsigned int max = 0;
        for (unsigned int j = 0; j < g->vertices; j++) {
            if (g->adjacencias[j].componente == v->componente && dist[j] != UINT_MAX) {
                if (dist[j] > max) {
                    max = dist[j];
                }
            }
        }

        unsigned int idx = v->componente - 1;
        if (max > diametros_componentes[idx]) {
            diametros_componentes[idx] = max;
        }
    }

    free(dist);

    qsort(diametros_componentes, qtd_componentes, sizeof(unsigned int), compara);

    size_t tam = (11 * qtd_componentes) + 1;
    char *resultado = malloc(tam);
    if (!resultado) {
        fprintf(stderr, "Erro de alocação\n");
        free(diametros_componentes);
        exit(1);
    }

    resultado[0] = '\0';

    for (unsigned int i = 0; i < qtd_componentes; i++) {
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%u", diametros_componentes[i]);
        strcat(resultado, buffer);
        if (i < qtd_componentes - 1) {
            strcat(resultado, " ");
        }
    }

    free(diametros_componentes);

    return resultado;
}

char *vertices_corte(grafo *g) {
    int *visitado = calloc(g->vertices, sizeof(int));
    int *desc = calloc(g->vertices, sizeof(int));
    int *low = calloc(g->vertices, sizeof(int));
    int *pai = malloc(g->vertices * sizeof(int));
    int *articulacoes = calloc(g->vertices, sizeof(int));

    if (!visitado || !desc || !low || !pai || !articulacoes) {
        fprintf(stderr, "Erro de alocação.\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < g->vertices; i++) {
        pai[i] = -1;
    }

    int tempo = 0;

    for (unsigned int i = 0; i < g->vertices; i++) {
        if (!visitado[i]) {
            dfs_corte(g, i, visitado, desc, low, pai, articulacoes, NULL, NULL, NULL, &tempo);
        }
    }

    unsigned int count = 0;
    for (unsigned int i = 0; i < g->vertices; i++) {
        if (articulacoes[i]) count++;
    }

    if (count == 0) {
        free(visitado); free(desc); free(low); free(pai); free(articulacoes);
        char *res = malloc(1);
        res[0] = '\0';
        return res;
    }

    char **nomes = malloc(count * sizeof(char *));
    unsigned int idx = 0;
    for (unsigned int i = 0; i < g->vertices; i++) {
        if (articulacoes[i]) {
            nomes[idx++] = g->adjacencias[i].v;
        }
    }

    qsort(nomes, count, sizeof(char *), cmp_string);

    size_t tamanho = 0;
    for (unsigned int i = 0; i < count; i++) {
        tamanho += strlen(nomes[i]) + 1;
    }

    char *res = malloc(tamanho + 1);
    res[0] = '\0';
    for (unsigned int i = 0; i < count; i++) {
        strcat(res, nomes[i]);
        if (i != count - 1) strcat(res, " ");
    }

    free(nomes);
    free(visitado); free(desc); free(low); free(pai); free(articulacoes);

    return res;
}

char *arestas_corte(grafo *g) {
    int *visitado = calloc(g->vertices, sizeof(int));
    int *desc = calloc(g->vertices, sizeof(int));
    int *low = calloc(g->vertices, sizeof(int));
    int *pai = malloc(g->vertices * sizeof(int));

    if (!visitado || !desc || !low || !pai) {
        fprintf(stderr, "Erro de alocação.\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < g->vertices; i++) {
        pai[i] = -1;
    }

    unsigned int max_arestas = 16;
    unsigned int qtd_arestas = 0;
    char **nomes_arestas = malloc(max_arestas * sizeof(char *));
    if (!nomes_arestas) {
        fprintf(stderr, "Erro de alocação.\n");
        exit(EXIT_FAILURE);
    }

    int tempo = 0;

    for (unsigned int i = 0; i < g->vertices; i++) {
        if (!visitado[i]) {
            dfs_corte(
                g, i, visitado, desc, low, pai,
                NULL, &nomes_arestas, &qtd_arestas, &max_arestas,
                &tempo
            );
        }
    }

    if (qtd_arestas == 0) {
        free(visitado); free(desc); free(low); free(pai); free(nomes_arestas);
        char *res = malloc(1);
        res[0] = '\0';
        return res;
    }

    qsort(nomes_arestas, qtd_arestas, sizeof(char *), cmp_string);

    size_t tamanho = 0;
    for (unsigned int i = 0; i < qtd_arestas; i++) {
        tamanho += strlen(nomes_arestas[i]) + 1; // +1 para espaço ou \0
    }

    char *res = malloc(tamanho + 1);
    if (!res) {
        fprintf(stderr, "Erro de alocação.\n");
        exit(EXIT_FAILURE);
    }

    res[0] = '\0';
    for (unsigned int i = 0; i < qtd_arestas; i++) {
        strcat(res, nomes_arestas[i]);
        if (i != qtd_arestas - 1) strcat(res, " ");
    }

    for (unsigned int i = 0; i < qtd_arestas; i++) {
        free(nomes_arestas[i]);
    }
    free(nomes_arestas);

    free(visitado);
    free(desc);
    free(low);
    free(pai);

    return res;
}

unsigned int destroi_grafo(grafo *g) {
    if (g == NULL) return 0;

    for (unsigned int i = 0; i < g->vertices; i++) {
        destroi_vertice(&g->adjacencias[i]);
    }

    free(g->adjacencias);
    g->adjacencias = NULL;

    free(g->nome);
    g->nome = NULL;

    free(g);
    g = NULL;

    return 1;
}

