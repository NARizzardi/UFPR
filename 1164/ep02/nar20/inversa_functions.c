/* Nicolas Andre Rizzardi GRR20206152*/
#include "inversa_functions.h"
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

matriz_t *nova_matriz(int tipo_matriz){
  matriz_t* nova_matriz;
  nova_matriz = (matriz_t *) malloc(sizeof(matriz_t));
  if(tipo_matriz < 0){
    scanf("%d", &nova_matriz->ordem);
     
    nova_matriz->matrix = (double **) malloc(sizeof(double *) * nova_matriz->ordem);
    for(int i = 0; i < nova_matriz->ordem; ++i){
      nova_matriz->matrix[i] = (double *) malloc(sizeof(double) * nova_matriz->ordem);
      for(int j = 0; j < nova_matriz->ordem; ++j){
        scanf("%lf", &nova_matriz->matrix[i][j]);
      }
    }
    
  } else {
    nova_matriz->ordem = tipo_matriz;
    nova_matriz->matrix = (double **) malloc(sizeof(double *) * tipo_matriz);
    for(int i = 0; i < tipo_matriz; ++i){
      nova_matriz->matrix[i] = (double *) malloc(sizeof(double) * tipo_matriz);
      for(int j = 0; j < tipo_matriz; ++j){
        nova_matriz->matrix[i][j] = 0;
      }
      nova_matriz->matrix[i][i] = 1;
    }
  }

  return nova_matriz;
}

/* Função interna para encontrar o pivô */
int encontra_pivo(matriz_t* matriz, int i){
  int max = i;
  for(int k = i+1; k < matriz->ordem; ++k){
    if(matriz->matrix[k][i] - matriz->matrix[max][i] > DBL_EPSILON) max = k;
  }
  return max;
}

/* Função de uso interno para pivoteamento parcial na matriz e também na matriz identidade*/
void troca_linhas(matriz_t* matriz, matriz_t* identidade, int i, int pivo){
  double aux;
  for(int j = 0; j < matriz->ordem; ++j){
    aux = matriz->matrix[i][j];
    matriz->matrix[i][j] = matriz->matrix[pivo][j];
    matriz->matrix[pivo][j] = aux;

    aux = identidade->matrix[i][j];
    identidade->matrix[i][j] = identidade->matrix[pivo][j];
    identidade->matrix[pivo][j] = aux;
    
  }
}



void decomposicao_LU(matriz_t* matriz, matriz_t* lower, matriz_t* upper, matriz_t* identidade){
  int ordem = matriz->ordem;

  for (int i = 0; i < ordem; ++i) {
    for (int j = 0; j < ordem; ++j) {
      upper->matrix[i][j] = matriz->matrix[i][j];
    }
  }

  for(int i = 0; i < ordem; ++i){
    int pivo = encontra_pivo(upper, i);
    if(pivo > i){
      troca_linhas(upper, identidade, i, pivo);
      troca_linhas(lower, identidade, i, pivo);
    }
    
    for(int k = i + 1; k < ordem; ++k){
      double m = upper->matrix[k][i] / upper->matrix[i][i];
      lower->matrix[k][i] = m;

      for(int j = i; j < ordem; ++j){
        upper->matrix[k][j] -= upper->matrix[i][j] * m;
      }
    }
  }
  for(int i = 0; i < ordem; ++i){
    lower->matrix[i][i] = 1;
  }
}

matriz_t* gera_inversa(matriz_t* upper, matriz_t* lower, matriz_t* identidade) {
    int ordem = identidade->ordem;
    matriz_t* inversa = nova_matriz(ordem);  // Inicializa a matriz inversa
    double* y = (double*) malloc(sizeof(double) * ordem);
    
    for(int i = 0; i < ordem; ++i){

      for(int j = 0; j < ordem; ++j){
        y[j] = identidade->matrix[i][j];
        
        for(int k = 0; k < j; ++k){
          y[j] -= lower->matrix[j][k] * y[k];
        }
      }

      for(int j = ordem - 1; j >= 0; --j){
        inversa->matrix[j][i] = y[j];
        for(int k = j + 1; k < ordem; ++k){
          inversa->matrix[j][i] -= upper->matrix[j][k] * inversa->matrix[k][i];
        }
        inversa->matrix[j][i] /= upper->matrix[j][j];
      }

    }
    free (y);
    return inversa;
}

double gera_residuo(matriz_t* original, matriz_t* inversa, matriz_t* identidade){
  double multiplicacao[original->ordem][original->ordem];
  double normas[original->ordem];
  double media = 0;

  // Função para criar a matriz da multiplicação
  for(int i = 0; i < original->ordem; ++i){
      normas[i] = 0;
      for(int j = 0; j < original->ordem; ++j){
        multiplicacao[i][j] = 0;
    }
  }

  // Função para fazer a multiplicação de A por A'
  for(int i = 0; i < original->ordem; ++i){
    for(int j = 0; j < original->ordem; ++j){
      for(int k = 0; k < original->ordem; ++k){
        multiplicacao[i][j] += original->matrix[i][k] * inversa->matrix[k][j];
        
      }
    }
  }

  // Função para calcular a diferença entre I e A*A'
  for(int i = 0; i < original->ordem; ++i){
      for(int j = 0; j < original->ordem; ++j){
        double diff = multiplicacao[i][j] - identidade->matrix[i][j];
        normas[i] += diff * diff;
    }
    media += sqrt(normas[i]);
  }

  return media / original->ordem;
}

void imprime_resultados(matriz_t* matriz, double residuo, double tempo){
  printf("%d\n", matriz->ordem);
  //printf("\n");
  for(int i = 0; i < matriz->ordem; ++i){
    for(int j = 0; j < matriz->ordem; ++j){
      printf("%.15e ", matriz->matrix[i][j]);
    }
    printf("\n");
  }
  printf("%.15e\n", residuo);
  printf("%.8e\n", tempo);
}

void libera_matriz(matriz_t* matriz){
  for(int i = 0; i < matriz->ordem; ++i){
    free(matriz->matrix[i]);
  }
  free(matriz->matrix);
  free(matriz);
}