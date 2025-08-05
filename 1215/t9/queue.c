/**
 * Nome: Nicolas Andre Rizzardi
 *  GRR: 20206152
 */
#include "queue.h"
#include <stdio.h>

/*------------------------------------------------------------------------------
 * Conta o numero de elementos na fila
 * Retorno: numero de elementos na fila
 */
int queue_size (queue_t *queue){
  if(!queue){
    return 0;
  }

  int cont = 1;
  
  queue_t *head = queue;
  queue_t *iterador = queue->next;
  while((iterador != head)){
    iterador = iterador->next;
    cont++;
  }
  return cont;
}

/*------------------------------------------------------------------------------
 * Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
 * elemento é feita por uma função externa, definida pelo programa que
 * usa a biblioteca.
 */
void queue_print (char *name, queue_t *queue, void print_elem (void*) ){
  int q_size = queue_size(queue);
  if(q_size == 0){
    printf("%s: []\n", name);
    return;
  } else if(q_size == 1){
    print_elem(queue);
    return;
  }

  queue_t *end = queue->prev;
  queue_t *iterador = queue;
  printf("%s: [", name);
  

  while(iterador != end){
    print_elem(iterador);
    printf(" ");
    iterador = iterador->next;
  }
  print_elem(iterador);
  printf("]\n");
  return;
}


/*------------------------------------------------------------------------------
 * Insere um elemento no final da fila.
 * Condicoes a verificar, gerando msgs de erro:
 * - a fila deve existir
 * - o elemento deve existir
 * - o elemento nao deve estar em outra fila
 * Retorno: 0 se sucesso, <0 se ocorreu algum erro
 */
int queue_append (queue_t **queue, queue_t *elem){

  if(!queue){
    fprintf(stderr, "queue_append: Fila nao existe\n");
    return -1;
  }

  if(!elem){
    fprintf(stderr, "queue_append: Elemento nao existe\n");
    return -2;
  } 
  if (!!elem->next && !!elem->prev){
    fprintf(stderr, "queue_append: Elemento ja esta em outra fila\n");
    return -3;
  }
  
  int q_size = queue_size(*queue);
  if( q_size == 0 ){
    (*queue) = elem;
    elem->next = *queue;
    elem->prev = *queue;
    return 0;
  }
  queue_t* last = queue[0]->prev;
  last->next = elem;

  queue[0]->prev = elem;

  elem->next = queue[0];
  elem->prev = last;

    
    return 0;

}

/*------------------------------------------------------------------------------
 * Remove o elemento indicado da fila, sem o destruir.
 * Condicoes a verificar, gerando msgs de erro:
 * - a fila deve existir
 * - a fila nao deve estar vazia
 * - o elemento deve existir
 * - o elemento deve pertencer a fila indicada
 * Retorno: 0 se sucesso, <0 se ocorreu algum erro
 */
int queue_remove (queue_t **queue, queue_t *elem){
  
  if(!queue){
    fprintf(stderr, "queue_remove: Fila nao existe\n");
    return -1;
  }

  if(!elem){
    fprintf(stderr, "queue_remove: Elemento nao existe\n");
    return -2;
  } 
  
  queue_t *aux = *queue;
  aux = aux->next;
  
  while(aux != elem && aux != *queue){
    aux = aux->next;
  }
  if(aux != elem){
    fprintf(stderr, "queue_remove: Elemento nao pertence a fila\n");
    return -3;
  }
 
  int q_size = queue_size(*queue);
  if(q_size == 0){
    fprintf(stderr, "queue_remove: Fila vazia\n");
    return -4;
  }
  
  if (q_size == 1){
    elem->next = NULL;
    elem->prev = NULL;
    elem = NULL;
    *queue = NULL;
    return 0;
  }
  
  if(*queue == elem){
    *queue = elem->next;
  }

  elem->prev->next = elem->next;
  elem->next->prev = elem->prev;

  elem->next = NULL;
  elem->prev = NULL;
  

  return 0;
}
