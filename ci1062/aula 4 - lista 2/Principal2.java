import java.util.Scanner;

public class Principal2 {
    public static void main(String[] args) {
        Estudante estudantes[] = new Estudante[5];
        Scanner s = new Scanner(System.in);
        int media = 0;
        int alunosEmFinal = 0;
        int reprovados = 0;
        for(int i = 0; i < estudantes.length; i++){
            estudantes[i] = new Estudante();
            estudantes[i].nome = s.next();
            estudantes[i].notaFinal = s.nextInt();
            media += estudantes[i].notaFinal;
            if(estudantes[i].notaFinal >= 40 && estudantes[i].notaFinal < 70){
                alunosEmFinal++;
            } else if(estudantes[i].notaFinal < 40){
                reprovados++;
            }
        }

        media /= estudantes.length;

        System.out.println("A média final da turma foi: " + media + "\n");
        System.out.println("Houveram " + alunosEmFinal + " alunos em final" + "\n");
        System.out.println("Houveram " + reprovados + " alunos reprovados direto" + "\n");
        System.out.println("Os seguintes alunos foram aprovados direto: ");
        for(int i = 0; i < estudantes.length; i++){
            if(estudantes[i].notaFinal >= 70){
                estudantes[i].exibirEstudante();
                System.out.println();
            }
        }

        s.close();
    }
}
