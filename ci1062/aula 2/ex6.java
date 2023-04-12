import java.util.Scanner;

public class ex6 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        String frase = s.nextLine();
        frase = frase.replaceAll("\\s", "");
        System.out.println(frase);
        s.close();
    }
}
