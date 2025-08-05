#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ATRIBUTOS 26 // Para atributos de 'A' a 'Z'
#define MAX_OPERACOES 100 // Deve ser o mesmo que o tamanho da lista de transações
#define LINESIZE 100
int n_transacoes = 0;
int n_escalonamentos = 0;
struct transaction{
  int identificador;
  char operacao;
  char atributo;
  int aberta;
}; typedef struct transaction transaction_t;

struct escalonamento{
  int *identificadores;
  int tamanho;
  char *serializavel;
  char *equivalente; 
}; typedef struct escalonamento escalonamento_t;

typedef struct {
    int relacoes_leitura[MAX_OPERACOES][2]; // [i][0]=leitor, [i][1]=escritor
    int num_leituras;
    int escritas_finais[MAX_ATRIBUTOS]; // escritas_finais['A'] = ID da transação da última escrita
} propriedades_t;

void destroi_lista_escalonamentos(escalonamento_t **lista_escalonamentos);
void destroi_lista_transacoes(transaction_t **lista_transacoes);
void testar_permutacoes(int* ids, int inicio, int fim, escalonamento_t* escalonamento, transaction_t** lista_transacoes,int n_ops, propriedades_t* props_originais, short int *encontrado);

void nova_transacao(transaction_t *transacao, int transacao_id, char operacao, char atributo) {
  transacao->identificador = transacao_id;
  transacao->operacao = operacao;
  transacao->atributo = atributo;
}

transaction_t **cria_lista_transacoes(){
  transaction_t **lista_transacoes = (transaction_t **)malloc(100 * sizeof(transaction_t *));
  for(int i = 0; i < 100; i++) {
    lista_transacoes[i] = (transaction_t *)malloc(sizeof(transaction_t));
    transaction_t *transacao = lista_transacoes[i];
    transacao->identificador = 0;
    transacao->aberta = 0;
    transacao->operacao = '\0';
    transacao->atributo = '\0';
  }

  char *entrada = (char*)malloc(LINESIZE * sizeof(char));
  char *token;
  int tempo; int transacao_id;
  char operacao; char atributo;

  while(fgets(entrada, LINESIZE, stdin)){
    token = strtok(entrada, " ");
    tempo = atoi(token);
    token = strtok(NULL, " ");
    transacao_id = atoi(token);
    token = strtok(NULL, " ");
    operacao = token[0];
    token = strtok(NULL, " ");
    atributo = token[0];
    transaction_t *transacao = lista_transacoes[tempo];
    nova_transacao(transacao, transacao_id, operacao, atributo);
    n_transacoes = tempo;
  }
  free(entrada);
  return lista_transacoes;
}

