#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bookArg "-b"
#define keyArg "-c"
#define decodArg "-d"
#define codArg "-e"
#define inputArg "-i"
#define messageArg "-m"
#define outputArg "-o"

FILE* openFile(char const *livro){
    FILE *livroCifra = fopen(livro, "r");

    if(!openFile(livro)){
        perror("Falha ao abrir o arquivo do livro cifra");
        fclose(livroCifra);
        exit(0);
    }
    return livroCifra;
}


int checkArgs(int argc, char const *argv[]){


    if(argc != 8 && argc != 10){
        //quantidade de argumentos invalida
        return -1;
    } else {
        int flag_b = 0, flag_c = 0, flag_d = 0, flag_e = 0, flag_i = 0, flag_m = 0, flag_o = 0;
        while ((option = getopt (argc, argv, "bcdeimo:")) != -1)
            switch (option)
            {
            case 'b':      // option -b was set
                flag_b = 1;
                break;

            case 'c':      // option -c was set with value
                flag_c = 1;
                break;
            case 'd':      // option -c was set with value
                flag_d = 1;
                break;
            case 'e':      // option -c was set with value
                flag_e = 1;
                break;
            case 'i':      // option -c was set with value
                flag_i = 1;
                break;
            case 'm':      // option -c was set with value
                flag_m = 1;
                break;
            case 'o':      // option -c was set with value
                flag_o = 1;
                break;
            default:
                fprintf (stderr, "Usage: %s -b -c -d -e -i- m -o value\n", argv[0]);
                exit (1) ;
            }
            
            return 0;
            }

            



            // if(strcmp(argv[1], codArg) == 0){
            //     if((strcmp(argv[2], bookArg) == 0) && (strcmp(argv[4], messageArg) == 0) && (strcmp(argv[6], outputArg) == 0) && (strcmp(argv[8], keyArg) == 0)){
            //         return 2; //codificar
            //     } else {
            //         return -1; //codificar nao possui os argumentos invalidos
            //     }
            // } else if (strcmp(argv[1], decodArg) == 0){
                
            //     if((strcmp(argv[2], inputArg) == 0) && (strcmp(argv[4], keyArg) == 0) && (strcmp(argv[6], outputArg) == 0)){
            //         return 0; //decodificar com arquivo de chaves
            //     } else if ((strcmp(argv[2], inputArg) == 0) && (strcmp(argv[4], bookArg) == 0) && (strcmp(argv[6], outputArg) == 0)){
            //         return 1; //decodificar com livro cifra
            //     } else {
            //         return -1; //decodificar nao possui os argumentos invalidos
            //     }
            // } else {
            // return -1; //argumento base invalido
            // }
            
        
        }
    
    return 1;
}


