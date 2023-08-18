import java.util.Scanner;

public class ex5 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.print("Entre com um numero ");
        int num = s.nextInt();
        int soma = 0;
        while (num != -1){
            soma += num;
            System.out.print("Entre com outro numero ");
            num = s.nextInt();
        }
        System.out.println("A soma total dos numeros é " + soma);
        s.close();
    }
}
