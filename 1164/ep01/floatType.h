#ifndef FLOATTYPE_H
#define FLOATTYPE_H

typedef union {
    uint64_t i;
    double f;
} Float_t;

double nextInteraction(int interaction_quantity, int* n_flops);
int lowerThanTolerance(Float_t tolerance, Float_t aprox_absolute_error);
double calculateNewError(double value_n_interaction, double value_previous_interaction);
uint64_t doubleToHexCoverter(double d);

void printFloat_t( Float_t num );
#endif