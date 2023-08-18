public class ImovelNovo extends Imovel{

    public ImovelNovo() {
        super();
    }

    public ImovelNovo(int preco) {
        super(preco);
    }

    public ImovelNovo(String nomeDaRua, int numeroDaRua, String bairro, String cidade, String estado, int preco) {
        super(nomeDaRua, numeroDaRua, bairro, cidade, estado, preco);
    }

    @Override
    public int calcularValorImovel() {
        return (this.getPreco()  / 10) * 11;
    }
    
}
