public class Funcionarios {
    public static void main(String[] args) {
        Funcionario[] funcionarios = new Funcionario[2];
        funcionarios[0] = new Funcionario();
        funcionarios[1] = new Funcionario();

        funcionarios[0].cadastrar("nicolas", 2021, 1200.00);
        funcionarios[0].exibirDados();

        System.out.println();

        funcionarios[1].cadastrar("Marcela", 2023, 1990.00);
        funcionarios[1].exibirDados();
        
    }
}
