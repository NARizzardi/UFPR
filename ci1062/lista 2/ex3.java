import java.util.Scanner;

public class ex3 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        String palavra = s.next();
        String vogais = "aeiou";
        int qtdVogais = 0;
        for(int i = 0; i < palavra.length(); i++){
            if(vogais.contains(palavra.substring(i, i+1))){
                qtdVogais++;
            }
        }
        System.out.println("A palavra possui " + qtdVogais + " vogais.");
        String consoante = s.next();
        palavra = palavra.replace('a', consoante.charAt(0));
        System.out.println("A nova palavra é:\n" + palavra);
        s.close();
    }
}
