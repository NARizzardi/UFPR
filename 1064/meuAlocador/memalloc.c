#include <stdio.h>
#include <unistd.h>

void *original_brk = 0, *current_brk = 0;

void setup_brk(){
    original_brk = sbrk(0);
    current_brk = original_brk;
}


void dismiss_brk(){
    current_brk = original_brk;
    brk(original_brk);
}


void* memory_alloc(unsigned long int bytes){

}


int memory_free(void *pointer){
    return 0;
}

