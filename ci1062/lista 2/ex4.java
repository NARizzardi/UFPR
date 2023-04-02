import java.util.Scanner;

public class ex4 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        double[] vetor = new double[7];
        double menor = 0, maior = 0;
        for(int i = 0; i < vetor.length; i++){
            vetor[i] = s.nextDouble();
            if(i == 0){
                menor = maior = vetor[i];
            } else {
                if(vetor[i] < menor){
                    menor = vetor[i];
                }
                if(vetor[i] > maior){
                    maior = vetor[i];
                }
            }
        }

        System.out.println("O maior elemento do vetor é " + maior);
        System.out.println("O menor elemento do vetor é " + menor);
        s.close();
    }
}