escalonamento_t **cria_lista_escalonamentos(transaction_t **lista_transacoes){
  escalonamento_t **lista_escalonamentos = (escalonamento_t **)malloc(100 * sizeof(escalonamento_t *));
  
  // Inicializa todos os ponteiros como NULL
  for(int i = 0; i < 100; i++){
    lista_escalonamentos[i] = NULL;
  }
  
  // Para cada atributo, encontra grupos de transações que se sobrepõem no tempo
  char atributos_processados[100];
  int num_processados = 0;
  
  for(int i = 0; i <= n_transacoes; i++) {
    if(lista_transacoes[i]->identificador != 0) {
      char atributo_atual = lista_transacoes[i]->atributo;
      
      // Pula commits e atributos já processados
      if(atributo_atual == '-') continue;
      
      int ja_processado = 0;
      for(int j = 0; j < num_processados; j++) {
        if(atributos_processados[j] == atributo_atual) {
          ja_processado = 1;
          break;
        }
      }
      if(ja_processado) continue;
      
      // Marca como processado
      atributos_processados[num_processados++] = atributo_atual;
      
      // Encontra todas as transações que acessam este atributo
      int transacoes_atributo[20][2]; // [id_transacao][inicio, fim]
      int count_trans = 0;
      
      for(int j = 0; j <= n_transacoes; j++) {
        transaction_t *transacao = lista_transacoes[j];
        if(transacao->identificador != 0 && transacao->atributo == atributo_atual) {
          int transacao_id = transacao->identificador;
          
          // Verifica se já foi registrada
          int ja_existe = -1;
          for(int k = 0; k < count_trans; k++) {
            if(transacoes_atributo[k][0] == transacao_id) {
              ja_existe = k;
              break;
            }
          }
          
          if(ja_existe == -1) {
            // Nova transação
            transacoes_atributo[count_trans][0] = transacao_id;
            transacoes_atributo[count_trans][1] = j; // tempo de início
            count_trans++;
          }
        }
      }
      
      // Encontra o tempo de commit de cada transação
      for(int j = 0; j < count_trans; j++) {
        int transacao_id = transacoes_atributo[j][0];
        int tempo_commit = n_transacoes + 1; // default: não fez commit
        
        for(int k = 0; k <= n_transacoes; k++) {
          if(lista_transacoes[k]->identificador == transacao_id && 
             lista_transacoes[k]->operacao == 'C') {
            tempo_commit = k;
            break;
          }
        }
        
        // Adiciona tempo de fim (substitui o tempo de início na segunda posição)
        // Agora transacoes_atributo[j] = [id, tempo_fim]
        transacoes_atributo[j][1] = tempo_commit;
        // Para debug, vamos usar: [id, tempo_commit]
      }
      
      // Agrupa transações que se sobrepõem no tempo
      int grupos[20][10]; // grupos de transações que se sobrepõem
      int tamanho_grupos[20];
      int num_grupos = 0;
      
      for(int j = 0; j < count_trans; j++) {
        int transacao_id = transacoes_atributo[j][0];
        int tempo_commit = transacoes_atributo[j][1];
        
        // Procura um grupo existente onde esta transação se sobrepõe
        int grupo_encontrado = -1;
        for(int g = 0; g < num_grupos; g++) {
          for(int t = 0; t < tamanho_grupos[g]; t++) {
            int outra_id = grupos[g][t];
            int outro_commit = -1;
            
            // Encontra o tempo de commit da outra transação
            for(int k = 0; k < count_trans; k++) {
              if(transacoes_atributo[k][0] == outra_id) {
                outro_commit = transacoes_atributo[k][1];
                break;
              }
            }
            
            // Verifica se há sobreposição temporal
            // Duas transações se sobrepõem se uma começa antes da outra fazer commit
            int inicio_atual = -1, inicio_outro = -1;
            for(int m = 0; m <= n_transacoes; m++) {
              if(lista_transacoes[m]->identificador == transacao_id && inicio_atual == -1) {
                inicio_atual = m;
              }
              if(lista_transacoes[m]->identificador == outra_id && inicio_outro == -1) {
                inicio_outro = m;
              }
            }
            
            if((inicio_atual < outro_commit && tempo_commit > inicio_outro) ||
               (inicio_outro < tempo_commit && outro_commit > inicio_atual)) {
              grupo_encontrado = g;
              break;
            }
          }
          if(grupo_encontrado != -1) break;
        }
        
        if(grupo_encontrado == -1) {
          // Criar novo grupo
          grupos[num_grupos][0] = transacao_id;
          tamanho_grupos[num_grupos] = 1;
          num_grupos++;
        } else {
          // Adicionar ao grupo existente
          grupos[grupo_encontrado][tamanho_grupos[grupo_encontrado]] = transacao_id;
          tamanho_grupos[grupo_encontrado]++;
        }
      }
      
      // Criar escalonamentos para grupos com mais de uma transação
      for(int g = 0; g < num_grupos; g++) {
        if(tamanho_grupos[g] > 1) {
          lista_escalonamentos[n_escalonamentos] = malloc(sizeof(escalonamento_t));
          lista_escalonamentos[n_escalonamentos]->identificadores = (int *) malloc(sizeof(int) * tamanho_grupos[g]);
          lista_escalonamentos[n_escalonamentos]->tamanho = tamanho_grupos[g];
          lista_escalonamentos[n_escalonamentos]->serializavel = (char *) malloc(sizeof(char) * 3);
          lista_escalonamentos[n_escalonamentos]->equivalente = (char *) malloc(sizeof(char) * 3);
          strcpy(lista_escalonamentos[n_escalonamentos]->serializavel, "SS");
          strcpy(lista_escalonamentos[n_escalonamentos]->equivalente, "SV");
          
          for(int t = 0; t < tamanho_grupos[g]; t++) {
            lista_escalonamentos[n_escalonamentos]->identificadores[t] = grupos[g][t];
          }
          
          n_escalonamentos++;
        }
      }
    }
  }
  
  return lista_escalonamentos;
}

