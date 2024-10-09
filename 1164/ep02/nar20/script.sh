#!/bin/bash

METRICA="FLOPS_DP"
CPU=3

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"
SCALING_FREQ="/sys/devices/system/cpu/cpufreq/policy${CPU}/scaling_governor"

if [ -w ${SCALING_FREQ} ]; then
    echo "performance" > ${SCALING_FREQ}
fi

for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./inversa >${k}_SemOtimiz.log
done

if [ -w ${SCALING_FREQ} ]; then
    echo "powersave" > ${SCALING_FREQ}
fi

echo ''
echo '-----------------------------------'
if [ -f FLOPS_DP_SemOtimiz.log ]; then
    echo 'Configuração LIKWID: SUCESSO'
    echo ''
    ls FLOPS_*.log
    echo ''
else
    echo 'Configuração LIKWID: FALHA'
fi
echo '-----------------------------------'
echo ''

