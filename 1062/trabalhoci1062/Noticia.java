import java.util.*;

public class Noticia extends Item{
    public Noticia(Posicao posicao){
        this.setPosicao(posicao);
    }

    /*
    *   Deleta uma fakenews qualquer 
    */
    public int realizaAcao(Tabuleiro tabuleiro,Posicao posicao,Jogador jogador){
      
        Random rand = Aleatorio.getAleatorio();

        int fakeId = rand.nextInt(tabuleiro.getFakeNewsQtd());
        tabuleiro.apagaEntidade(tabuleiro.getOneFakeNews(fakeId).posicao);
        return 0;

    }
}
