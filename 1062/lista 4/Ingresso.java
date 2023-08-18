public class Ingresso {
    protected float valor;

    public Ingresso() {
    }

    public Ingresso(float valor) {
        if(valor >= 0)
            this.valor = valor;
    }



    public float getValor() {
        return valor;
    }

    public void setValor(float valor) {
        if(valor >= 0)
            this.valor = valor;
    }

    public void imprimeValor(){
        System.out.printf("%.2f\n", valor);
    }

    
}
