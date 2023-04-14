public class FuncHorista extends Funcionario{
    
    private float valorHora;
    private int horasTrabalhadas;

    public FuncHorista() {
    }

    
    public FuncHorista(String nome, Data dataContratacao, float valorHora, int horasTrabalhadas) {
        super(nome, dataContratacao);
        this.valorHora = valorHora;
        this.horasTrabalhadas = horasTrabalhadas;
    }


    public FuncHorista(String nome, int matricula, Data dataContratacao, boolean ehEStrangeiro, float valorHora,
            int horasTrabalhadas) {
        super(nome, matricula, dataContratacao, ehEStrangeiro);
        setValorHora(valorHora);
        setHorasTrabalhadas(horasTrabalhadas);
    }

    public float getValorHora() {
        return valorHora;
    }

    public void setValorHora(float valorHora) {
        this.valorHora = valorHora;
    }

    public int getHorasTrabalhadas() {
        return horasTrabalhadas;
    }

    public void setHorasTrabalhadas(int horasTrabalhadas) {
        this.horasTrabalhadas = horasTrabalhadas;
    }

    public String toString(){
        String funcHoristaData = super.toString();
               funcHoristaData = funcHoristaData.concat("\nHoras trabalhadas: ");
               funcHoristaData = funcHoristaData.concat(String.format("%d", horasTrabalhadas));
               funcHoristaData = funcHoristaData.concat("\nValor da hora: R$");
               funcHoristaData = funcHoristaData.concat(String.format("%.2f", valorHora));


        return funcHoristaData;
    }

    public float calculaSalario(){
        return super.calculaSalario() + (valorHora * horasTrabalhadas);
    }
}
