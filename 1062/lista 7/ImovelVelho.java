public class ImovelVelho extends Imovel{

    public ImovelVelho() {
        super();
    }

    public ImovelVelho(int preco) {
        super(preco);
    }

    public ImovelVelho(String nomeDaRua, int numeroDaRua, String bairro, String cidade, String estado, int preco) {
        super(nomeDaRua, numeroDaRua, bairro, cidade, estado, preco);
    }

    @Override
    public int calcularValorImovel() {
        return (this.getPreco()  / 10) * 9;
    }
    
}
