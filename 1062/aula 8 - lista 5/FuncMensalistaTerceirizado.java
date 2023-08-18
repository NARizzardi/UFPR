public class FuncMensalistaTerceirizado extends FuncMensalista{
    private String nomeEmpresaTerceirizada;

    

    public FuncMensalistaTerceirizado(String nomeEmpresaTerceirizada) {
        this.nomeEmpresaTerceirizada = nomeEmpresaTerceirizada;
    }

    public FuncMensalistaTerceirizado(String nome, Data dataContratacao, float salarioMensal,
            String nomeEmpresaTerceirizada) {
        super(nome, dataContratacao, salarioMensal);
        this.nomeEmpresaTerceirizada = nomeEmpresaTerceirizada;
    }

    public FuncMensalistaTerceirizado(String nome, int matricula, Data dataContratacao, boolean ehEStrangeiro,
            float salarioMensal, String nomeEmpresaTerceirizada) {
        super(nome, matricula, dataContratacao, ehEStrangeiro, salarioMensal);
        this.nomeEmpresaTerceirizada = nomeEmpresaTerceirizada;
    }

    public String getNomeEmpresaTerceirizada() {
        return nomeEmpresaTerceirizada;
    }

    public void setNomeEmpresaTerceirizada(String nomeEmpresaTerceirizada) {
        this.nomeEmpresaTerceirizada = nomeEmpresaTerceirizada;
    }


}
