import java.util.Scanner;

public class Principal1 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        LampadaFluorescente lampadaFluorescente = new LampadaFluorescente(20);
        LampadaLed lampadaLed = new LampadaLed();
        int menu;
        do{
            System.out.println("Para alterar a lâmpada fluorescente, digite 1");
            System.out.println("Para alterar a lâmpada de led, digite 2");
            System.out.println("Para encerrar, digite 0");
            System.out.print("Entre com as sua opção: ");
            menu = s.nextInt();
            System.out.println();
            if(menu == 1){
                lampadaFluorescente.alterarEstado();
                System.out.println("A lâmpada fluorescente está " + lampadaFluorescente.isEstado() + "\n");
            } else if(menu == 2){
                lampadaLed.alterarEstado();
                System.out.println("A lâmpada de led está " + lampadaLed.isEstado() + "\n");
            }
        } while(menu != 0);
        System.out.println("Sayonara!");
        s.close();
    }
}
