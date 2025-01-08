public abstract class Entidade {
    protected Posicao posicao;

    public Posicao getPosicao() {
        return posicao;
    }

    public void setPosicao(Posicao posicao) {
        this.posicao = posicao;
    }

    public void mudaPosicao(Posicao posicao){
        this.posicao.setPosX(posicao.getPosX());
        this.posicao.setPosY(posicao.getPosY());
    }
}
