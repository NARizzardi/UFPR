#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

#define LINESIZE 2047
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
    int desc;  // tempo de descoberta
    int low;   // menor tempo alcançável
    int visitado; // para algoritmo de Tarjan
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
int existe_adjacencia(vertice *v, char *vertice_destino);
int existe_vertice(grafo *g, char *v_escolhido);
void adiciona_adjacencia(vertice *v, char *vertice_destino, unsigned int peso);
void adiciona_vertice(grafo *g, char *vertice_origem, char* vertice_destino, unsigned int peso);
unsigned int destroi_adjacencias(adjacencia *a);
unsigned int destroi_vertice(vertice *v);
void zera_grafo(grafo *g);
int belongs_to(grafo *g, char *v);
void add_to(grafo *g, vertice *v);
int djikstra(grafo *g, char *v);
void ordena_lista(int *lista_diametros, unsigned int qtd_componentes);
void calcula_componente(grafo *g, vertice *v);
void tarjan_dfs(grafo *g, int v, int parent, int *time, int *ap, char **vertices_corte_lista, int *vc_count, char **arestas_corte_lista, int *ac_count);
void inicializa_tarjan(grafo *g);
// --------------------------------------- FUNÇÕES INTERNAS ---------------------------------------
grafo *novo_grafo(void){
  grafo *g = (grafo *) malloc(sizeof(grafo));
  if(!g)
    return NULL;
  g->nome = (char *) malloc(sizeof(char) * LINESIZE);
  strcpy(g->nome, ""); // Inicializa com string vazia
  g->arestas = 0;
  g->vertices = 0;
  g->qtd_componentes = 0;
  g->adjacencias = (vertice *) malloc(sizeof(vertice) * 100);
  
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
  v->pai = (vertice *) malloc(sizeof(vertice));
  v->pai = NULL;
  v->desc = -1;
  v->low = -1;
  v->visitado = 0;
  strcpy(v->v, nome);
  return v;
}

int existe_adjacencia(vertice *v, char *vertice_destino){
  adjacencia *a = v->cabeca;
  while(a != NULL){
    if(strcmp(a->v, vertice_destino) == 0){
      return 1;
    }
    a = a->proximo;
  }
  return 0;

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
      existe_origem = (int) g->vertices;
      g->vertices++;
    }
    if(existe_destino < 0){
      destino = cria_vertice(vertice_destino);
      g->adjacencias[g->vertices] = *destino;
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
}

int djikstra(grafo *g, char *v){
  return (int) v[0] + (int) g->qtd_componentes;
}

void ordena_lista(int *lista_diametros, unsigned int qtd_componentes){
  int i, key, j;
    for (i = 1; i < (int) qtd_componentes; i++) {
        key = lista_diametros[i];
        j = i - 1;

        while (j >= 0 && lista_diametros[j] > key) {
            lista_diametros[j + 1] = lista_diametros[j];
            j = j - 1;
        }
        lista_diametros[j + 1] = key;
    }
}

void inicializa_tarjan(grafo *g) {
    for(unsigned int i = 0; i < g->vertices; i++) {
        g->adjacencias[i].visitado = 0;
        g->adjacencias[i].desc = -1;
        g->adjacencias[i].low = -1;
    }
}

void tarjan_dfs(grafo *g, int v, int parent, int *time, int *ap, char **vertices_corte_lista, int *vc_count, char **arestas_corte_lista, int *ac_count) {
    int children = 0;
    g->adjacencias[v].visitado = 1;
    g->adjacencias[v].desc = g->adjacencias[v].low = ++(*time);
    
    adjacencia *adj = g->adjacencias[v].cabeca;
    while(adj != NULL) {
        int u = existe_vertice(g, adj->v);
        if(u != -1) {
            if(!g->adjacencias[u].visitado) {
                children++;
                tarjan_dfs(g, u, v, time, ap, vertices_corte_lista, vc_count, arestas_corte_lista, ac_count);
                
                g->adjacencias[v].low = (g->adjacencias[v].low < g->adjacencias[u].low) ? 
                                       g->adjacencias[v].low : g->adjacencias[u].low;
                
                // Verifica se v é vértice de corte
                if(parent == -1 && children > 1) {
                    ap[v] = 1;
                }
                if(parent != -1 && g->adjacencias[u].low >= g->adjacencias[v].desc) {
                    ap[v] = 1;
                }
                
                // Verifica se (v,u) é aresta de corte
                if(g->adjacencias[u].low > g->adjacencias[v].desc) {
                    // Adiciona aresta de corte à lista
                    sprintf(arestas_corte_lista[*ac_count], "%s %s", g->adjacencias[v].v, g->adjacencias[u].v);
                    (*ac_count)++;
                }
            }
            else if(u != parent) {
                g->adjacencias[v].low = (g->adjacencias[v].low < g->adjacencias[u].desc) ? 
                                       g->adjacencias[v].low : g->adjacencias[u].desc;
            }
        }
        adj = adj->proximo;
    }
}

