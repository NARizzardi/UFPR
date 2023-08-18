import java.util.ArrayList;

public class Principal {
    public static void main(String[] args) {
        ArrayList<Imovel> imoveis = new ArrayList<Imovel>(200);

        for(int i = 0; i < imoveis.size(); i++){
            double preco;
            do{
                preco = Math.random() * 1000000;
            }while(preco <= 100000);
            if(i%2 == 0){
                imoveis.add(ImovelNovo((int)preco));
            }else{
                imoveis[i] = new ImovelVelho((int) preco);
            }
        }

        for(int i = 0; i < imoveis.length; i++){
            System.out.printf("Valor do Imovel %d: R$%d,00\n",i+1 ,imoveis[i].calcularValorImovel());
        }

    }
}
