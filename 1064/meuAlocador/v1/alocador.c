#include <stdio.h>
#include <unistd.h>

void *brk_original = 0, *brk_current = 0;

void setup_brk(){
    printf("Setando BRK\n");
    brk_original = sbrk(0);
    brk_current = brk_original;
}

void dismiss_brk(){
    printf("Liberando toda a heap\n");
    brk_current = brk_original;
    brk(brk_original);
}

void* memory_alloc(unsigned long int bytes){
    printf("Alocando um espaço de %ld bytes\n\n", bytes);
    brk_current += bytes;

    return sbrk(bytes);
}

int memory_free(void *pointer){
    printf("Espaço liberado\n");
    return 0;
}
