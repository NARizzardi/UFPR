public class Telefone {
    int ddi;
    int ddd;
    int numero;

    public void cadastrar(int ddi, int ddd, int numero){
        this.ddi = ddi;
        this.ddd = ddd;
        this.numero = numero;
    }

    public void exibirDados(){
        System.out.println("+" + ddi + " ("+ ddd + ") " + numero);
    }

}
