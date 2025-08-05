#!/bin/bash

./escalona < testes/teste1.in > teste1.sol
./escalona < testes/teste2.in > teste2.sol
./escalona < testes/teste3.in > teste3.sol

echo "teste1.sol"
diff teste1.sol testes/teste1.out

echo "teste2.sol"
diff teste2.sol testes/teste2.out

echo "teste3.sol"
diff teste3.sol testes/teste3.out