#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <fenv.h>
#include <math.h>
#include <stdint.h>
#include "likwid.h"
#include "utils.h"

/////////////////////////////////////////////////////////////////////////////////////
//   AJUSTE DE CURVAS
/////////////////////////////////////////////////////////////////////////////////////

void montaSL(double **A, double *b, int n, long long int p, double *x, double *y) {
  LIKWID_MARKER_START("SL_V1");
  
  double *powxk  = (double *) malloc(p * sizeof(double));
  double *powxkj = (double *) malloc(p * sizeof(double));

  for (long long int k = 0; k < p; ++k) {
    powxk[k] = 1.0;
    powxkj[k] = powxk[k];
  }
  
  for (long long int i = 0; i < n; ++i){
    for (long long int j = 0; j < n; ++j) {
      A[i][j] = 0.0;
      for (long long int k = 0; k < p-p%4; k+=4) { // unroll & jam
	      A[i][j] += powxkj[k];

        A[i][j] += powxkj[k+1];

        A[i][j] += powxkj[k+2];

        A[i][j] += powxkj[k+3];
      }
      for (long long int k = p-p%4; k < p; ++k) { // loop remainder
	      A[i][j] += powxkj[k];
      }


      for (long long int k = 0; k < p-p%4; k+=4) { // unroll & jam
        powxkj[k] *= x[k];
        
        powxkj[k+1] *= x[k+1];
        
        powxkj[k+2] *= x[k+2];
        
        powxkj[k+3] *= x[k+3];
      }
      for (long long int k = p-p%4; k < p; ++k) { // loop remainder
        powxkj[k] *= x[k];
      }

    }

    for (long long int k = 0; k < p-p%4; k+=4) {   // unroll & jam
      powxk[k] *= x[k];
      powxkj[k] = powxk[k];
      
      powxk[k+1] *= x[k+1];
      powxkj[k+1] = powxk[k+1];
      
      powxk[k+2] *= x[k+2];
      powxkj[k+2] = powxk[k+2];
      
      powxk[k+3] *= x[k+3];
      powxkj[k+3] = powxk[k+3];
    }
    for (long long int k = p-p%4; k < p; ++k) {    // loop remainder
      powxk[k] *= x[k];
      powxkj[k] = powxk[k];
    }

  }

  for (long long int k = 0; k < p; ++k) {
    powxk[k] = 1.0;
  }
  

  for (long long int i = 0; i < n; ++i) {
    b[i] = 0.0;
    for (long long int k = 0; k < p-p%4; k+=4){    // unroll & jam
      b[i] += powxk[k] * y[k];
      
      b[i] += powxk[k+1] * y[k+1];
      
      b[i] += powxk[k+2] * y[k+2];
      
      b[i] += powxk[k+3] * y[k+3];
    }
    for (long long int k = p-p%4; k < p; ++k){     // loop remainder
      b[i] += powxk[k] * y[k];
    }
    
    for (long long int k = 0; k < p-p%4; k+=4){    // unroll & jam
      powxk[k] *= x[k];
      powxk[k+1] *= x[k+1];
      powxk[k+2] *= x[k+2];
      powxk[k+3] *= x[k+3];
    }
    for (long long int k = p-p%4; k < p; ++k){     // loop remainder
      powxk[k] *= x[k];
    }
  }

  LIKWID_MARKER_STOP("SL_V1");
}

void eliminacaoGauss(double **A, double *b, long long int n) {
  for (long long int i = 0; i < n; ++i) {
    long long int iMax = i;
    for (long long int k = i + 1; k < n; ++k) {
      if (fabs(A[k][i]) > fabs(A[iMax][i])) {
        iMax = k;
      }
    }
    if (iMax != i) {
      double *tmp, aux;
      tmp = A[i];
      A[i] = A[iMax];
      A[iMax] = tmp;

      aux = b[i];
      b[i] = b[iMax];
      b[iMax] = aux;
    }

    for (long long int k = i + 1; k < n; ++k) {
      double m = A[k][i] / A[i][i];
      A[k][i] = 0.0;
      long long int j;
      for (j = i + 1; j <= n - 4; j += 4) {
        A[k][j] -= A[i][j] * m;
        A[k][j + 1] -= A[i][j + 1] * m;
        A[k][j + 2] -= A[i][j + 2] * m;
        A[k][j + 3] -= A[i][j + 3] * m;
      }
      for (; j < n; ++j) {
        A[k][j] -= A[i][j] * m;
      }
      b[k] -= b[i] * m;
    }
  }
}

// void eliminacaoGauss(double **A, double *b, long long int n) {
//   for (long long int i = 0; i < n; ++i) {
//     long long int iMax = i;
//     for (long long int k = i+1; k < n; ++k)
//       if (A[k][i] > A[iMax][i])
// 	      iMax = k;
//     if (iMax != i) {
//       double *tmp, aux;
//       tmp = A[i];
//       A[i] = A[iMax];
//       A[iMax] = tmp;

