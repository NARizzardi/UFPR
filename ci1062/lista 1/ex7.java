import java.util.Scanner;

public class ex7 {
    public static void main(String[] args) {
        double[][] notas = new double[30][4];
        double[] melhores = new double[30];
        double melhor;
        double melhorAluno;
        Scanner s = new Scanner(System.in);
        for(int aluno = 0; aluno < 30; aluno++){
            for(int nota = 0; nota < 4; nota++){
                notas[aluno][nota] =  Math.random() * 100;;
                if(nota == 0){
                    melhores[aluno] = notas[aluno][nota];
                } else {
                    if(melhores[aluno] < notas[aluno][nota]){
                        melhores[aluno] = notas[aluno][nota];
                    }
                }
            }
        }
        melhor = melhores[0];
        melhorAluno = 1;
        for(int aluno = 0; aluno < 30; aluno++){
            if(melhores[aluno] > melhor){
                melhor = melhores[aluno];
                melhorAluno = aluno+1;
            }
            System.out.println("A melhor nota do aluno " + (aluno+1) + " foi " + String.format("%.2f", melhores[aluno]));
        }
        System.out.println("A melhor nota da turma foi do aluno " + melhorAluno + " com a nota " + String.format("%.2f", melhor));
        s.close();
    }
}
