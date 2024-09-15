#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "floatType.h"

#define ERROR 0.000001


double nextInteraction(int interaction_quantity){
    double ret = 1;
    double denominator, numerator;
    double twoPotency = 1;
    double kFactorial = 1;
    int denominatorFactorial;
    denominator = 1;
    denominatorFactorial = (2*interaction_quantity) + 1;

    for(int k = interaction_quantity; k > 0; k--){
        kFactorial = kFactorial * k;
        twoPotency = twoPotency * 2;
        denominator = denominator * denominatorFactorial;

        denominatorFactorial-- ;

        denominator = denominator * denominatorFactorial;

        denominatorFactorial--;
    }

    kFactorial = kFactorial * kFactorial;
    numerator = twoPotency * kFactorial;
    ret = numerator / denominator;
    ret = ret;
    
    return ret * 2;
}

int lowerThanTolerance(Float_t tolerance, Float_t aprox_absolute_error){
    if((aprox_absolute_error.f-tolerance.f) <= ERROR)
        return 1;
    return 0;
}

uint64_t doubleToHexCoverter(double d)
{
  return (*(uint64_t*)&d);
}

double calculateNewError(double value_n_interaction, double value_previous_interaction){
    return value_n_interaction - value_previous_interaction;
}

/* imprime a union Float_t como ponto flutuante, hexadecimal e 
 * suas partes na forma de inteiros */
void printFloat_t( Float_t num )
{
   printf("%.15e %08lX\n",
            num.f, num.i); 
} 