unsigned int destroi_adjacencias(adjacencia *a){
  if(a->proximo){
    destroi_adjacencias(a->proximo);
  }

  free(a->v);
  a->v = NULL;
  free(a);
  a = NULL;

  return 1;
}

unsigned int destroi_vertice(vertice *v){
  free(v->v);
  v->v = NULL;
  free(v);
  v = NULL;
  return 1;
}

void zera_grafo(grafo *g){
  vertice *v;
  for(unsigned int i = 0; i < g->vertices; i++){
    v = &g->adjacencias[i];
    v->estado = 0;
  }
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


char *diametros(grafo *g){
  // if(g->qtd_componentes == 0) {
  //   char *ret = (char *) malloc(sizeof(char) * LINESIZE);
  //   strcpy(ret, "");
  //   return ret;
  // }
  
  // int *lista_diametros = (int *) malloc(sizeof(int) * g->qtd_componentes);
  // for(unsigned int i = 0; i < g->qtd_componentes; i++){
  //   lista_diametros[i] = 0;
  //   printf("Componente #%d\n", i+1);
  //   // Implementação simplificada - retorna 0 para todos os componentes
  //   lista_diametros[i] = 0;
  // }

  // ordena_lista(lista_diametros, g->qtd_componentes);
  // //ordena_lista
  // //concatena string
  // char *ret = (char *) malloc(sizeof(char) * LINESIZE);
  // char *str_num = (char *) malloc(sizeof(char) * LINESIZE);
  // ret[0] = '\0'; // Inicializa string vazia
  // unsigned int i;
  // for(i = 0; i < g->qtd_componentes-1; i++){
  //   snprintf(str_num, 127, "%d", lista_diametros[i]);
  //   strcat(ret, str_num);
  //   strcat(ret, " ");
  // }
  // if(g->qtd_componentes > 0) {
  //   snprintf(str_num, 127, "%d", lista_diametros[i]);
  //   strcat(ret, str_num);
  // }
  // free(str_num);
  // free(lista_diametros);
  // return ret;
  char *nome = (char *) malloc(sizeof(char) * LINESIZE);
  strcpy(nome, g->nome);
  return nome;
}

char *vertices_corte(grafo *g){
    if(g->vertices <= 1) {
        char *result = (char *) malloc(sizeof(char) * LINESIZE);
        strcpy(result, "");
        return result;
    }
    
    inicializa_tarjan(g);
    int time = 0;
    int *ap = (int *) calloc(g->vertices, sizeof(int)); // articulation points
    char **vertices_corte_lista = (char **) malloc(sizeof(char *) * g->vertices);
    char **arestas_corte_lista = (char **) malloc(sizeof(char *) * g->arestas);
    int vc_count = 0, ac_count = 0;
    
    // Aloca espaço para as strings
    for(unsigned int i = 0; i < g->vertices; i++) {
        vertices_corte_lista[i] = (char *) malloc(sizeof(char) * LINESIZE);
    }
    for(unsigned int i = 0; i < g->arestas; i++) {
        arestas_corte_lista[i] = (char *) malloc(sizeof(char) * LINESIZE);
    }
    
    // Executa DFS para todos os vértices não visitados
    for(unsigned int i = 0; i < g->vertices; i++) {
        if(!g->adjacencias[i].visitado) {
            tarjan_dfs(g, i, -1, &time, ap, vertices_corte_lista, &vc_count, arestas_corte_lista, &ac_count);
        }
    }
    
    // Coleta os vértices de corte
    char **nomes_vertices_corte = (char **) malloc(sizeof(char *) * g->vertices);
    int num_vertices_corte = 0;
    for(unsigned int i = 0; i < g->vertices; i++) {
        if(ap[i]) {
            nomes_vertices_corte[num_vertices_corte] = g->adjacencias[i].v;
            num_vertices_corte++;
        }
    }
    
    // Ordena os vértices de corte em ordem alfabética
    for(int i = 0; i < num_vertices_corte - 1; i++) {
        for(int j = i + 1; j < num_vertices_corte; j++) {
            if(strcmp(nomes_vertices_corte[i], nomes_vertices_corte[j]) > 0) {
                char *temp = nomes_vertices_corte[i];
                nomes_vertices_corte[i] = nomes_vertices_corte[j];
                nomes_vertices_corte[j] = temp;
            }
        }
    }
    
    // Constrói a string de resultado
    char *result = (char *) malloc(sizeof(char) * LINESIZE);
    strcpy(result, "");
    for(int i = 0; i < num_vertices_corte; i++) {
        if(i > 0) strcat(result, " ");
        strcat(result, nomes_vertices_corte[i]);
    }
    
    // Libera memória
    free(ap);
    free(nomes_vertices_corte);
    for(unsigned int i = 0; i < g->vertices; i++) {
        free(vertices_corte_lista[i]);
    }
    for(unsigned int i = 0; i < g->arestas; i++) {
        free(arestas_corte_lista[i]);
    }
    free(vertices_corte_lista);
    free(arestas_corte_lista);
    
    return result;
}

char *arestas_corte(grafo *g){
    if(g->vertices <= 1) {
        char *result = (char *) malloc(sizeof(char) * LINESIZE);
        strcpy(result, "");
        return result;
    }
    
    inicializa_tarjan(g);
    int time = 0;
    int *ap = (int *) calloc(g->vertices, sizeof(int)); // articulation points
    char **vertices_corte_lista = (char **) malloc(sizeof(char *) * g->vertices);
    char **arestas_corte_lista = (char **) malloc(sizeof(char *) * g->arestas);
    int vc_count = 0, ac_count = 0;
    
    // Aloca espaço para as strings
    for(unsigned int i = 0; i < g->vertices; i++) {
        vertices_corte_lista[i] = (char *) malloc(sizeof(char) * LINESIZE);
    }
    for(unsigned int i = 0; i < g->arestas; i++) {
        arestas_corte_lista[i] = (char *) malloc(sizeof(char) * LINESIZE);
    }
    
    // Executa DFS para todos os vértices não visitados
    for(unsigned int i = 0; i < g->vertices; i++) {
        if(!g->adjacencias[i].visitado) {
            tarjan_dfs(g, i, -1, &time, ap, vertices_corte_lista, &vc_count, arestas_corte_lista, &ac_count);
        }
    }
    
    // Ordena as arestas de corte em ordem alfabética
    for(int i = 0; i < ac_count - 1; i++) {
        for(int j = i + 1; j < ac_count; j++) {
            if(strcmp(arestas_corte_lista[i], arestas_corte_lista[j]) > 0) {
                char temp[LINESIZE];
                strcpy(temp, arestas_corte_lista[i]);
                strcpy(arestas_corte_lista[i], arestas_corte_lista[j]);
                strcpy(arestas_corte_lista[j], temp);
            }
        }
    }
    
    // Constrói a string de resultado
    char *result = (char *) malloc(sizeof(char) * LINESIZE);
    strcpy(result, "");
    for(int i = 0; i < ac_count; i++) {
        if(i > 0) strcat(result, " ");
        strcat(result, arestas_corte_lista[i]);
    }
    
    // Libera memória
    free(ap);
    for(unsigned int i = 0; i < g->vertices; i++) {
        free(vertices_corte_lista[i]);
    }
    for(unsigned int i = 0; i < g->arestas; i++) {
        free(arestas_corte_lista[i]);
    }
    free(vertices_corte_lista);
    free(arestas_corte_lista);
    
    return result;
}

unsigned int destroi_grafo(grafo *g){
  for(unsigned int i = 0; i < g->vertices; i++){
    vertice *v = &g->adjacencias[i];
    adjacencia *a = v->cabeca;
    if(a){
      destroi_adjacencias(a);
    }
    destroi_vertice(v);
  }

  g->adjacencias = NULL;
  free(g->nome);
  g->nome = NULL;
  free(g);
  g = NULL;
  return 1;
}
