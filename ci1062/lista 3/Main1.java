public class Main1 {
    public static void main(String[] args) {
        Time hora1 = new Time(12, 00);
        Time hora2 = new Time(12, 30);
        

        System.out.println(hora1.toString());
        System.out.println(hora2.toString());
        if(hora1.anterior(hora2.getH(), hora2.getM()))
            System.out.println("Posterior");
        else if(hora1.posterior(hora2.getH(), hora2.getM()))
            System.out.println("Anterior");
        else if(hora1.equals(hora2.getH(), hora2.getM()))
            System.out.println("Iguais");

    }
}
