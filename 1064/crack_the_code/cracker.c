#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 85 //DEFINA O TAMANHO DO BUFFER AQUI

void execute() {
  system("sudo echo 0 > /proc/sys/kernel/randomize_va_space");
  system("./ctc");
  system("sudo echo 2 > /proc/sys/kernel/randomize_va_space");
}

void debug() {
  system("sudo echo 0 > /proc/sys/kernel/randomize_va_space");
  system("gdb ./ctc");
  system("sudo echo 2 > /proc/sys/kernel/randomize_va_space");
}

void crack() {
  FILE *f = fopen("./teste.in", "w+");
  char password_buff[BUFF_SIZE] = "SB0123456789ABC\nSB0123456789ABCSB0123456789ABCSB0123456789ABC\nA BANDEIRA E MINHA!\n";
  
  //IMPLEMENTE A ENTRADA PARA ALCANÇAR OS OBJETIVOS DO TRABALHO AQUI (USAR A ENTRADA PADRÃO)
  fwrite(password_buff, 1, BUFF_SIZE, f);
fclose(f);

  system("sudo echo 0 > /proc/sys/kernel/randomize_va_space");
  system("./ctc < teste.in");
  system("sudo echo 2 > /proc/sys/kernel/randomize_va_space");
}

int main(int argc, char **argv) {
  
  if (argc == 2){ 	
    if (!strcmp(argv[1], "1")){
      execute(); 
      return 0;
    } 
    if (!strcmp(argv[1], "2")){
      debug();
      return 0;
    }
    if (!strcmp(argv[1], "3")){
      crack();
      return 0;
    }
  }
  
  printf("=========== HELP ===========\n");
  printf("EXECUTE AS SUPER USER!!\n");
  printf("./cracker [1|2|3]\n");
  printf("1 -> Execute\n");
  printf("2 -> Debug\n");
  printf("3 -> Crack\n");
  printf("============================\n");
  return 1;
  
}
