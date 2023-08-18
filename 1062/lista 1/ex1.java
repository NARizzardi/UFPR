import java.util.Scanner;

public class ex1 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int num = s.nextInt();

        if(num > 0){
            System.out.println("O numero e positivo");
        } else if (num == 0){
            System.out.println("O numero e nulo");
        } else {
            System.out.println("O numero e negativo");
        }
        s.close();
    }
}
