import java.util.Random;

public class F1 extends FakeNews{

    public F1(Posicao posicao){
        this.setPosicao(posicao);
    }
    
    /*
    *   Movimento aleatorio uma casas vertical ou horizontal 
    */
    public Posicao movimentaFakeNews(){
        Random rand = Aleatorio.getAleatorio();
        Posicao p = this.getPosicao();

        switch (rand.nextInt(4)){
            case 0:
                return new Posicao(p.getPosX()+1, p.getPosY());
            case 1:
                return new Posicao(p.getPosX()-1, p.getPosY());
            case 2:
                return new Posicao(p.getPosX(), p.getPosY()+1);
            case 3:
                return new Posicao(p.getPosX(), p.getPosY()-1);
        }
        return null;
    }
}
