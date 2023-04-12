public class Contador{
    int contagem;

    public Contador(int contagem) {
        this.contagem = contagem;
    }

    public Contador() {
        this.contagem = 0;
    }

    public int getContagem() {
        return contagem;
    }

    public void setContagem(int contagem) {
            this.contagem = contagem;
    }

    public void zerar(){
        setContagem(0);
    }

    public void incrementar(){
        contagem++;
    }

    public void decrementar(){
        if(contagem >= 0){
            contagem--;
        }
    }

}

/*
 * Catraca
 * Odômetro
 * Maquina de Exercicios
 * Iterador
 * Vetor
 */