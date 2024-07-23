#include <stdio.h>
#include <unistd.h>

void *topo_inicial_heap = 0, *topo_heap = 0;

void setup_brk(){
    topo_inicial_heap = sbrk(0);
    topo_heap = topo_inicial_heap;
}


void dismiss_brk(){
    topo_heap = topo_inicial_heap;
    brk(topo_inicial_heap);
}


void* memory_alloc(unsigned long int bytes){
    topo_heap += bytes;
    return brk(bytes);
}


int memory_free(void *pointer){
    return 0;
}

