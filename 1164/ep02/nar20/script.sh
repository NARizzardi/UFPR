#!/bin/bash

METRICA="FLOPS_DP"
CPU=3


SCALING_FREQ="/sys/devices/system/cpu/cpufreq/policy${CPU}/scaling_governor"

if [ -w ${SCALING_FREQ} ]; then
    echo "performance" > ${SCALING_FREQ}
fi
for k in $METRICA
do
    
    likwid-perfctr -C ${CPU} -g ${k} -m ./inversa | grep -E '^([0-9]+(\.[0-9]+)?|([+-]?[0-9]*\.?[0-9]+[eE][+-]?[0-9]+)|DP MFLOP/s|FP_ARITH_INST_RETIRED_SCALAR_DOUBLE)' | grep -v "AVX"  | sed -e 's/      |       /,/g' -e 's/|      //g' -e 's/   |   PMC1  |     /,/g'  -e 's/|    //g' -e 's/ |//g' -e 's/MFLOP/[MFLOP/g' -e 's/s,/s],/g'
done



