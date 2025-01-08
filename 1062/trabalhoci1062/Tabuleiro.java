import java.util.*;

public class Tabuleiro {
    
    private ArrayList<ArrayList<Entidade>> entidades; 
    private ArrayList<FakeNews> fakeNews;
    private ArrayList<Jogador> jogadores;
    
    //Construtor
    public Tabuleiro() {}
    
    //==========================================
    //Getters e setters
    //==========================================

    public ArrayList<ArrayList<Entidade>> getEntidades() {
        return entidades;
    }
    private void setEntidades(ArrayList<ArrayList<Entidade>> entidades) {
        this.entidades = entidades;
    }
    
    /*
    *   Pega uma entidade do tabuleiro
    *   Posicao pos        Posição da entidade
    *   retorna a entidade da posição, null se ela estiver vazia
    */
    private Entidade getEntidade(Posicao pos){
        ArrayList<Entidade> row = this.entidades.get(pos.getPosY());
        Entidade e = row.get(pos.getPosX());
        return e;
    }

    public ArrayList<FakeNews> getFakeNews() {
        return fakeNews;
    }
    private void setFakeNews(ArrayList<FakeNews> fakeNews) {
        this.fakeNews = fakeNews;
    }

    public ArrayList<Jogador> getJogadores(){
        return this.jogadores;
    }
    private void setJogadores(ArrayList<Jogador> jogadores) {
        this.jogadores = jogadores;
    }

    public int getJogadorIndex(Jogador jog) {
        for(int i = 0; i < this.jogadores.size(); i++){
            Jogador j = this.jogadores.get(i);
            if(jog.equals(j))
                return i;
        }
        return 0;
    }
    public int getFakeNewsIndex(FakeNews fake) {
        for(int i = 0; i < this.fakeNews.size(); i++){
            FakeNews f = this.fakeNews.get(i);
            if(fake.equals(f))
                return i;
        }
        return 0;
    }

    public Jogador getJogador(int index){
        return this.jogadores.get(index);
    }
    public Jogador getJogador(Posicao pos){
        Entidade e = this.getEntidade(pos);
        if(this.entidadeTipo(e) == 2)
            return (Jogador) e;
        return null;
    }
    public FakeNews getOneFakeNews(int index){
        return this.fakeNews.get(index);
    }

    public int getJogadoresQtd(){
        return this.jogadores.size();
    }
    public int getFakeNewsQtd(){
        return this.fakeNews.size();
    }

    //==========================================
    //Metodos
    //==========================================
    
    /*
    * Inicia um jogo no tabuleiro
    * ArrayList<Jogador> jogadores       Jogadores, min 1 max 4
    */
    public void iniciaJogo(ArrayList<Jogador> jogadores){
        
        System.out.println("\n\nGerando tabuleiro...");        
        this.criaMapa();
       
        System.out.println("Adicionando jogadores...");
        this.posicionaJogadores(jogadores);

        System.out.println("Adicionando áreas restritas...");        
        for(int i = 0; i < 4; i++){
            this.inicializaAreaRestrita();
        }
        
        System.out.println("Adicionando os itens");
        for(int i = 0; i < 2; i++){
            this.geraItens();
        }

        System.out.println("Adicionando Fakenews...");
        this.inicializaFakeNews();
        
    }

    /*
    *   Executa o turno de todas as fakenews presentes no tabuleiro 
    */
    public void turnoFakeNews() throws InterruptedException{
        FakeNews f;
        Posicao p;
        for(int index = this.getFakeNewsQtd() -1; index >= 0 ; index--){  
            f = this.getOneFakeNews(index);
            p = f.movimentaFakeNews();
            this.limpaTerminal();
            if(this.resolveMovimento(f, p) == 1){
                this.morteFakenews();
            }
            this.imprimeTabuleiro();
            Thread.sleep(2000);
        }
    }

