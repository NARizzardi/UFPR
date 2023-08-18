
public class Trabalho {
    
    public static void main(String[] args) {
        for(int i = 0; i < 8; i++){
            imprimeMapa(i % 8 == 0);
        }

    }
    public static void imprimeMapa(boolean flag){
        for(int i = 0; i < 9; i++)
            System.out.print("+----");
        System.out.println("+");
        for(int i = 0; i < 9; i++)
            System.out.print("|    ");
        System.out.println("|");
        if(flag){
            for(int i = 0; i < 9; i++)
                System.out.print("|    ");
            System.out.println("|");
        }
    }
}
