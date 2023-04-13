import java.util.Scanner;

public class ex1 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        int par[] = new int[10];
        int indexPar = 0;
        int impar[] = new int[10];
        int indexImpar = 0;
        int somaPares = 0;
        int num;

        for(int i = 0; i < 10; i++){
            num = s.nextInt();
            if(num % 2 == 0){
                par[indexPar] = num;
                indexPar++;
                somaPares += num;
            } else {
                impar[indexImpar] = num;
                indexImpar++;
            }
        }
        System.out.println("Os numeros pares sao: ");
        for(int i = 0; i < indexPar; i++){
            System.out.print(par[i] + " ");
        }

        System.out.println("\nA soma dos numeros pares e: " + somaPares + "\n Os numeros impares sao:");

        for(int i = 0; i < indexImpar; i++){
            System.out.print(impar[i] + " ");
        }
        System.out.println("\nTendo um total de " + indexImpar + " numeros impares");
    }
}
