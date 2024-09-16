#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "floatType.h"
#include <math.h>
#include <fenv.h>

/*
  #include <float.h>
*/



int main(int argc, char const *argv[]){
  /* Variable declaration section */
  Float_t tolerance;
  printf("Entre com a tolerancia: ");
  scanf("%lf", &tolerance.f);

  int interaction_quantity = 0;

  Float_t aprox_absolute_error, real_absolute_error;
  aprox_absolute_error.f = tolerance.f+1;
  Float_t value_n_interaction;
  value_n_interaction.f = 0;
  //value_n_interaction.f = nextInteraction(interaction_quantity);
  Float_t value_previous_interaction;
  /* End of variable declaration section */
  while(!lowerThanTolerance(tolerance, aprox_absolute_error)){
    value_previous_interaction.f = value_n_interaction.f;
    value_n_interaction.f += nextInteraction(interaction_quantity);
    interaction_quantity++;
    aprox_absolute_error.f = calculateNewError(value_n_interaction.f, value_previous_interaction.f);
  }
    
  real_absolute_error.f = calculateNewError(M_PI, value_n_interaction.f);

  /* Hex convertion section */
  value_n_interaction.i = doubleToHexCoverter(value_n_interaction.f);
  value_previous_interaction.i = doubleToHexCoverter(value_previous_interaction.f);
  aprox_absolute_error.i = doubleToHexCoverter(aprox_absolute_error.f);
  real_absolute_error.i = doubleToHexCoverter(real_absolute_error.f);
  /* End of hex convertion section */

  /* Printing section */
  printf("%d\n", interaction_quantity);
  printFloat_t(aprox_absolute_error);
  printFloat_t(real_absolute_error);
  printFloat_t(value_n_interaction);
  printFloat_t(value_previous_interaction);
  printf("%d\n", interaction_quantity-1);
  /* End of printing section */

  
  return 0;
}