    /*
    * Cria uma FakeNews no tabuleiro
    * int tipo
    * boolean duplicada
    * Posição posAtual 
    */
    public FakeNews geraFakeNews(int tipo, boolean duplicada, Posicao posAtual){
        Posicao pos = new Posicao();
        if(!duplicada)
            pos = geraPosicaoVazia(7,1);
        else{
            int posX = posAtual.getPosX();
            int posY = posAtual.getPosY();
            Random aleatorio = Aleatorio.getAleatorio();
            int newPos = 0;
            do{
                int x = (aleatorio.nextInt(4) % 3) - 1;
                int y = (aleatorio.nextInt(4) % 3) - 1;
                pos.setPosX(posX + x);
                pos.setPosY(posY + y);
                newPos = checaPosicao(pos);
            }while(((newPos % 2 )!= 0) == true);

            if(newPos == 2){  //nova fakeNews gerada em um jogador
                apagaEntidade(pos);
            } else if(newPos == 4){ //nova fakeNews gerada em um novoItem;
                geraFakeNews(tipo, true, pos); //gera uma nova fakeNews
                geraItens(); //repõe o item perdido
            }

        }
        FakeNews fake;
        switch (tipo) {
            case 1:
                fake = new F1(pos);
                break;
            case 2:
                fake = new F2(pos);
                break;
            case 3:
                fake = new F3(pos);
                break;
            default:
                return null;
        }
        this.adicionaNoTabuleiro(fake);
        this.getFakeNews().add(fake);
        return fake;
    }

    /*
    *   Cria um item aleatorio em uma posição vazia do tabuleiro
    */
    public void geraItens(){
        Posicao pos = this.geraPosicaoVazia(9,0);
        Random aleatorio = Aleatorio.getAleatorio();
        int tipo = (aleatorio.nextInt(5) % 4);
        Item item;
        switch(tipo){
            case 0:
                item = new Boato(pos);
                break;
            case 1:
                item = new Denuncia(pos);
                break;
            case 2:
                item = new Fuga(pos);
                break;
            case 3:
                item = new Noticia(pos);
                break;
            default:
                return;
        }

        this.adicionaNoTabuleiro(item);
    }

    /*
    * Deleta completamente uma entidade do tabuleiro
    * Posição Posicao         Posição da Entidade a ser deletada 
    */
    public void apagaEntidade(Posicao posicao){
        Entidade e = this.getEntidade(posicao);

        /* Remove entidade e do Tabuleiro*/
        this.removeDoTabuleiro(posicao);
    
        /* Remove dos arrays de FakeNews ou Jogador, se necessario */
        if(e instanceof FakeNews){
            fakeNews.remove((FakeNews) e);
            return;
        } 
        if(e instanceof Jogador){
            jogadores.remove((Jogador) e);
            return;
        }
    }

    /*
    *   Resolve uma tentativa de movimento de uma entidade no tabuleiro
    *   Entidade e              Entidade que está tentando o movimento
    *   Posição newPos          Posição que a entidade quer se mover
    *   Retorna 1 se uma Fakenews morreu, 0 caso contrario
    */    
    public int resolveMovimento(Entidade e, Posicao newPos){
        int valorPosicao = checaPosicao(newPos);

        if(e instanceof Jogador){
            Jogador j = (Jogador) e;
            /* Posição invalida */
            if(valorPosicao == 1 || valorPosicao == 3 || valorPosicao == -1){
                morteJogador(j);                    
                this.apagaEntidade(j.getPosicao());
            } else {
                /* Teleportou para a mesma posição */
                if(newPos.getPosX() == j.getPosicao().getPosX() && newPos.getPosY() == j.getPosicao().getPosY())
                    return 0;
                /* Posição Valida */
                this.removeDoTabuleiro(j.getPosicao());
                j.mudaPosicao(newPos);
                /* Posição é item */
                if(valorPosicao == 4) {    
                    Item i = (Item)this.getEntidade(newPos);
                    j.setItem(i);
                    this.geraItens();
                }else if(valorPosicao == 2) {
                    /* Posição é outro jogador*/   
                    morteJogador(j);                    
                    this.apagaEntidade(j.getPosicao());
                    return 0; // um jogador morreu
                }
                this.adicionaNoTabuleiro(j);
                return 0; //jogador completou a ação dele
                
            }
        } else {
            /* FakeNews */
            FakeNews f = (FakeNews) e; 
            if(valorPosicao == 3 || valorPosicao == 1 || valorPosicao == -1){
                this.apagaEntidade(f.getPosicao());
                return 1;
            } else {

                    this.removeDoTabuleiro(f.getPosicao());
                    f.mudaPosicao(newPos);

                if(valorPosicao == 2) {
                    morteJogador(this.getJogador(newPos));                    
                    this.apagaEntidade(newPos);
                } else if(valorPosicao == 4){
                    int tipo;
                    if(f instanceof F1){
                        tipo = 1;
                    }else if(f instanceof F2){
                        tipo = 2;
                    }else{
                        tipo = 3;
                    }
                    this.geraFakeNews(tipo, true, newPos);
                }
                this.adicionaNoTabuleiro(e);
            }
        }
        return 0;
    }
    
