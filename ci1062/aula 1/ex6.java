public class ex6 {
    public static void main(String[] args) {
        int num = 3;
        int soma = 0;
        for(int cont = 0; cont < 10; cont ++){
            soma += num;
            num += 3;
        }
        System.err.println(soma);
    }
}
