#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "floatType.h"

/*
 Function used to calculate the next term of the summatory
*/
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


/*
 Function used to check if the approximate absolute
 error is lesser than the stipulated tolerance
*/
int lowerThanTolerance(Float_t tolerance, Float_t aprox_absolute_error){
    if((aprox_absolute_error.f-tolerance.f) <= DBL_EPSILON)
        return 1;
    return 0;
}

/*
 Function used to conver the floating point number
 to integer used in the hex print
*/
uint64_t doubleToHexCoverter(double d)
{
  return (*(uint64_t*)&d);
}

/*
 Function to calculate the error
 it can be both approximate error
 or the real error
*/
double calculateNewError(double value_n_interaction, double value_previous_interaction){
    double result = value_n_interaction - value_previous_interaction;
    return result;
}

/* imprime a union Float_t como ponto flutuante, hexadecimal e 
 * suas partes na forma de inteiros */
void printFloat_t( Float_t num )
{
   printf("%.15e %08lX\n",
            num.f, num.i); 
} 