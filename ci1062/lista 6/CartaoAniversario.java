public class CartaoAniversario extends CartaoWeb{
    public CartaoAniversario(String destinatario){
        super(destinatario);
    }

    @Override
    public String retornarMensagem(String remetente) {
        String message = "Oi, " + this.destinatario + ", como você está?!\nFeliz aniversário!\nVocê merece muito amor,muita alegria e paz!\nQue esse novo ano venha apenas com coisas boas!\nCom amor, " + remetente + ".";;
        return message;
    }
}
