# Relatorio TP03
## Introdução
**Nicolas Andre Rizzardi** GRR20206152
Para o **EP03** eu utilizei a máquina **H53** disponível no **Lab12**

## Alterações
As alterações que eu realizei foram apenas em código, conforme abaixo

Na função `montaSL`, primeiramente tentei fazer um *loop fusion* porém essa função acabou gerando uma complexidade maior no código ao tentar aplicar outras técnicas de otimização, então acabei optando por primeiramente remover as custosas operações `pow()` colocando duas variáveis incrementais para ter controle da potenciação uma sendo a `pow_xk_i` que é utilizada tanto para `A[i][j]`, quanto para `B[i]` e também a variável `pow_xk_j` que eu utilizei para conseguir replicar a operação `pow(x[k], i+j)`, depois apliquei a técnica de *Unroll & Jam*, além disso foi removido o stride do acesso à matriz, começando o laço pela variável **k**.

Já na função `eliminacaoGauss` a alteração se deu após o pivoteamento, aplicando novamente um *Unroll & Jam*. O pivoteamento foi uma função que não enxerguei como otimizar o seu *stride*, mudar a ordem de acesso à matriz pelo pivoteamento geraria um *stride* em todos os demais acessos à matriz.

A função `retrossubs` foi aplicado um *Unroll & Jam* e após isso não houveram outras possibilidades de otimização.

A última alteração veio na função `P`, onde eu apliquei a técnica de *Unroll & Jam* e também removi a função `pow()`, colocando uma variável incremental para ter o controle da potenciação.

## Resultados

## Topologia
```
--------------------------------------------------------------------------------
CPU name:	Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz
CPU type:	Intel Coffeelake processor
CPU stepping:	9
********************************************************************************
Hardware Thread Topology
********************************************************************************
Sockets:		1
Cores per socket:	4
Threads per core:	1
--------------------------------------------------------------------------------
HWThread	Thread		Core		Socket		Available
0		0		0		0		*
1		0		1		0		*
2		0		2		0		*
3		0		3		0		*
--------------------------------------------------------------------------------
Socket 0:		( 0 1 2 3 )
--------------------------------------------------------------------------------
********************************************************************************
Cache Topology
********************************************************************************
Level:			1
Size:			32 kB
Type:			Data cache
Associativity:		8
Number of sets:		64
Cache line size:	64
Cache type:		Non Inclusive
Shared by threads:	1
Cache groups:		( 0 ) ( 1 ) ( 2 ) ( 3 )
--------------------------------------------------------------------------------
Level:			2
Size:			256 kB
Type:			Unified cache
Associativity:		4
Number of sets:		1024
Cache line size:	64
Cache type:		Non Inclusive
Shared by threads:	1
Cache groups:		( 0 ) ( 1 ) ( 2 ) ( 3 )
--------------------------------------------------------------------------------
Level:			3
Size:			6 MB
Type:			Unified cache
Associativity:		12
Number of sets:		8192
Cache line size:	64
Cache type:		Inclusive
Shared by threads:	4
Cache groups:		( 0 1 2 3 )
--------------------------------------------------------------------------------
********************************************************************************
NUMA Topology
********************************************************************************
NUMA domains:		1
--------------------------------------------------------------------------------
Domain:			0
Processors:		( 0 1 2 3 )
Distances:		10
Free memory:		333.074 MB
Total memory:		7825.65 MB
--------------------------------------------------------------------------------


********************************************************************************
Graphical Topology
********************************************************************************
Socket 0:
+---------------------------------------------+
| +--------+ +--------+ +--------+ +--------+ |
| |    0   | |    1   | |    2   | |    3   | |
| +--------+ +--------+ +--------+ +--------+ |
| +--------+ +--------+ +--------+ +--------+ |
| |  32 kB | |  32 kB | |  32 kB | |  32 kB | |
| +--------+ +--------+ +--------+ +--------+ |
| +--------+ +--------+ +--------+ +--------+ |
| | 256 kB | | 256 kB | | 256 kB | | 256 kB | |
| +--------+ +--------+ +--------+ +--------+ |
| +-----------------------------------------+ |
| |                   6 MB                  | |
| +-----------------------------------------+ |
+---------------------------------------------+

```