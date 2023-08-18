import java.util.Scanner;

public class ex1 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int[] numeros = new int[5];
        int soma= 0;
        for(int i = 0; i < 5; i++){
            numeros[i] = s.nextInt();
            soma += numeros[i];
        }
        System.out.println(soma);
        s.close();
    }
}
