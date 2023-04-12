import java.util.Scanner;

public class ex1 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        String texto = s.nextLine();
        System.out.println(texto.length());
        s.close();
    }
}
