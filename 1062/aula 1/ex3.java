import java.util.Scanner;

public class ex3 {
    public static void main(String[] args) {
        int mult;
        Scanner s = new Scanner(System.in);
        mult = s.nextInt();
        for(int cont = 1; cont <= 10; cont++){
            System.out.println(mult * cont);
        }
        s.close();
    }
}
