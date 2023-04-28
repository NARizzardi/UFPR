public class Principal {
    public static void main(String[] args) {
        Imovel imoveis[] = new Imovel[2];

        for(int i = 0; i < imoveis.length; i++){
            if(i%2 == 0){
                
                imoveis[i] = new ImovelNovo();
            }else{
                imoveis[i] = new ImovelVelho();
            }
        }

        for(int i = 0; i < imoveis.length; i++){
            System.out.printf("Valor do Imovel %d: R$%d,00\n", imoveis[i].calcularValorImovel());
        }

    }
}
