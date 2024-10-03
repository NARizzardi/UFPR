#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include "utils.h"
/*
#include <stdint.h>
#include <math.h>
*/

#define MAXIT 50
int ordem;
/*
 * Função para impressão dos resultados
*/
void imprime_resultado(int tipo, int quantidade_interacoes, int ordem, double* resultados, double* residuos, double tempo ){
  if(tipo == 0) 
    printf("EG:");
  else
    printf("GS %d:", quantidade_interacoes);

  printf("\n%.8lf ms\n", tempo);

  for(int i = 0; i < ordem; i++){
      printf(" %.12lf ", resultados[i]);
  }
  printf("\n");

  for(int i = 0; i < ordem; i++){
      printf("%.12lf ", residuos[i]);
  }
  printf("\n");

}

/*
 * Função para aplicação da solução por meio do Método de Eliminação de Gauss
*/
void eliminacao_gauss(int ordem, double** matriz_entrada, double* coeficientes){
  //imprime_resultado(0, 0, ordem);
}


/*
 * Função para aplicação da solução por meio do Método Iterativo de Gauss-Seidel
*/
void gauss_seidel(int ordem, double** matriz_entrada, double* coeficientes){
  //imprime_resultado();
}


/*
 * Função utilizada para liberar memória alocada dinâmicamente
*/
void memory_free(int ordem, double** matriz_entrada, double* coeficientes){
  for(int i = 0; i < ordem; i++){
    free(matriz_entrada[i]);
  }
  free(matriz_entrada);
  free(coeficientes);
}

int main(int argc, char const *argv[]){
  /*
   * Definindo método de arredondamento para baixo
  */
  fesetround(FE_DOWNWARD);

  /*
   * Seção de alocação dinãmica de memória
  */
  
  scanf("%d", &ordem);
  double** matriz_entrada = (double**) malloc(ordem * sizeof(double*));
  for(int i = 0; i < ordem; i++){
    matriz_entrada[i] = (double*) malloc((ordem * sizeof(double))+1);
  }
  double* coeficientes = (double*) malloc(ordem * sizeof(double));
  /*
   * Fim da seção de alocação dinâmica de memória
  */

  /*
   * Seção de população da matriz de entrada
  */
  for(int i = 0; i < ordem; i++){
    for(int j = 0; j <= ordem; j++){
      scanf("%lf", &matriz_entrada[i][j]);
      if(j == ordem)
        coeficientes[i] = matriz_entrada[i][j];
    }
  }
  /*
   * Fim da seção de população da matriz de entrada
  */


  eliminacao_gauss(ordem, matriz_entrada, coeficientes);

  gauss_seidel(ordem, matriz_entrada, coeficientes);


  /*
   * Liberação de memória
  */
  memory_free(ordem, matriz_entrada, coeficientes);
  return 0;
}

