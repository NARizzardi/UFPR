public class FuncMensalista extends Funcionario{
    
    protected float salarioMensal;

    public FuncMensalista() {
    }
    
    public FuncMensalista(String nome, Data dataContratacao, float salarioMensal) {
        super(nome, dataContratacao);
        this.salarioMensal = salarioMensal;
    }

    public FuncMensalista(String nome, int matricula, Data dataContratacao, boolean ehEStrangeiro,
            float salarioMensal) {
        super(nome, matricula, dataContratacao, ehEStrangeiro);
        setSalarioMensal(salarioMensal);
    }

    public float getSalarioMensal() {
        return salarioMensal;
    }

    public void setSalarioMensal(float salarioMensal) {
        this.salarioMensal = salarioMensal;
    }

    public String toString(){
        // String funcMensalistaData = super.toString();
            //    funcMensalistaData = funcMensalistaData.concat("\nSalario mensal: R$");
            //    funcMensalistaData = funcMensalistaData.concat(String.format("%.2f", salarioMensal));
        
        return super.toString();

    }

    public float calculaSalario(){
        return super.calculaSalario() + salarioMensal;
    }

    public final float calculaBonificacao(){
        return salarioMensal * (float) ((Math.random() * 10) - 5);
    }
}
