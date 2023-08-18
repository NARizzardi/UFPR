import java.util.Scanner;

public class ex5 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int num, result = 0;
        num = s.nextInt();
        if(num >= 0 && num < 5){
            result = num;
        } else if(num >= 5 && num < 10){
            result = (2 * num) + 1;
        } else if (num >= 10){
            result = num - 3;
        }
        System.out.println(result);
        s.close();
    }
}
