#include <stdio.h>
#include "alocador.h"

int main(){

    printf("Iniciando alocador de memoria... \n\n");
    setup_brk();
    dismiss_brk();
    void* pointer = memory_alloc(100);
    memory_free(pointer);

    return 0;
}

