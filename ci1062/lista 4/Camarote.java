public class Camarote extends Vip {
    private float adicionalCamarote;

    public Camarote(float valor, float valorAdicional, float adicionalCamarote) {
        super(valor, valorAdicional);
        this.adicionalCamarote = adicionalCamarote;
    }

    public float getAdicionalCamarote() {
        return adicionalCamarote;
    }

    public void setAdicionalCamarote(float adicionalCamarote) {
        this.adicionalCamarote = adicionalCamarote;
    }

    public float valorCamarote(){
        return valorVip() + adicionalCamarote;
    }

    public void imprimeValor(){
        System.out.printf("%.2f\n", valorCamarote());
    }
}