void imprime_transacoes(transaction_t **lista_transacoes){
  for(int i = 0; i < n_transacoes; i++){
    if(lista_transacoes[i]->identificador != 0) {
      transaction_t *transacao = lista_transacoes[i];
      printf("Tempo: %d, Transacao ID: %d, Operacao: %c, Atributo: %c\n", 
        i, transacao->identificador, transacao->operacao, transacao->atributo);
    }   
  }
}

void imprime_escalonamentos(escalonamento_t **lista_escalonamentos, transaction_t **lista_transacoes, int n_escalonamentos) {
    printf("\n=== ESCALONAMENTOS (Transações que acessam o mesmo atributo antes do commit) ===\n");
    for (int i = 0; i < n_escalonamentos; i++) {
        printf("Escalonamento %d: ", i + 1);
        for (int j = 0; j < lista_escalonamentos[i]->tamanho; j++) {
            printf("T%d", lista_escalonamentos[i]->identificadores[j]);
            if (j < lista_escalonamentos[i]->tamanho - 1) {
                printf(", ");
            }
        }
        printf(" (tamanho: %d)\n", lista_escalonamentos[i]->tamanho);
    }
    if (n_escalonamentos == 0) {
        printf("Nenhum escalonamento com conflitos encontrado.\n");
    }
}

int transacao_no_escalonamento(escalonamento_t *escalonamento, int identificador){
  for(int i = 0; i < escalonamento->tamanho; i++){
    if(escalonamento->identificadores[i] == identificador) return 1;
  }
  return 0;
}

void matriz_quadrada(int **matriz){
  int **aux = (int **)malloc(n_transacoes * sizeof(int *));
  for(int i = 0; i < n_transacoes; i++) {
      aux[i] = (int *)malloc(n_transacoes * sizeof(int));
      for(int j = 0; j < n_transacoes; j++) {
          aux[i][j] = 0; // Inicializa a matriz com zeros
      }
  }

  for (int i = 0; i < n_transacoes; i++) {
    for (int j = 0; j < n_transacoes; j++) {
      for (int k = 0; k < n_transacoes; k++) {
        aux[i][j] += matriz[i][k] * matriz[k][j];
      }
    }
  }

  for(int i = 0; i < n_transacoes; i++) {
      for(int j = 0; j < n_transacoes; j++) {
          matriz[i][j] = aux[i][j];
      }
  }
  for(int i = 0; i < n_transacoes; i++) {
    free(aux[i]);
  }
  free(aux);
}

void teste_seriabilidade(escalonamento_t *escalonamento, transaction_t **lista_transacoes) {
  
  int **matriz_seriabilidade = (int **)malloc(n_transacoes * sizeof(int *));
  for(int i = 0; i < n_transacoes; i++) {
      matriz_seriabilidade[i] = (int *)malloc(n_transacoes * sizeof(int));
      for(int j = 0; j < n_transacoes; j++) {
          matriz_seriabilidade[i][j] = 0; // Inicializa a matriz com zeros
      }
  }
  
  for(int i = 0; i < n_transacoes; i++) {
    transaction_t *transacao = lista_transacoes[i];
    if(transacao_no_escalonamento(escalonamento, transacao->identificador)){
      if(transacao->operacao == 'R' ) {
        for(int j = i + 1; j < n_transacoes; j++) {
          transaction_t *aux = lista_transacoes[j];
          // Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti
          if(aux->operacao == 'W' && aux->atributo == transacao->atributo && aux->identificador!= transacao->identificador) { 
            matriz_seriabilidade[transacao->identificador][aux->identificador] = 1; 
          }
        }
      }
      if(transacao->operacao == 'W') {
        for(int j = i + 1; j < n_transacoes; j++) {
          transaction_t *aux = lista_transacoes[j];
          // Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
          if(aux->operacao == 'R' && aux->atributo == transacao->atributo && aux->identificador!= transacao->identificador) { 
            matriz_seriabilidade[transacao->identificador][aux->identificador] = 1;
          }
          // Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti
          if(aux->operacao == 'W' && aux->atributo == transacao->atributo && aux->identificador!= transacao->identificador) { 
            matriz_seriabilidade[transacao->identificador][aux->identificador] = 1;
          }
        }
      }
    }
  }
  matriz_quadrada(matriz_seriabilidade);
  for(int i = 0; i < n_transacoes; i++){
    if(matriz_seriabilidade[i][i] != 0){
      strcpy(escalonamento->serializavel, "NS");
      break;
    }
  }

  for(int i = 0; i < n_transacoes; i++) {
    free(matriz_seriabilidade[i]);
  }
  free(matriz_seriabilidade);
}

