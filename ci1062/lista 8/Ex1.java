import java.util.ArrayList;
import java.util.Iterator;

public class Ex1 {
    public static void main(String[] args) throws InterruptedException {
     ArrayList<Loja> loja = new ArrayList<Loja>();   
        Celular c1 = new Celular("soby", 100);
        loja.add(c1);
        Televisao t1 = new Televisao("gl", 1000);
        loja.add(t1);
        Serviço s = new Serviço(60, "eu", 0);
        loja.add(s);

        Iterator<Loja> i = loja.iterator();

        while(i.hasNext()){
            Loja l = i.next();
            if(l instanceof ProdEletronico){
                if(l instanceof Celular){
                    Celular c = (Celular) l;
                    c.vender();
                    c.ligar();
                    c.desligar();
                    c.acionarGarantia();

                }
                if(l instanceof Televisao){
                    Televisao c = (Televisao) l;
                    c.vender();
                    c.ligar();
                    c.desligar();
                    c.acionarGarantia();
                }
            } else {
                Serviço s1 = (Serviço) l;
                s1.vender();
                s1.acionarGarantia();
            }

            System.err.println();
            Thread.sleep(10000);
        }


    }



}
