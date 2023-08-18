public class Principal2 {
    public static void main(String[] args) {
        float valorBase = 100;
        float adicionalVip = 75;
        float adicionalCamarote = 50;
        
            
        Vip ingressosVip[] = new Vip[25];
        Camarote ingressosCamarote[] = new Camarote[25];
        Normal ingressosNormal[] = new Normal[25];
        for(int i = 0; i < ingressosNormal.length; i++){
            ingressosVip[i] = new Vip(valorBase, adicionalVip);
            ingressosNormal[i] = new Normal(valorBase);
            ingressosCamarote[i] = new Camarote(valorBase, adicionalVip, adicionalCamarote);    
        }

        for(int i = 0; i < ingressosNormal.length; i++){
            System.out.printf("Valor do ingresso VIP: ");
            ingressosVip[i].imprimeValor();
            System.out.printf("Valor do ingresso normal: ");
            ingressosNormal[i].imprimeValor();
            System.out.printf("Valor do ingresso camarote: ");
            ingressosCamarote[i].imprimeValor();
            System.out.println();
        }

    }
}
