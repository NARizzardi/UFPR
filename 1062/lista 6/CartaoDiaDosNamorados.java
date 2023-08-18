public class CartaoDiaDosNamorados extends CartaoWeb {
    public CartaoDiaDosNamorados(String destinatario){
        super(destinatario);
    }

    @Override
    public String retornarMensagem(String remetente) {
        String mensagem = "Oi, " + this.destinatario + ", eu te amo!\nTenha um feliz dia dos namorados!\nE que esse cartão tenha sido o único que você ganhou hoje\nCom amor, " + remetente + ".";

        return mensagem;
    }
    
}
