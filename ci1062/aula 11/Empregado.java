public class Empregado implements Comparable<Empregado>{
    private String nome;
    private float salario;


    public Empregado(String nome, float salario) {
        this.nome = nome;
        this.salario = salario;
    }


    public String getNome() {
        return nome;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }
    public float getSalario() {
        return salario;
    }
    public void setSalario(float salario) {
        this.salario = salario;
    }


    @Override
    public int compareTo(Empregado e) {
        if(this.salario < e.salario){
            return -1;
        }else if(this.salario > e.salario){
            return 1;
        }
        
        if(this.nome.compareTo(e.nome) == -1){
            return -1;
        } else if(this.nome.compareTo(e.nome) == 1){
            return 1;
        }
        return 0;
    }
}
