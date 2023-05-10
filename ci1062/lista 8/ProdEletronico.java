public abstract class ProdEletronico implements Loja{
    private String marca;
    private int peso;
    
    public ProdEletronico() {
    
    }
    public ProdEletronico(String marca, int peso) {
        this.marca = marca;
        this.peso = peso;
    }

    public String getMarca() {
        return marca;
    }
    public void setMarca(String marca) {
        this.marca = marca;
    }

    public int getPeso() {
        return peso;
    }
    public void setPeso(int peso) {
        this.peso = peso;
    }
    
    public void ligar(){}
    public void desligar(){}
}
