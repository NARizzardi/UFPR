public class CartaoNatal extends CartaoWeb{

        public CartaoNatal(String destinatario){
            super(destinatario);
        }

    @Override
    public String retornarMensagem(String remetente) {
        String message = "Oi, " + this.destinatario + ", como você está?!\nTenha um feliz natal!\nQue o espírito de natal encha seu coração de amor e paz!\nCom amor, " + remetente + ".";
        return message;
    }
    
}
