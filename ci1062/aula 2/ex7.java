import java.util.Scanner;

public class ex7 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        String nome = s.nextLine();
        String citacao = "";
        int i;
        for(i = nome.length() - 1; nome.charAt(i) != ' '; i--){
        }
        int pos = i;
        citacao = citacao.concat(nome.substring(i+1, nome.length()));
        citacao = citacao.concat(", ").concat(nome.substring(0, 1)).concat(". ");
        for(i = 0; i < pos; i++){
            if(nome.charAt(i) == ' '){
                citacao = citacao.concat(nome.substring(i+1, i+2)).concat(". ");
            }
        }
        System.out.println(citacao);
        s.close();
    }
}
