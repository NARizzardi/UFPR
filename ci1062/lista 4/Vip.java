public class Vip extends Ingresso {

    protected float adicionalVip;

    public Vip(float valor, float adicionalVip) {
        super(valor);
        this.adicionalVip = adicionalVip;
    }

    public float getadicionalVip() {
        return adicionalVip;
    }

    public void setadicionalVip(float adicionalVip) {
        this.adicionalVip = adicionalVip;
    }

    public float valorVip(){
        return valor + adicionalVip;
    }

    public void imprimeValor(){
        System.out.printf("%.2f\n", valorVip());
    }

}
