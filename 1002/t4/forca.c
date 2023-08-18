#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINESIZE 1024

void insereTentativa(char tentativa, char *palavra, char *palavraJogador, int tam){
    int i;
    printf("Voce tentou a letra %c\n", tentativa);
    for(i = 0; i < tam; i++){
        if(tentativa == palavra[i])
            palavraJogador[i] = tentativa;
    }

}

void imprimeJogo(char *palavraJogador, int tam){
    int i;
    printf("(");
    for(i = 0; i < tam; i++){
        printf("%c", palavraJogador[i]);
    }
    printf(")\n\n");

}

int jogoCompleto(char *palavraJogador, int tam){
    int i;
    for(i = 0; i < tam; i++){
        if(palavraJogador[i] == '_')
            return 0;
    }
    return 1;
}

int validaTentativa(char tentativa){
    if(tentativa >= 97 && tentativa <= 122)
        return 1;
    if(tentativa != '\n')
        printf("%c nao eh um caracter valido, tente apenas letras minusculas e sem acentos\n", tentativa);
    
    return 0;
}

int main(int argc, char **argv){
    int nTentativas = 1;
    int linhas = 1;
    int index;    int sorteada;    int linhaAtual;    int tam;
    FILE *arq;
    char cValue;
    

    arq = fopen(argv[1], "r");
    if(!arq){
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    /*contar quantas linhas tem o codigo*/
    fread(&cValue, sizeof(char), 1, arq);
    while(!feof(arq)){
    
        if(cValue == '\n'){
            linhas++;
        }
        fread(&cValue, sizeof(char), 1, arq);
        
    }

    /*sortear qual vai ser a palavra*/
    srand(clock());
    sorteada = (random() % linhas);
    rewind(arq);
    linhaAtual = 0;
    
    tam = -1;
    /*determinar o tamanho da palavra*/
    fread(&cValue, sizeof(char), 1, arq);
    while(!feof(arq)){
        if(cValue == '\n'){
            linhaAtual++;
        }
        if(linhaAtual == sorteada){
            tam++;
        }
        fread(&cValue, sizeof(char), 1, arq);
        
    }
    rewind(arq);
    linhaAtual = 0;

    index = 0;
    char *palavra= malloc(tam * sizeof(char));
    char *palavraJogador = malloc(tam * sizeof(char));
    /*alocar a memoria dinamicamente e gravar a palavra*/
    fread(&cValue, sizeof(char), 1, arq);
    while(!feof(arq)){
        if(cValue == '\n'){
            linhaAtual++;
        }else {
            if(linhaAtual == sorteada){
            palavra[index] = cValue;
            palavraJogador[index] = '_';
            index++;
            }
        }
        fread(&cValue, sizeof(char), 1, arq);
        
    }
    printf("%d letras:\n", tam);
    imprimeJogo(palavraJogador, tam);
    while(1){
        char tentativa;
        scanf("%c", &tentativa);
        if(validaTentativa(tentativa)){
            
            insereTentativa(tentativa, palavra, palavraJogador, tam);
            imprimeJogo(palavraJogador, tam);
            if(jogoCompleto(palavraJogador, tam)){
                break;
            }
            nTentativas++;
        }
    }
    
    printf("Numero de tentativas: %d\n", nTentativas);
    
    free(palavra);
    free(palavraJogador);
    fclose(arq);
    return 0;
}