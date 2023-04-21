import java.util.Scanner;

public class Principal {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("Entre com o nome do remetente");
        String remetente = s.nextLine();
        System.out.println("Entre com o nome do destinatario");
        String destinatario = s.nextLine();
        CartaoWeb cartoes[] = new CartaoWeb[3];
        cartoes[0] = new CartaoAniversario(destinatario);
        cartoes[1] = new CartaoDiaDosNamorados(destinatario);
        cartoes[2] = new CartaoNatal(destinatario);

        for(int i = 0; i < cartoes.length; i++){
            System.out.printf("%s\n\n", cartoes[i].retornarMensagem(remetente));
        }
        s.close();
    }
}
