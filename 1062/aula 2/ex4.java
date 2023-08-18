import java.util.Scanner;

public class ex4 {
    public static void main(String[] args) {
        Scanner s =new Scanner(System.in);
        String frase = s.nextLine();
        String esarf = "";
        for(int i = frase.length() - 1; i >= 0; i--){
            String caracter = frase.substring(i, i+1);
            esarf = esarf.concat(caracter);
        }
        System.out.println(esarf);
        s.close();
    }
}
