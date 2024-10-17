#include "likwid.h"
#include <stdio.h>

int main(){
  LIKWID_MARKER_INIT;

  LIKWID_MARKER_START ("Inversa_LIKWID");
  
  // criar variaveis
  // alocar memoria

  // entrada de dados
  printf("4.5\n4.5 -1 0 0\n-1 4 -1 0\n0 -1 4 -1\n0 0 -1 4\n");
  // processamento

  // impressao dos resultados

  // liberacao de memoria

  LIKWID_MARKER_STOP ("Inversa_LIKWID");
    
  LIKWID_MARKER_CLOSE;
  return 0;
}