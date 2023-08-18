public class Serviço implements Loja{
    private int duracao;
    private String responsavel;
    private int localidade;
    
    public Serviço() {
    } 
    public Serviço(int duracao, String responsavel, int localidade) {
        this.duracao = duracao;
        this.responsavel = responsavel;
        this.localidade = localidade;
    }

    public int getDuracao() {
        return duracao;
    }
    public void setDuracao(int duracao) {
        this.duracao = duracao;
    }
    public String getResponsavel() {
        return responsavel;
    }
    public void setResponsavel(String responsavel) {
        this.responsavel = responsavel;
    }
    public int getLocalidade() {
        return localidade;
    }
    public void setLocalidade(int localidade) {
        this.localidade = localidade;
    }

    @Override
    public void vender() {
        System.out.println("Vendendo serviço...");
    }
    @Override
    public void acionarGarantia() {
        System.out.println("Acionando a garantia do serviço...");
    }

    
}
