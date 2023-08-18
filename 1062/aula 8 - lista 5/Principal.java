public class Principal {
    public static void main(String[] args) {
        Data dataAdmissao = new Data(1, 1, 2023);
        float salarioA;
        do{
            salarioA = (float) Math.random() * 10000;
        }while(salarioA < 1200);

        float valorHoraB;
        do{
            valorHoraB = (float) Math.random() * 200;
        }while(valorHoraB < 30);
        FuncMensalista funcA = new FuncMensalista("Nicolas", 13, dataAdmissao, false, salarioA);
        FuncHorista funcB = new FuncHorista("Pedro", 7, dataAdmissao, true, valorHoraB, 40);

        System.out.println(funcA.toString());
        float salarioFinalA = funcA.calculaSalario();
        System.out.printf("Salario mensal: R$%.2f\n", salarioFinalA);
        System.out.println();
        System.out.println(funcB.toString());
        float salarioFinalB = funcB.calculaSalario();
        System.out.printf("Salario mensal: R$%.2f\n", salarioFinalB);
    }
}
