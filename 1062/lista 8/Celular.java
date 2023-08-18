public class Celular extends ProdEletronico{

    public Celular(String string, int i) {
        super(string, i);
    }

    @Override
    public void acionarGarantia() {
        System.out.println("Acionando garantia do celular");
    }

    @Override
    public void vender() {
        System.out.println("Vendendo celular");
    }
    
    @Override
    public void desligar() {
        System.out.println("desligando celular...");
    }

    @Override
    public void ligar() {
        System.out.println("ligando celular...");
    }

}
