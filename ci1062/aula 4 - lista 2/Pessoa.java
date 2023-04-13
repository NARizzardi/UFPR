public class Pessoa {
    String nome;
    int idade;
    Data data;

    public void criaPessoa(String nome){
        this.nome = nome;   
        this.data = new Data();
    }

    public String retornarNome(){
        return nome;
    }

    public int retonarIdade(){
        return idade;
    }

    public void calcularIdade(int dia, int mes, int ano){
        
        if((mes > data.mes) || (mes == data.mes && dia >= data.dia)){
            this.idade = ano - data.ano; 
            return;
        }
        this.idade = ano - data.ano - 1;
    }
}
