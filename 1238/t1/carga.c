#include <stdio.h>
#include <stdlib.h>


  /*
   * Maximize:
   *  somatorio de i=1 até k de (
   *   somatorio de j=1 até n de (
   *    g[j] * p[j][i]
   *   )
   *  )

   * Sujeito a:
   *  somatorio de j=1 até n de:      p[j][i] <= w[i], para todo i
   *
   *  somatorio de j=1 até n de: t[j]*p[j][i] <= v[i], para todo i
   *
   *  a = somatorio de j=1 até n de: p[j][i]/w[i], para todo i
   *
   *  somatorio de i=1 até k de:      p[j][i] <= p[j], para todo j
   *
   *  p[j][i] > 0 para todo i, j
   */

int main(int argc, char **argv){

  /*
   * declaração de variáveis

   * g[j]:    ganho do carregamento j $$ por tonelada -> valor dado
   * t[j]:    volume do carregamento j > valor dado
   * p[j]:    peso do carregamento j -> valor dado
   * w[i]:    peso do compartimento i -> valor dado
   * v[i]:    volume do compartimento i -> valor dado

   * t[j][i]: volume do carregamento j no compartimento i -> variavel
   * p[j][i]: peso do carregamento j no compartimento i -> variavel
   */

  FILE *f = fopen("carga.lp", "w");
  int n_compartimentos;
  int n_carregamentos;
  int *w;
  int *p;
  int *v;
  int *t;
  int *g;
  scanf("%d %d", &n_compartimentos, &n_carregamentos);

  w = (int *) malloc(sizeof(int) * n_compartimentos);
  v = (int *) malloc(sizeof(int) * n_compartimentos);


  p = (int *) malloc(sizeof(int) * n_carregamentos);
  t = (int *) malloc(sizeof(int) * n_carregamentos);
  g = (int *) malloc(sizeof(int) * n_carregamentos);



  /*
   * entrada dos dados
   */

  for(int i = 0; i < n_compartimentos; ++i){
    scanf("%d %d", &w[i], &v[i]);
  }

  for(int i = 0; i < n_carregamentos; ++i){
    scanf("%d %d %d", &p[i], &t[i], &g[i]);
  }

  /*
   * inicio função objetivo
   */

  fprintf(f, "max : ");

  int i, j;
  for(i = 0; i < n_compartimentos - 1; ++i){
    for(j = 0 ; j < n_carregamentos; ++j){
      fprintf(f, "%dx%d%d + ", g[j], i, j);
    }
  }

  for(j = 0 ; j < n_carregamentos - 1; ++j){
    fprintf(f, "%dx%d%d + ", g[j], i, j);
  }

  fprintf(f, "%dx%d%d;\n\n", g[j], i, j);

  /*
   * fim função objetivo
   */

  /*
   * inicio constrição de peso do compartimento
   */

  for(i = 0; i < n_compartimentos; ++i){
    for(j = 0; j < n_carregamentos - 1; ++j){
      fprintf(f, "x%d%d + ", i, j);
    }
    fprintf(f, "x%d%d <= %d;\n", i, j, w[i]);
  }

  fprintf(f, "\n");

  /*
   * fim constrição de peso do compartimento
   */

  /*
   * inicio constrição de volume relativo ao peso
   */


  for(i = 0; i < n_compartimentos; ++i){
    for(j = 0; j < n_carregamentos - 1; ++j){
      fprintf(f, "%dx%d%d + ", t[j], i, j);
    }
    fprintf(f, "%dx%d%d <= %d;\n", t[j], i, j, v[i]);
  }

  fprintf(f, "\n");

  /*
   * fim constrição de volume
   */

  /*
   * inicio constrição de peso do carregamento
   */

  for(j = 0; j < n_carregamentos; ++j){
    for(i = 0; i < n_compartimentos - 1; ++i){
      fprintf(f, "x%d%d + ", i, j);
    }
    fprintf(f, "x%d%d <= %d;\n", i, j, p[j]);
  }

  fprintf(f, "\n");

  /*
   * fim constrição de peso do carregamento
   */

  /*
   * inicio constrição de peso do compartimento
   */

  for(i = 0; i < n_compartimentos; ++i){
    fprintf(f, "%da = ", w[i]);
    for(j = 0; j < n_carregamentos - 1; ++j){
      fprintf(f, "x%d%d + ", i, j);
    }
    fprintf(f, "x%d%d;\n", i, j);
  }

  fprintf(f, "\n");

  /*
   * fim constrição de peso do compartimento
   */

  /*
   * inicio constrição de peso maior ou igual a zero
   */

  for(i = 0; i < n_compartimentos; ++i){
    for(j = 0; j < n_carregamentos; ++j){
        fprintf(f, "x%d%d >= 0;\n", i, j);
    }
  }

  fprintf(f, "\n");

  /*
   * fim constrição de peso não negativo
   */




  /*
   * limpeza dos dados
   */
  fclose(f);
  free(w);
  free(v);
  free(p);
  free(t);
  free(g);

 return 0;
}

