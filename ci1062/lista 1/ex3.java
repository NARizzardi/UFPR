import java.util.Scanner;

public class ex3 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int num;
        num = s.nextInt();
        int soma = 0;
        while(num != -1){
            soma += num;
            num = s.nextInt();
        }
        System.out.println(soma);
        s.close();
    }
}
