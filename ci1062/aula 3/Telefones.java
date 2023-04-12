import java.util.Scanner;

public class Telefones {
    public static void main(String[] args) {
        Telefone[] numeros = new Telefone[5];
        Scanner s = new Scanner(System.in);
        for(int i = 0; i < 5; i++){
            numeros[i] = new Telefone();
            int ddi = s.nextInt();
            int ddd = s.nextInt();
            int numero = s.nextInt();
            numeros[i].cadastrar(ddi, ddd, numero);
        }

        for(int i = 0; i < 5; i++){
            numeros[i].exibirDados();
            System.out.println();
        }

        s.close();
    }
}
