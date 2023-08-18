public class Main2 {
    public static void main(String[] args) {
        Data data1 = new Data(21, 10, 2000);
        Data data2 = new Data(6, 6, 2000);

        System.out.println(data1.toString());
        System.out.println(data2.toString());

        if(data1.anterior(data2.getDia(), data2.getMes(), data2.getAno())){
            System.out.println("Posterior");
        }
        if(data1.posterior(data2.getDia(), data2.getMes(), data2.getAno())){
            System.out.println("Anterior");
        }
        if(data1.equals(data2.getDia(), data2.getMes(), data2.getAno())){
            System.out.println("Iguais");
        }
    }
}
