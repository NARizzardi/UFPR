#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 16000

int main(int argc, char **argv, char **envp){
    
    FILE* arq;
    char cValue;
    int iValue;
    int control = 0;

    arq = fopen(argv[1], "r");
    if(!arq){
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char *frase = malloc(TAM * sizeof(int));
    fread(&iValue, sizeof(int), 1, arq);
    while(! feof(arq)){
        if(control == 0){
            fread(&cValue, sizeof(char), 1, arq);
            frase[iValue] = cValue;
            control++;
        } else {
            fread(&iValue, sizeof(int), 1, arq);
            control--;
        }
    }
    
    int index;
    int totalTam = strlen(frase);
    for(index = 0; index < totalTam; index++){
        putchar(frase[index]);
    }
    printf("\n");

    fclose(arq);
    free(frase);
    return 0;
}