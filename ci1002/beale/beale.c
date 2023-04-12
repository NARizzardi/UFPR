#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codify.h"
#include "decodify.h"
#include "keyfile.h"
#include "bealeFunctions.h"

int main(int argc, char const *argv[])
{
int basicStart = checkArgs(argc, argv);
    if(basicStart < 0){
        printf("Nao foi possivel executar o programa, leia o manual para prosseguir.\n");
        exit(0);

    } else {
        if(basicStart == 2){
            FILE* livroCifra = openFile(argv[3]);
            if(!livroCifra)
                return 0;
            codify();
        } else if(basicStart == 0 || basicStart == 1){
            decodify(basicStart);
        }
    }

    return 0;
}


