
public class Denuncia extends Item{
    public Denuncia(Posicao posicao){
        this.setPosicao(posicao);
    }

    private boolean adjacente(Posicao jogador, Posicao fakenews){
    
        int jogadorX = jogador.getPosX();
        int jogadorY = jogador.getPosY();

        int fakenewsX = fakenews.getPosX();
        int fakenewsY = fakenews.getPosY();

        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){

                if(jogadorX + i == fakenewsX && jogadorY + j == fakenewsY) 
                    return true;
                
            }
        }
       
        return false;
    }

    /*
    *   Destroi todas as fakenews adjacentes ao jogador 
    */
    public int realizaAcao(Tabuleiro tabuleiro,Posicao posicao,Jogador jogador){

        for (int index = tabuleiro.getFakeNewsQtd()-1; index >= 0; index--) {
            if(adjacente(jogador.getPosicao(), tabuleiro.getOneFakeNews(index).posicao))
               tabuleiro.apagaEntidade(tabuleiro.getOneFakeNews(index).posicao);
        }

        return 0;
    }
        
    

}
