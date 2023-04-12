public class Principal1 {
    public static void main(String[] args) {
        Pessoa pessoas[] = new Pessoa[2];
        for(int i = 0; i < pessoas.length; i++){
            pessoas[i] = new Pessoa();
        }
        

        pessoas[0].criaPessoa("Grace Hopper");
        pessoas[0].data.ajustarData(9, 12, 1906);
        pessoas[0].calcularIdade(2, 4, 2023);
        System.out.print(pessoas[0].retornarNome() + " nasceu em ");
        pessoas[0].data.imprimirData();
        System.out.println(" e hoje teria " + pessoas[0].retonarIdade() + " anos de idade.");

        pessoas[1].criaPessoa("Ada Lovelace");
        pessoas[1].data.ajustarData(10, 12, 1815);
        pessoas[1].calcularIdade(2, 4, 2023);
        System.out.print(pessoas[1].retornarNome() + " nasceu em ");
        pessoas[1].data.imprimirData();
        System.out.println(" e hoje teria " + pessoas[1].retonarIdade() + " anos de idade.");
    }
}
