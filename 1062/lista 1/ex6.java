import java.util.Scanner;

public class ex6 {
    public static void main(String[] args) {
        String nome, bairro, time;
        Scanner s = new Scanner(System.in);
        nome = s.nextLine();
        time = s.nextLine();
        bairro = s.nextLine();
        System.out.println("Seu nome é " + nome);
        System.out.println("Seu time do coração é o " + time);
        System.out.println(("Você mora no bairro " + bairro));
        s.close();
    }
}