    /*
    * Verifica se o jogo acabou, não verifica numero de rounds
    * Retorna true se o jogo acabou
    */
    public boolean fimDeJogo(){
        return (this.getFakeNewsQtd() == 0 || this.getJogadoresQtd() == 0);
    }
    /*
    * "Limpa" o terminal, é pratico pq funciona pra windows e Linux além de deixar um historico
    */
    public void limpaTerminal(){
        System.out.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }

    /*
    *   Imprime no Tabuleiro que uma fakenews morreu
    */
    public void morteFakenews(){
        System.out.println("==============================");
        System.out.println("     Uma FakeNews se foi!     ");
        System.out.println("==============================");
        System.out.println("   Mentira tem perna Curta!   ");
        System.out.println("==============================");
    }

    /*
    *   Imprime no Tabuleiro que umm fakenews morreu
    */
    public void morteJogador(Jogador j){
        System.out.println("==============================");
        System.out.printf("      Jogador %s Morreu!      \n", j.getNome());
        System.out.println("==============================");
        System.out.println("         RIP IN PEACE         ");
        System.out.println("==============================");
    }

    /*
    * Imprime o tabuleiro no terminal
    */
    public void imprimeTabuleiro(){
        this.imprimeDivisorDeLinhas();
        
        this.imprimeCoordenadas();
        for(int i = 0; i < 10; i++){
            this.imprimeDivisorDeLinhas();
            
            /* Imprime a linha em si */
            if(i < 9){
                ArrayList<Entidade> al = this.entidades.get(i);
                System.out.printf("| 0%d ", i+1); /* Imprime as coordenadas da coluna */
                for(int j = 0; j < 9; j++){

                    Entidade e = al.get(j);
                    System.out.print("| ");
                    int tipo = this.entidadeTipo(e);
                    if(tipo == 1){
                        String tipoFakeNews = e.getClass().getSimpleName().concat(" ");
                        this.imprimeEntidade(Cores.ANSI_RED, tipoFakeNews);
                    } 

                    else if (tipo == 2){
                        Jogador jog = (Jogador) e; /* Downcasting para usar o metodo getNome da classe Jogador */
                        String player = "J".concat(jog.getNome()).concat(" ");
                        this.imprimeEntidade(Cores.ANSI_CYAN, player);
                    } 

                    else if (tipo == 3){
                        this.imprimeEntidade(Cores.ANSI_WHITE, "xx ");
                    } 

                    else if (tipo == 4){
                        this.imprimeEntidade(Cores.ANSI_YELLOW, "?? ");
                        
                    } 
                    
                    else {
                        System.out.print("   ");
                    }
                    
                }
                System.out.print("|\n");
            }

            
        }
        System.out.println("\n\n\n\n");
        
    }

    //==========================================
    //Metodos internos 
    //==========================================    
    


    /*
    * Descobre o Tipo de uma entidade
    * Entidade e        Entidade analisada
    * Retorna ::
    *      Se Fakenews      retorna 1
    *      Se Jogador       retorna 2
    *      Se AreaProibida  retorna 3
    *      Se Item          retorna 4
    *      Em outro casa    retorna 0       
    */
    private int entidadeTipo(Entidade e) {
        if(e instanceof FakeNews)
            return 1;
        if(e instanceof Jogador)
            return 2;
        if (e instanceof AreaProibida)
            return 3;
        if (e instanceof Item)
            return 4;
        return 0;
    }

    /*
    * Inicia Atributo Entidades Vazio
    */
    private void criaMapa() {
        ArrayList<ArrayList<Entidade>> map = new ArrayList<ArrayList<Entidade>>(9);
        for(int i = 0; i < 9; i++){
            ArrayList<Entidade> row = new ArrayList<Entidade>(9);
            for(int j = 0; j < 9; j++){
                row.add(j, null);
            }
            map.add(row);
        }

        this.setEntidades(map);
    }

