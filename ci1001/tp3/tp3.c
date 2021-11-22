#include <stdio.h>
#define MAX 100

/*le o vetor*/
void lerVetor(int tam, int *vetor){
    int i;
    for(i = 0; i<tam; i++){
        scanf("%d", &vetor[i]);
    }
    
}
/*define a subsequencia com base no vetor original*/
void definirSub(int *sub, int *vetor, int inicio, int fim){
    int i;
    for(i=inicio; i <= fim; i++){
        sub[i-inicio+1] = vetor[i];
        int var = i-inicio+1;
    }
}
/*compara a subsequencia com o vetor original*/
int comparar(int *vetor, int *sub, int inicioSub, int fimSub){
    int i, cont;
     cont = 1;
    for(i = inicioSub;i <= fimSub;i++){
        if(vetor[i] != sub[cont]){
            return 0;
        }
        cont++;
    }
    return 1;
}
/*passa por todas as subsequencias de tamanho X ate a metade do vetor*/
int possiveisSubs(int *vetor, int tamBase, int tamSub){
    int inicio, inicioSub, fim, fimSub, comparador;
    int sub[MAX];
    inicio = 0; fim = tamSub-1;
    while(fim <= ((tamBase/2)-1)){
        definirSub(sub, vetor, inicio, fim);
        inicioSub = fim + 1;
        fimSub = fim + tamSub;
        /*compara a subsequencia com outras subsequencias de mesmo tamanho dentro do vetor*/
        while(fimSub <= tamBase){
            comparador = comparar(vetor, sub, inicioSub, fimSub);
            if(comparador == 1) {
                return inicio;
            }
            inicioSub++;
            fimSub++;
        }
            inicio++;
            fim++;
    }
    return -1;
}

int main(){
    int tamBase, posicao, tamSub;    
    int vetor[MAX];
    scanf("%d", &tamBase);
    lerVetor(tamBase, vetor);
    tamSub = tamBase / 2;
    posicao = -1;
    while((tamSub > 1) && (posicao == -1)){
        posicao = possiveisSubs(vetor, tamBase, tamSub);
        tamSub--;
    }
    if(posicao == -1){
        printf("nenhuma");
    } else {
        printf("posicao: %d - tamanho: %d", posicao+1, tamSub+1);
    }
    return 0;
 }