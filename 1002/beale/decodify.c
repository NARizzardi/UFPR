#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void cypher(){
    printf("decodificar com livro cifra\n");
}

void codeFile(){
    printf("decodificar com arquivo de codigos\n");
}

int decodify(int basicStart){
    if(basicStart)
        cypher();
    else 
        codeFile();

    return 1;
}