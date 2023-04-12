import java.util.Scanner;

public class ex7 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        String frase1, frase2;

        frase1 = s.nextLine();
        frase2 = s.nextLine();

        frase1 = frase1.replace('a', '*');
        frase2 = frase2.replace('a', '*');
        
        for(int i = frase2.length() - 1; i >= 0; i--){
            System.out.print(frase2.charAt(i));   
        }
        System.out.println();
        for(int i = frase1.length() - 1; i >= 0; i--){
            System.out.print(frase1.charAt(i));   
        }
        System.out.println();

        s.close();
    }
}
