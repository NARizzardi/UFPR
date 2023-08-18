public class Data {
    
    private int dia;
    private int mes;
    private int ano;

    public Data(){}

    public Data(int dia, int mes, int ano) {
        
        if(dataValida(dia, mes)){
            this.dia = dia;
            this.mes = mes;
            this.ano = ano;
        }
        else System.err.println("Data invalida");
    }

    public int getDia() {
        return dia;
    }
    public void setDia(int dia) {
        this.dia = dia;
    }

    public int getMes() {
        return mes;
    }
    public void setMes(int mes) {
        this.mes = mes;
    }

    public int getAno() {
        return ano;
    }
    public void setAno(int ano) {
        this.ano = ano;
    }

    public boolean anterior(int dia, int mes, int ano){
        if(this.ano > ano || (this.ano == ano && ((this.mes == mes && this.dia > dia) || (this.mes > mes)) ))
            return true;
        return false;
    }

    public boolean posterior(int dia, int mes, int ano){
        if(ano > this.ano || (ano == this.ano && ((mes == this.mes && dia > this.dia) || (mes > this.mes))))
            return true;    
        return false;
    }

    public boolean equals(int dia, int mes, int ano){
        if((this.dia == dia) && (this.mes == mes) && (this.ano == ano))
            return true;
        return false;
    }

    public String toString(){
        String data;
        if(dia < 10){
            data = String.format("0%d/", dia);
        } else {
            data = String.format("%d/", dia);
        }
        if(mes < 10){
            data = data.concat(String.format("0%d/", mes));
        } else {
            data = data.concat(String.format("%d/", mes));
        }
        data = data.concat(String.format("%d", ano));
        return data;
    }

    private boolean dataValida(int dia, int mes){
        if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes ==10 || mes == 11)
            if(dia <= 30)
                return true;
            else
                return false;
        else if(mes == 2)
            if(dia <= 28)
                return true;
            else
                return false;
        

        return true;
            

        
    }

}
