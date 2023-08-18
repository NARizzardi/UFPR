import java.util.Scanner;

public class ex5 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        String frase = s.nextLine();
        frase = frase.replace('a', '@');
        System.out.println(frase);
        s.close();
    }
}
