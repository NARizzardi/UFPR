public class Endereco {

    private String nomeDaRua;
    private int numeroDaRua;
    private String bairro;
    private String cidade;
    private String estado;
    

    public Endereco() {}
    public Endereco(String nomeDaRua, int numeroDaRua, String bairro, String cidade, String estado) {
        this.nomeDaRua = nomeDaRua;
        this.numeroDaRua = numeroDaRua;
        this.bairro = bairro;
        this.cidade = cidade;
        this.estado = estado;
    }

    
    public String getNomeDaRua() {
        return nomeDaRua;
    }
    public void setNomeDaRua(String nomeDaRua) {
        this.nomeDaRua = nomeDaRua;
    }
    
    public int getNumeroDaRua() {
        return numeroDaRua;
    }
    public void setNumeroDaRua(int numeroDaRua) {
        this.numeroDaRua = numeroDaRua;
    }
   
    public String getBairro() {
        return bairro;
    }
    public void setBairro(String bairro) {
        this.bairro = bairro;
    }
   
    public String getCidade() {
        return cidade;
    }
    public void setCidade(String cidade) {
        this.cidade = cidade;
    }
   
    public String getEstado() {
        return estado;
    }
    public void setEstado(String estado) {
        this.estado = estado;
    }
}
