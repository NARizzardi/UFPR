import java.util.*;

public class Principal {
    public static void main(String[] args) {
        Empregado a = new Empregado("Nico", 10000);
        Empregado b = new Empregado("Marcela", 10000);
        Empregado c = new Empregado("PEDRO", 6900);

        Collection<Empregado> emp = new TreeSet<Empregado>();
        emp.add(a);
        emp.add(b);
        emp.add(c);

        for(Empregado e: emp){
            System.out.println(e.getNome() + " - R$" + e.getSalario());
        }
    }
}
