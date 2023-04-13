import java.util.Scanner;

public class ex6 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int[][] matriz = new int[4][4];
        int lin = 0, col = 0;
        boolean existe = false;
        for(int i = 0; i < matriz.length; i++){
            for(int j = 0; j < matriz[i].length; j++){
                matriz[i][j] = s.nextInt();
            }
        }

        int busca = s.nextInt();

        for(int i = 0; i < matriz.length; i++){
            for(int j = 0; j < matriz[i].length; j++){
                if(busca == matriz[i][j]){
                    lin = i+1;
                    col = j+1;
                    existe = true;
                    break;
                }
            }
        }
        if(existe){
            System.out.println("O numero " + busca + " esta na linha " + lin + " coluna " + col);
        } else {
            System.out.println("Não encontrado");
        }
        s.close();
    }
}
