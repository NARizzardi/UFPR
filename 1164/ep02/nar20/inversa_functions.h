/* Nicolas Andre Rizzardi GRR20206152*/
#ifndef INVERSA_FUNCTIONS
#define INVERSA_FUNCTIONS

/*
 * Estrutura criada para facilitar a manipulação dos dados e a passagem dos parâmetros
 */
struct matriz{
  int ordem;
  double **matrix;
};
typedef struct matriz matriz_t;

/*
 * Função utilizada para criar a estrutura da nova matriz 
 * Caso tipo_matriz > 0 então é gerado uma matriz identidade de tamanho #tipo_matriz
*/
matriz_t* nova_matriz(int tipo_matriz);

/* 
 * Função utilizada para decompor a matriz fornecida em matrizes LU
 */
void decomposicao_LU(matriz_t* matriz, matriz_t* lower, matriz_t* upper, matriz_t* identidade);

/*
 * Função utilizada para gerar a matriz inversa a partir das matrizes Lower e Upper 
 * 
 */
matriz_t* gera_inversa(matriz_t* upper, matriz_t* lower, matriz_t* identidade);


/*
 * Função utilizada para calcular o resíduo gerado pelas operações
 */
double gera_residuo(matriz_t* original, matriz_t* inversa, matriz_t* identidade);

/*
 * Função utilizada para imprimir a matriz na tela 
 */
void imprime_resultados(matriz_t* matriz, double residuo, double tempo); 

/*
 * Função utilizada para liberar a memória alocada pela matriz 
 */
void libera_matriz(matriz_t* matriz);

#endif