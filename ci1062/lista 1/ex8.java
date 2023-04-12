import java.util.Scanner;

public class ex8 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int peso = 1, altura = 1;
        double imc;
        int pessoas = -1;
        while (true){
            double alt = (double) altura / 100;
            imc = peso / (alt * alt);
            if(imc > 25){
                pessoas++;
            }
            System.out.println("Peso");
            peso = s.nextInt();
            if(peso == -1){
                break;
            }
            System.out.println("Altura");
            altura = s.nextInt();
            if(altura == -1){
                break;
            }
        }
        System.out.println("Tem " + pessoas + " pessoas acima do peso");
        s.close();
    }
}
