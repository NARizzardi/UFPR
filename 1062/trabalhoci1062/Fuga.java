public class Fuga extends Item{
    public Fuga(Posicao posicao){
        this.setPosicao(posicao);
    }

    /*
    * Move um jogador para uma posição qualquer que ele escolher
    */
    public int realizaAcao(Tabuleiro tabuleiro,Posicao posicao,Jogador jogador){
        tabuleiro.resolveMovimento(jogador, posicao);
        return 1;
    }
        

}
