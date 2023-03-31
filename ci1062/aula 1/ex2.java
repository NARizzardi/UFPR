import java.util.Scanner;

public class ex2 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.print("Entre com um número ");
        int x = s.nextInt();
        System.out.print("Entre com outro número ");
        int y = s.nextInt();
        if(x > y){
            System.out.println(y + " " + x);
        } else {
            System.out.println(x + " " + y);
        }
        s.close();
    }
}