// Analisa um conjunto de operações e extrai suas propriedades de leitura e escrita.
void analisar_propriedades(transaction_t** ops, int n_ops, propriedades_t* props) {
    props->num_leituras = 0;
    // Inicializa escritas como 0 (nenhuma transação escreveu ainda)
    memset(props->escritas_finais, 0, sizeof(props->escritas_finais));
    int ultimas_escritas_temp[MAX_ATRIBUTOS] = {0};

    for (int i = 0; i < n_ops; i++) {
        transaction_t* op = ops[i];
        if (op->identificador == 0 || op->operacao == 'C') continue;

        char attr = op->atributo;
        if (attr >= 'A' && attr <= 'Z') {
            int idx_attr = attr - 'A';
            if (op->operacao == 'W') {
                ultimas_escritas_temp[idx_attr] = op->identificador;
            } else if (op->operacao == 'R') {
                props->relacoes_leitura[props->num_leituras][0] = op->identificador;
                props->relacoes_leitura[props->num_leituras][1] = ultimas_escritas_temp[idx_attr];
                props->num_leituras++;
            }
        }
    }
    // Copia o estado final das últimas escritas
    memcpy(props->escritas_finais, ultimas_escritas_temp, sizeof(ultimas_escritas_temp));
}


//Compara as propriedades (relações de leitura e escritas finais) de dois escalonamentos.
short int comparar_propriedades(propriedades_t* p1, propriedades_t* p2) {
    if (p1->num_leituras != p2->num_leituras) return 0;

    // Compara as escritas finais de uma vez
    if (memcmp(p1->escritas_finais, p2->escritas_finais, sizeof(p1->escritas_finais)) != 0) {
        return 0;
    }

    // Compara cada relação de leitura
    for (int i = 0; i < p1->num_leituras; i++) {
        if (p1->relacoes_leitura[i][0] != p2->relacoes_leitura[i][0] ||
            p1->relacoes_leitura[i][1] != p2->relacoes_leitura[i][1]) {
            return 0;
        }
    }
    return 1;
}

// Verifica se tem uma escrita quando uma transação Ti escreve em X sem ter lido X antes
short int tem_escrita_cega(escalonamento_t* escalonamento, transaction_t** lista_transacoes, int n_ops) {
    for (int i = 0; i < n_ops; i++) {
        transaction_t* op_w = lista_transacoes[i];
        if (op_w->operacao == 'W' && transacao_no_escalonamento(escalonamento, op_w->identificador)) {
            short int leu_antes = 0;
            // Procura para trás por uma leitura do mesmo atributo pela mesma transação
            for (int j = 0; j < i; j++) {
                transaction_t* op_r = lista_transacoes[j];
                if (op_r->identificador == op_w->identificador &&
                    op_r->operacao == 'R' &&
                    op_r->atributo == op_w->atributo) {
                    leu_antes = 1;
                    break;
                }
            }
            if (!leu_antes) {
                return 1; // Encontrou uma escrita cega
            }
        }
    }
    return 0;
}

