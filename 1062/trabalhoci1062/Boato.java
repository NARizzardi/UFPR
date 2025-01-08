public class Boato extends Item{
    public Boato(Posicao posicao){
        this.setPosicao(posicao);
    }
    /*
    *   Força o jogador a fazwer um movimento aleatorio no proximo turno 
    */
    public int realizaAcao(Tabuleiro tabuleiro,Posicao posicao,Jogador jogador){
        jogador.setBoatoFlag(true);
        return 1;
    }
}
