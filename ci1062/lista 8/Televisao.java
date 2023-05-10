public class Televisao extends ProdEletronico {

    public Televisao(String marca, int peso){
        super(marca, peso);
    }

    @Override
    public void acionarGarantia() {
        System.out.println("Acionando garantia da televisao");
    }

    @Override
    public void vender() {
        System.out.println("Vendendo televisao");
    }

    @Override
    public void desligar() {
        System.out.println("desligando tv...");
    }

    @Override
    public void ligar() {
        System.out.println("ligando tv...");
    }

    
    
}
