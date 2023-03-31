import java.util.Scanner;

public class ex3 {
    public static void main(String[] args) {
        String a, b;
        Scanner s = new Scanner(System.in);
        a = s.nextLine();
        b = s.nextLine();
        a = a.concat(b);
            System.out.println(a);
        
        s.close();
    }

}
