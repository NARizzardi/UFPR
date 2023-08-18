public class Funcionario{
    
    protected String nome;
    protected int matricula;
    protected Data dataContratacao;
    protected boolean ehEStrangeiro;
    
    

    public Funcionario() {
    }

    public Funcionario(String nome, Data dataContratacao){
        this.setNome(nome);
        this.dataContratacao = new Data();
        this.setDataContratacao(dataContratacao);
    }

    public Funcionario(String nome, int matricula, Data dataContratacao, boolean ehEStrangeiro) {
        this.setNome(nome);
        this.setMatricula(matricula);
        this.dataContratacao = new Data();
        this.setDataContratacao(dataContratacao);
        this.setEhEStrangeiro(ehEStrangeiro);
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getMatricula() {
        return matricula;
    }

    public void setMatricula(int matricula) {
        this.matricula = matricula;
    }

    public Data getDataContratacao() {
        return dataContratacao;
    }

    public void setDataContratacao(Data dataContratacao) {
        this.dataContratacao.setDataContratacao(dataContratacao);
    }

    public boolean isEhEStrangeiro() {
        return ehEStrangeiro;
    }

    public void setEhEStrangeiro(boolean ehEStrangeiro) {
        this.ehEStrangeiro = ehEStrangeiro;
    }

    public String toString(){
        String funcData = "Nome: ".concat(nome);
               funcData = funcData.concat("\nMatricula: ");
               funcData = funcData.concat(String.format("%d", matricula));
               funcData = funcData.concat("\nData de contratação: ");
               funcData = funcData.concat(dataContratacao.toString());
               funcData = funcData.concat("\nFuncionario estrangeiro? ");
               if(ehEStrangeiro)
                   funcData = funcData.concat("Sim");
               else
                   funcData = funcData.concat("Não");
        return funcData;
    }

    public float calculaSalario(){
        return 0;
    }
}