public abstract class Imovel {
    protected Endereco endereco;
    protected int preco;

    
    
    public Imovel() {
    }

    public Imovel(String nomeDaRua, int numeroDaRua, String bairro, String cidade, String estado, int preco) {
        this.endereco = new Endereco(nomeDaRua, numeroDaRua, bairro, cidade, estado);
        this.preco = preco;
    }


    public Endereco getEndereco() {
        return endereco;
    }


    public void setEndereco(String nomeDaRua, int numeroDaRua, String bairro, String cidade, String estado) {
        this.endereco.setNomeDaRua(nomeDaRua);
        this.endereco.setNumeroDaRua(numeroDaRua);
        this.endereco.setBairro(bairro);
        this.endereco.setCidade(cidade);
        this.endereco.setEstado(estado);
    }


    public int getPreco() {
        return preco;
    }


    public void setPreco(int preco) {
        this.preco = preco;
    }


    public abstract int calcularValorImovel();
}
