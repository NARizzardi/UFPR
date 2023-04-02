import java.util.Scanner;

public class ex2 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int num = s.nextInt();

        if(num % 2 == 0){
            System.out.println("O numero e par");
        } else {
            System.out.println("O numero e impar");
        }
        s.close();
    }
}
