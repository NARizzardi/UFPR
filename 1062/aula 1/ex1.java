import java.util.Scanner;

public class ex1 {

	public static void main(String[] args) {
		Scanner s = new Scanner (System.in);
		System.out.print("Entre com um numero: ");
		int var = s.nextInt();
		System.out.println("Voce digitou o numero " + var);
		s.close();

	}

}
