public class Pessoa {
    private String nome;
    private String ocupacao;
    private Endereco enderecoResidencial;
    private Data dataNasc;

    
    public Pessoa() {}

    public Pessoa(String nome, String ocupacao) {
        this.nome = nome;
        this.ocupacao = ocupacao;
        this.enderecoResidencial = new Endereco();
        this.dataNasc = new Data();
    }

    public Pessoa(String nome, String ocupacao, String nomeDaRua, int numeroDaRua, String bairro, String cidade, String estado, int cep, int dia, int mes, int ano){
        this.nome = nome;
        this.ocupacao = ocupacao;
        this.enderecoResidencial = new Endereco(nomeDaRua, numeroDaRua, bairro, cidade, estado, cep);
        this.dataNasc = new Data(dia, mes, ano);
    }


    public String getNome() {
        return nome;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }
   
    public String getOcupacao() {
        return ocupacao;
    }
    public void setOcupacao(String ocupacao) {
        this.ocupacao = ocupacao;
    }
   
    public Endereco getEnderecoResidencial() {
        return enderecoResidencial;
    }
    public void setEnderecoResidencial(String nomeDaRua, int numeroDaRua, String bairro, String cidade, String estado, int cep) {
        this.enderecoResidencial.setNomeDaRua(nomeDaRua);
        this.enderecoResidencial.setNumeroDaRua(numeroDaRua);
        this.enderecoResidencial.setBairro(bairro);
        this.enderecoResidencial.setCidade(cidade);
        this.enderecoResidencial.setEstado(estado);
        this.enderecoResidencial.setCep(cep);
    }
   
    public Data getDataNasc() {
        return dataNasc;
    }
    public void setDataNasc(int dia, int mes, int ano) {
        this.dataNasc.setDia(dia);
        this.dataNasc.setMes(mes);
        this.dataNasc.setAno(ano);
    }


}
