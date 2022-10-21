#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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