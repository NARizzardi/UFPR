public class Estudante {
    String nome;
    int notaFinal;

    public void criarEstudante(String nome, int notaFinal){
        this.nome = nome;
        this.notaFinal = notaFinal;
    }

    public void exibirEstudante(){
        System.out.println("Nome: " + nome);
        System.out.println("Nota final: " + notaFinal);
    }

    public String retornaNome(){
        return nome;
    }

    public int retornaNotaFinal(){
        return notaFinal;
    }
}
