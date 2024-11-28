/* Nicolas Andre Rizzardi GRR20206152*/
#include <fenv.h>
#include <stdio.h>
#include "likwid.h"
#include "inversa_functions.h"
#include "utils.h"

int main(){
  LIKWID_MARKER_INIT;

  LIKWID_MARKER_START ("Inversa_LIKWID");
  fesetround(FE_DOWNWARD);

  /* Declaração das variáveis utilizadas */
  matriz_t *matriz = nova_matriz(-1);
  matriz_t *identidade = nova_matriz(matriz->ordem);  
  matriz_t *upper = nova_matriz(matriz->ordem);
  matriz_t *lower = nova_matriz(matriz->ordem);
  matriz_t *inversa = nova_matriz(matriz->ordem);
  double residuo = 0;
  /* Fim do bloco de declaração de variáveis */
  

  /* Bloco de processamento dos dados para encontrar a matriz inversa e seu resíduo */
  double tempo = timestamp();
  decomposicao_LU(matriz, lower, upper, identidade);
  inversa = gera_inversa(matriz, lower, identidade);
  
  tempo = timestamp() - tempo;
  residuo = gera_residuo(matriz, inversa, identidade);

  /* Fim do bloco de processamento */
  

  /* Bloco de impressão e liberação de memória */
  imprime_resultados(inversa, residuo, tempo); //trocar matriz por inversa ao finalizar

  libera_matriz(matriz);
  libera_matriz(identidade);
  libera_matriz(lower);
  libera_matriz(upper);
  libera_matriz(inversa);

  /* Fim do bloco de impressão e liberação de memória */
  LIKWID_MARKER_STOP ("Inversa_LIKWID");
    
  LIKWID_MARKER_CLOSE;
  return 0;
}