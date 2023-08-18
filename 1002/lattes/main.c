#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib_lattes.h"

	/*
	 * 1) apresentar a produção sumarizada do grupo por ordem de periódicos discriminando o estrato
	 * 2) apresentar a produçãoi sumarizada do grupo por ordem de conferências
	 * 3) apresentar a produção dos pesquisadores do grupo por ordem de autoria, em periódicos e conferências
	 * 4) apresentar a produção sumarizada do grupo por ano, em periódicos e conferências
	 * 5) listar aqueles periodicos e eventos classificados no nivel c
	 * 6) listar aqueles periodicos e eventos não classificados
	 * ./lattes -d <diretorio com os CVs> -c <arquivo com a lista Qualis Conf> -p <arquivo com a lista Qualis Periódicos>
	*/

int main(){
	FILE *file_pointer;
	char ch;
	int index = 0;
	file_pointer = fopen("curriculo.xml", "r");

	while((ch = getc(file_pointer))!= EOF){
  		printf("%c",ch);
		if(ch == '>')
			printf("\n");
		index++;
	}
	return 0;
}