    /*
    * Inicia o Atributo Jogadores e Coloca os Jogadores no tabuleiro
    */
    private void posicionaJogadores(ArrayList<Jogador> jogadores) {
        this.setJogadores(jogadores);
        for (int i = 0; i < jogadores.size(); i++) {
            this.adicionaNoTabuleiro(jogadores.get(i));
        }
    }
    
    /*
    * Inicia o Atributo FakeNews e Coloca os FakeNews no tabuleiro
    */
    private void inicializaFakeNews(){
        ArrayList<FakeNews> fakeNews = new ArrayList<FakeNews>(6);
        this.setFakeNews(fakeNews);
        
        this.geraFakeNews(1, false, null);
        this.geraFakeNews(1, false, null);

        this.geraFakeNews(2, false, null);
        this.geraFakeNews(2, false, null);

        this.geraFakeNews(3, false, null);
        this.geraFakeNews(3, false, null);
    }

    /*
    * Coloca uma area proibida em uma posição aleatoria do tabuleiro
    */
    private void inicializaAreaRestrita(){
        Posicao pos = geraPosicaoVazia(9,0);
        AreaProibida ap = new AreaProibida(pos);

        this.adicionaNoTabuleiro(ap);
    }

    /*
    * Verifica o que está em uma posição do tabuleiro
    * Posicao posicao            A posição a ser verificada
    * Retorna ::
    *      Se Vazia         retorna 0    
    *      Se Fakenews      retorna 1
    *      Se Jogador       retorna 2
    *      Se AreaProibida  retorna 3
    *      Se Item          retorna 4
    *      Caso esteja fora do tabuleiro retorna -1    
    */
    private int checaPosicao(Posicao posicao){
        if(posicao.getPosX() > 8 || posicao.getPosY()>8 ||posicao.getPosX() < 0 || posicao.getPosY() < 0 )
            return -1;
        int ocupacao = this.entidadeTipo(this.getEntidade(posicao));
        return ocupacao;
    }

    /*
    * Adiciona uma entidade no Tabuleiro, sobrescreeve a posição
    * Entidade e              Entidade a ser adicionada
    */
    private void adicionaNoTabuleiro(Entidade e){
        ArrayList<Entidade> row = this.entidades.get(e.getPosicao().getPosY());
        row.set(e.getPosicao().getPosX(), e);
    }

    /*
    * Esvazia uma posição do tabuleiro
    */
    private void removeDoTabuleiro(Posicao pos){
        ArrayList<Entidade> row = this.entidades.get(pos.getPosY());
        row.set(pos.getPosX(), null);
    }
    
    /*
    * Devolve uma posição vazia Aleatoria, caso não exista posição vazia entra em loop
    * int limit              serve para definir o tamanho da área hábil para a geração
    * int offset              utilizada para dar a distância das bordas do tabuleiro
    */
    private Posicao geraPosicaoVazia(int limit, int offset){
        Random aleatorio = Aleatorio.getAleatorio();
        int pX;
        int pY;
        Posicao pos = new Posicao();
        do{
            pX = aleatorio.nextInt(limit) + offset;        
            pY = aleatorio.nextInt(limit) + offset;        
            pos.setPosX(pX);
            pos.setPosY(pY);
        } while(this.checaPosicao(pos) != 0);
        return pos;
    }

    /*
    * Imprime uma entidade no terminal
    * String cor             Strings declaradas em Cores.java
    * String tipoEntidade    Representação em chars da entidade
    */
    private void imprimeEntidade(String cor, String tipoEntidade){
        String clearColor = Cores.ANSI_RESET;
        System.out.print(cor+tipoEntidade+clearColor);
    }

    /*
     * Imprime o divisor de linhas 
     */
    private void imprimeDivisorDeLinhas() {
        for(int j = 0; j < 10; j++){
                System.out.print("+----");   
            }

            System.out.print("+\n");
    }

    /*
     * Imprime as coordenadas das linhas
     */
    private void imprimeCoordenadas(){
        System.out.print("|    ");
        for(int i = 1; i < 10; i++)
            System.out.printf("| 0%d ", i);
        System.out.println("|");
    }
}

