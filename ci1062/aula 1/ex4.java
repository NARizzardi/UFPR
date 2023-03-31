import java.util.Scanner;

public class ex4 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.print("Entre com um numero ");
        int num = s.nextInt();
        if(num % 2 == 0){
            System.out.println(num + " é par");
        } else {
            System.out.println(num + " é ímpar");
        }
        s.close();
    }
}
