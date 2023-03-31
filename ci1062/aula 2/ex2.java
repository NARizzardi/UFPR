import java.util.Scanner;

public class ex2 {
    public static void main(String[] args) {
        String a, b;
        Scanner s = new Scanner(System.in);
        a = s.nextLine();
        b = s.nextLine();
        if( a.equals(b)){
            System.out.println("Iguais");
        } else {
            System.err.println("Diferentes");
        }
        s.close();
    }
}
