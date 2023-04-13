import java.util.Scanner;

public class ex2 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        
        int[][] matriz = new int[3][3];
        int[] vetor = new int[matriz.length];

        for(int i = 0; i < matriz.length; i++){
            for(int j = 0; j < matriz[i].length; j++){
                matriz[i][j] = s.nextInt();
            }
        }

        for(int i = 0; i< matriz.length; i++){
            vetor[i] = 0;
            for(int j = 0; j< matriz[i].length; j++){
                vetor[i]+= matriz[j][i];
            }
            System.out.print(vetor[i] + " ");
        }



        s.close();
    }
}
