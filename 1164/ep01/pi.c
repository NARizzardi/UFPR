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
  fesetround(FE_DOWNWARD);
  Float_t tolerance;
  int ulps;
  scanf("%lf", &tolerance.f);

  int interaction_quantity = 0;

  Float_t aprox_absolute_error, real_absolute_error;
  aprox_absolute_error.f = tolerance.f+1;
  Float_t value_n_interaction;
  value_n_interaction.f = 0;
  Float_t value_previous_interaction;
  Float_t pi_fedownward;
  /* End of variable declaration section */


  /* Start of fe_downward rounding summatory */
  while(!lowerThanTolerance(tolerance, aprox_absolute_error)){
    value_previous_interaction.f = value_n_interaction.f;
    value_n_interaction.f += nextInteraction(interaction_quantity);
    interaction_quantity++;
    aprox_absolute_error.f = calculateNewError(value_n_interaction.f, value_previous_interaction.f);
  }
  /* End of fe_downward rounding summatory */

  /* Start of fe_upward summatory */
  pi_fedownward.f = value_n_interaction.f;
  fesetround(FE_UPWARD);
  value_n_interaction.f = 0;
  interaction_quantity = 0;
  aprox_absolute_error.f = tolerance.f+1;


  while(!lowerThanTolerance(tolerance, aprox_absolute_error)){
    value_previous_interaction.f = value_n_interaction.f;
    value_n_interaction.f += nextInteraction(interaction_quantity);
    interaction_quantity++;
    aprox_absolute_error.f = calculateNewError(value_n_interaction.f, value_previous_interaction.f);

  }

  real_absolute_error.f = calculateNewError(value_n_interaction.f, M_PI);
  /* End of fe_upward rounding summatory */

  /* Hex convertion section */
  value_n_interaction.i = doubleToHexCoverter(value_n_interaction.f);
  pi_fedownward.i = doubleToHexCoverter(pi_fedownward.f);
  aprox_absolute_error.i = doubleToHexCoverter(aprox_absolute_error.f);
  real_absolute_error.i = doubleToHexCoverter(real_absolute_error.f);
  /* End of hex convertion section */

  ulps = value_n_interaction.i - pi_fedownward.i - 1;;

  /* Printing section */
  printf("%d\n", interaction_quantity);
  printFloat_t(aprox_absolute_error);
  printFloat_t(real_absolute_error);
  printFloat_t(pi_fedownward);
  printFloat_t(value_n_interaction);
  printf("%d\n", ulps);
  /* End of printing section */

  return 0;
}