//       aux = b[i];
//       b[i] = b[iMax];
//       b[iMax] = aux;
//     }

//     for (long long int k = i+1; k < n; ++k) {
//       double m = A[k][i] / A[i][i];
//       A[k][i]  = 0.0;
//       for (long long int j = i+1; j < n-n%4; j+=4){
// 	      A[k][j] -= A[i][j]*m;
//         A[k][j+1] -= A[i][j+1]*m;
//         A[k][j+2] -= A[i][j+2]*m;
//         A[k][j+3] -= A[i][j+3]*m;
//       }
//       for (long long int j = n-n%4; j < n; ++j)
//         A[k][j] -= A[i][j]*m;
//       b[k] -= b[i]*m;
//     }
//   }
// }

void retrossubs(double **A, double *b, double *x, long long int n) {
  for (long long int i = n-1; i >= 0; --i) {
    x[i] = b[i];
    for (long long int j = i+1; j < n-n%4; j+=4){
      x[i] -= A[i][j]*x[j];
      x[i] -= A[i][j+1]*x[j+1];
      x[i] -= A[i][j+2]*x[j+2];
      x[i] -= A[i][j+3]*x[j+3];
    }
    for (long long int j = n-n%4; j < n; ++j){
      x[i] -= A[i][j]*x[j];
    }
    x[i] /= A[i][i];
  }
}

// void retrossubs(double **A, double *b, double *x, long long int n) {
//   for (long long int i = n - 1; i >= 0; --i) {
//     double soma = b[i];
    
//     long long int j;
//     for (j = i + 1; j <= n - 4; j += 4) {
//       soma -= A[i][j] * x[j];
//       soma -= A[i][j + 1] * x[j + 1];
//       soma -= A[i][j + 2] * x[j + 2];
//       soma -= A[i][j + 3] * x[j + 3];
//     }

//     for (; j < n; ++j) {
//       soma -= A[i][j] * x[j];
//     }

//     x[i] = soma / A[i][i];
//   }
// }

// void retrossubs(double **A, double *b, double *x, long long int n) {
//   for (long long int i = n-1; i >= 0; --i) {
//     double soma = b[i];
    
//     for (long long int j = i+1; j <= n-n%4 ; j+=4){
//       soma -=   A[i][j] * x[j];
//       soma -= A[i][j+1] * x[j+1];
//       soma -= A[i][j+2] * x[j+2];
//       soma -= A[i][j+3] * x[j+3];
//     }

//     for (long long int j = n-n%4; j < n ; ++j){
//       soma -= A[i][j] * x[j];
//     }
    

//     x[i] = soma / A[i][i];
//   }
// }

double P(double x, long long int N, double *alpha) {
  double Px = alpha[0];
  double powX = x;
  for (long long int i = 1; i <= N; ++i){
    Px += alpha[i]*powX;
    powX *= x;
  }
  
  return Px;
}

int main() {
  LIKWID_MARKER_INIT;
  long long int N, n;
  long long int K, p;

  scanf("%lld %lld", &N, &K);
  p = K;   // quantidade de pontos
  n = N+1; // tamanho do SL (grau N + 1)

  double *x = (double *) malloc(sizeof(double) * p);
  double *y = (double *) malloc(sizeof(double) * p);

  // ler numeros
  for (long long int i = 0; i < p; ++i)
    scanf("%lf %lf", x+i, y+i);

  double **A = (double **) malloc(sizeof(double *) * n);
  for (long long int i = 0; i < n; ++i)
    A[i] = (double *) malloc(sizeof(double) * n);
  
  double *b = (double *) malloc(sizeof(double) * n);
  double *alpha = (double *) malloc(sizeof(double) * n); // coeficientes ajuste

  // (A) Gera SL
  double tSL = timestamp();
  montaSL(A, b, n, p, x, y);
  tSL = timestamp() - tSL;

  // (B) Resolve SL
  double tEG = timestamp();
  LIKWID_MARKER_START("EG_V1");
  eliminacaoGauss(A, b, n); 
  retrossubs(A, b, alpha, n); 
  LIKWID_MARKER_STOP("EG_V1");
  tEG = timestamp() - tEG;

  // Imprime coeficientes
 for (long long int i = 0; i < n; ++i)
   printf("%1.15e ", alpha[i]);
 puts("");

  // Imprime resíduos
//  for (long long int i = 0; i < p; ++i)
//    printf("%1.15e ", fabs(y[i] - P(x[i],N,alpha)) );
//  puts("");

  // Imprime os tempos
  printf("%lld %1.10e %1.10e\n", K, tSL, tEG);
  LIKWID_MARKER_CLOSE;
  return 0;
}
