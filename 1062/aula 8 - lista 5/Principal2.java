public class Principal2 {
    public static void main(String[] args) {
        Data dataAdmissao = new Data(1, 1, 2023);
        FuncMensalista funcionariosMensalistas[] = new FuncMensalista[100];
        FuncHorista funcionariosHoristas[] = new FuncHorista[100];
        float mediaSalariosMensalistas = 0;
        float mediaSalariosHoristas = 0;

        for(int i = 0; i < 100; i++){
            float salarioA;
            do{
                salarioA = (float) Math.random() * 10000;
            }while(salarioA < 1200);

            funcionariosMensalistas[i] = new FuncMensalista("Nicolas", 13, dataAdmissao, false, salarioA);
            mediaSalariosMensalistas += funcionariosMensalistas[i].calculaSalario();

            float valorHoraB;
            do{
                valorHoraB = (float) Math.random() * 200;
            }while(valorHoraB < 30);
            
            funcionariosHoristas[i] = new FuncHorista("Pedro", 7, dataAdmissao, true, valorHoraB, 40);
            mediaSalariosHoristas += funcionariosHoristas[i].calculaSalario();
        }

        mediaSalariosMensalistas /= 100;
        System.out.printf("A média salarial dos funcionarios mensalistas é R$%.2f\n", mediaSalariosMensalistas);
        mediaSalariosHoristas /= 100;
        System.out.printf("A média salarial dos funcionarios horistas é R$%.2f\n", mediaSalariosHoristas);
    }
}
