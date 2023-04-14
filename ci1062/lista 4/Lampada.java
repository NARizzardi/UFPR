public class Lampada {
    protected boolean estado;

    public Lampada() {
        estado = false;
    }

    public String isEstado() {
        if(estado)
            return "ligada";
        return "desligada";
    }

    public void setEstado(boolean estado) {
        this.estado = estado;
    }

    public void alterarEstado(){
        estado = !estado;
    }
}
