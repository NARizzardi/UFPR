import java.util.Random;

public class F3 extends FakeNews{
    public F3(Posicao posicao){
        this.setPosicao(posicao);
    }
    
    /*
    *   Movimento aleatorio duas casas na diagonal 
    */
    public Posicao movimentaFakeNews(){
        Random rand = Aleatorio.getAleatorio();
        Posicao p = this.getPosicao();
        switch (rand.nextInt(4)){
            case 0:
                return new Posicao(p.getPosX()+1, p.getPosY()+1);
            case 1:
                return new Posicao(p.getPosX()+1, p.getPosY()-1);
            case 2:
                return new Posicao(p.getPosX()-1, p.getPosY()+1);
            case 3:
                return new Posicao(p.getPosX()-1, p.getPosY()-1);
        }
        return null;
    }
}