void troca(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// testa equivalencia por visão, a partir de um 'escalonamento', uma 'lista_transaçoes' de todas as operaçoes e o numero total 'n_ops' de operaçoes
void visao_equivalente(escalonamento_t* escalonamento, transaction_t** lista_transacoes, int n_ops) {
    // serializável por conflito == serializável por visão.
    if (strcmp(escalonamento->serializavel, "SS") == 0) {
        strcpy(escalonamento->equivalente, "SV");
        return;
    }

    // não é serializável por conflito e NÃO tem escrita cega == NÃO pode ser por visão.
    if (!tem_escrita_cega(escalonamento, lista_transacoes, n_ops)) {
        strcpy(escalonamento->equivalente, "NV");
        return;
    }

    // gera todas as permutações seriais e comparar as propriedades
    propriedades_t props_originais;
    analisar_propriedades(lista_transacoes, n_ops, &props_originais);

    short int encontrado = 0;
    // Chama a função recursiva que testará todas as permutações
    testar_permutacoes(escalonamento->identificadores, 0, escalonamento->tamanho - 1,escalonamento, lista_transacoes, n_ops, &props_originais, &encontrado);

    if (encontrado) {
        strcpy(escalonamento->equivalente, "SV");
    } else {
        strcpy(escalonamento->equivalente, "NV");
    }
}

// gera todas as permutações de IDs de transação e testa
void testar_permutacoes(int* ids, int inicio, int fim, escalonamento_t* escalonamento, transaction_t** lista_transacoes,int n_ops, propriedades_t* props_originais, short int *encontrado)
{
    if (*encontrado) 
      return;
    if (inicio == fim) {
        // salva as operações na ordem serial
        transaction_t** escalonamento_serial_ops = malloc(n_ops * sizeof(transaction_t*));
        int count = 0;

        // monta a lista de operações na ordem da permutação atual
        for (int i = 0; i <= fim; i++) {
            int id_atual = ids[i];
            for (int j = 0; j < n_ops; j++) {
                if (lista_transacoes[j]->identificador == id_atual) {
                    escalonamento_serial_ops[count++] = lista_transacoes[j];
                }
            }
        }

        propriedades_t props_serial;
        analisar_propriedades(escalonamento_serial_ops, count, &props_serial);

        if (comparar_propriedades(props_originais, &props_serial))
            *encontrado = 1;

        free(escalonamento_serial_ops);
    } 
    else {
        // gera as permutações dos elementos restantes
        for (int i = inicio; i <= fim; i++) {
            troca(&ids[inicio], &ids[i]);
            testar_permutacoes(ids, inicio + 1, fim, escalonamento, lista_transacoes, n_ops, props_originais, encontrado);
            troca(&ids[inicio], &ids[i]);
        }
    }
}

int main (){
  transaction_t **lista_transacoes = cria_lista_transacoes();
  // imprime_transacoes(lista_transacoes);
  
  escalonamento_t **lista_escalonamentos = cria_lista_escalonamentos(lista_transacoes);
  
  // imprime_escalonamentos(lista_escalonamentos, lista_transacoes, n_escalonamentos);
  
  int total_de_operacoes = n_transacoes + 1;
  for(int i = 0; i < n_escalonamentos; i++){
    escalonamento_t *escalonamento = lista_escalonamentos[i];
    teste_seriabilidade(escalonamento, lista_transacoes); 
    visao_equivalente(escalonamento, lista_transacoes, total_de_operacoes);
    printf("%d ", i+1);
    int j;
    for(j = 0; j < escalonamento->tamanho-1; j++){
      printf("%d,", escalonamento->identificadores[j]);
    }
    printf("%d %s %s\n", escalonamento->identificadores[j], escalonamento->serializavel, escalonamento->equivalente);
  }

  destroi_lista_transacoes(lista_transacoes);
  destroi_lista_escalonamentos(lista_escalonamentos);

  return 0;
}

void destroi_lista_transacoes(transaction_t **lista_transacoes){
  for(int i = 0; i < 100; i++){
    free(lista_transacoes[i]);
  }
  free(lista_transacoes);
}

void destroi_lista_escalonamentos(escalonamento_t **lista_escalonamentos){
  // Só libera os escalonamentos que foram realmente criados
  for(int i = 0; i < n_escalonamentos; i++){
    if(lista_escalonamentos[i]){
      if(lista_escalonamentos[i]->identificadores){
        free(lista_escalonamentos[i]->identificadores);
      }
      if(lista_escalonamentos[i]->equivalente){
        free(lista_escalonamentos[i]->equivalente);
      }
      if(lista_escalonamentos[i]->serializavel){
        free(lista_escalonamentos[i]->serializavel);
      }
      free(lista_escalonamentos[i]);
    }
  }
  free(lista_escalonamentos);
}
