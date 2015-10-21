import java.io.*;
import java.util.*;
/**
 * 
 * @author Grupo 30
 */
public class GESTAUTS
{
    
    private static RedeGlobalAutores rede;
    private static Menu MenuP, MenuAd,MenuAdI,MenuAdII,MenuAdIII;
    private static String nameFile;
    
    public static void main() throws IOException{
        carregarMenus();
        do {
            System.out.println("Bem Vindo à aplicação GestAuts desenvolvida pelo Grupo 30");
            MenuP.executa();
            switch (MenuP.getOpcao()) {
                case 1: {
                    nameFile = "publicx.txt";
                    Crono.start();
                    rede = readFile();
                    Crono.stop();
                    System.out.print('\u000C');
                    System.out.println("\nTempo leitura do ficheiro e população da estrutura de dados: "+Crono.print()+" segundos\n");
                    MenuAd();
                    break;
                }
                case 2: {
                    nameFile = "publicx_x4.txt";
                    Crono.start();
                    rede = readFile();
                    Crono.stop();
                    System.out.print('\u000C');
                    System.out.println("\nTempo leitura do ficheiro e população da estrutura de dados: "+Crono.print()+" segundos\n");
                    MenuAd();
                    break;
                }    
                case 3: {
                    nameFile = "publicx_x6.txt";
                    Crono.start();
                    rede = readFile();
                    Crono.stop();
                    System.out.print('\u000C');
                    System.out.println("\nTempo leitura do ficheiro e população da estrutura de dados: "+Crono.print()+" segundos\n");
                    MenuAd();
                    break;
                }
                case 4: {
                    System.out.print("\nInsira o nome do ficheiro que pretende carregar: ");
                    nameFile = Input.lerString();
                    Crono.start();
                    rede = readFile();
                    Crono.stop();
                    System.out.print('\u000C');
                    System.out.println("\nTempo leitura do ficheiro e população da estrutura de dados: "+Crono.print()+" segundos\n");
                    MenuAd();
                    break;
                }
                case 5: {
                    rede = open();
                    if (rede == null) System.out.println("\nO ficheiro rede.obj não existe, por favor escolha outra opção\n");
                    else { 
                        Crono.start();
                        rede = readFile();
                        Crono.stop();
                        System.out.print('\u000C');
                        System.out.println("\nTempo leitura do ficheiro e população da estrutura de dados: "+Crono.print()+" segundos\n");
                        MenuAd(); 
                    }
                    break;
                }
            }
        } while (MenuP.getOpcao()!=0);
        
        System.out.println("Até breve!...");
    }
    
    public static void MenuAd() throws IOException{
        do {
            MenuAd.executa();
            switch (MenuAd.getOpcao()) {
                case 1: { // Consultas estatíticas
                    MenuAdI();
                    break;
                }
                case 2: { // Consultas indexadas por ano
                    MenuAdII();
                    break;
                }    
                case 3: { // Consultas globais especiais
                    MenuAdIII();
                    break;
                }
                case 4: { // Gravar estado
                    Crono.start();
                    save(rede);
                    Crono.stop();
                    System.out.println("\nTempo de exec: "+Crono.print()+" segundos\n");
                    break;
                }
            }
        } while (MenuAd.getOpcao()!=0);
        
        System.out.println("Até breve!...");
    }
    
    public static void MenuAdI() {
        do {
            MenuAdI.executa();
            switch (MenuAdI.getOpcao()) {
                case 1: { // 1.1
                    System.out.print('\u000C');
                    System.out.println("\nRelatorio de leitura do ficheiro " + nameFile + ":\n");
                    System.out.println(rede.Relatorio() + "\n");
                    break;
                }
                case 2: { // 1.2
                    System.out.print('\u000C');
                    System.out.println("Número total de autores: " + (rede.getAutores().size()));
                    System.out.println("Número total de artigos publicados por um único autor: " + rede.getOnlyOne());
                    System.out.println("Número total de autores que apenas publicaram a solo: " + rede.sempreSolo());
                    System.out.println("Número total de autores que nunca publicaram a solo: " + rede.nuncaSolo());
                    break;
                } 
                case 3: { // 1.2.4
                    System.out.print('\u000C');
                    System.out.print("Indique o número de artigos (o X): " );
                    int x = Input.lerInt();
                    Crono.start();
                    int y = rede.MorethanX(x);
                    Crono.stop(); 
                    System.out.println("Tempo de exec: "+Crono.print()+" segundos\n");
        
                    System.out.println(y + "\n");
                    break;
                }
                case 4: { // 1.3
                    System.out.print('\u000C');
                    Crono.start();
                    String x = rede.getTab();
                    Crono.stop();
                    System.out.println("Tempo de exec: "+Crono.print()+" segundos\n");
         
                    System.out.println(x + "\n");
                    break;
                }
            }
        } while (MenuAdI.getOpcao()!=0);
    }
    
    public static void MenuAdII(){
        do {
            MenuAdII.executa();
            int m, M, t;
            switch (MenuAdII.getOpcao()) {
                case 1: { 
                    System.out.print('\u000C');
                    System.out.print("Introduza o tamanho da lista que pretende (o X): ");
                    t = Input.lerInt();
                    System.out.println("Introduza o intervalo de anos que pretende");
                    System.out.print("Indique o limite inferior: ");
                    m = Input.lerInt();
                    System.out.print("Indique o limite superior: ");
                    M = Input.lerInt();
                    
                    if(m < rede.getMinY() || M > rede.getMaxY() || m > M){ System.out.println("Intervalo de anos inválido."); break; }
                    
                    Crono.start();
                    Iterator<ParAutPubs> aux = rede.MorePub(m,M).iterator();
                    Crono.stop();
                    System.out.println("\nTempo de exec: "+Crono.print()+" segundos\n");
         
                    TreeSet<String> result = new TreeSet<>();
                    int n=0;
                    while(aux.hasNext() && ++n <= t){   
                        ParAutPubs a = aux.next();
                        result.add(a.getNome());
                    }
                    Iterator<String> it = result.iterator();
                    while(it.hasNext()){ System.out.print(it.next() + "\n"); }
                    break;
                }
                case 2: { 
                    System.out.print('\u000C');
                    System.out.print("Introduza o tamanho da lista que pretende (o X): ");
                    t = Input.lerInt();
                    System.out.println("Introduza o intervalo de anos que pretende");
                    System.out.print("Indique o limite inferior: ");
                    m = Input.lerInt();
                    System.out.print("Indique o limite superior: ");
                    M = Input.lerInt();
                    
                    if(m < rede.getMinY() || M > rede.getMaxY() || m > M){ System.out.println("Intervalo de anos inválido."); break; }
                    
                    Crono.start();
                    Iterator<ParAutsPubs> it = rede.BestPar(m,M).iterator();
                    Crono.stop();
                    System.out.println("\nTempo de exec: "+Crono.print()+" segundos\n");
         
                    int n = 0;
                    while(it.hasNext() && ++n <= t){   
                        System.out.print(it.next().toString());
                    }
                    break;
                }    
                case 3: { 
                    System.out.print('\u000C');
                    System.out.print("Introduza o tamanho da lista que pretende (max 3): ");
                    t = Input.lerInt();
                    if (t > 3 || t == 0) { System.out.println("Tamanho da lista inválido"); break; }
                    System.out.println("Introduza a lista: ");
                    ArrayList<String> aux = new ArrayList<>();
                    int n = 0;
                    while(n < t){
                        String y = Input.lerString();
                        if (!y.equals("")){
                            aux.add(y);
                            n++;
                        }
                    }
                    System.out.println("Introduza o intervalo de anos que pretende");
                    System.out.print("Indique o limite inferior: ");
                    m = Input.lerInt();
                    System.out.print("Indique o limite superior: ");
                    M = Input.lerInt();
                    if(m < rede.getMinY() || M > rede.getMaxY() || m > M){ System.out.println("Intervalo de anos inválido."); break; }
                    
                    try{
                        Crono.start();
                        Iterator<String> it = rede.ComunsCoAut(m,M,aux).iterator();
                        Crono.stop();
                        System.out.println("\nTempo de exec: "+Crono.print()+" segundos\n");
                        
                        n = 0;
                        while(it.hasNext() && n < 15){
                            System.out.print(it.next() + "\n");
                            n++;
                            if(n == 15){
                               System.out.println("\nDeseja ver mais?"); 
                               System.out.println("\t 1 - Sim");
                               System.out.println("\t Qualquer outro para voltar ao menu");
                               System.out.print("\t Indique a opção:");
                               int op = Input.lerInt();
                               if(op==1) n = 0;
                            }
                        }
                    }catch(AutorNaoExiste e){
                        System.out.println(e);
                    }
                    break;
                }
                case 4: {
                    System.out.print('\u000C');
                    System.out.println("Introduza o intervalo de anos que pretende");
                    System.out.print("Indique o limite inferior: ");
                    m = Input.lerInt();
                    System.out.print("Indique o limite superior: ");
                    M = Input.lerInt();
                    
                    if(m == M || m < rede.getMinY() || M > rede.getMaxY() || m > M){ System.out.println("Intervalo de anos inválido."); break; }
                    
                    try{
                       Crono.start();
                       Iterator<String> aux = rede.ListaMPub(m,M).iterator();
                       Crono.stop();
                       System.out.println("\nTempo de exec: "+Crono.print()+" segundos\n");
         
                       int n = 0;
                       while(aux.hasNext() && n < 15){
                           System.out.print(aux.next() + "\n");
                           n++;
                           if(n == 15){
                               System.out.println("\nDeseja ver mais?"); 
                               System.out.println("\t 1 - Sim");
                               System.out.println("\t Qualquer outro para voltar ao menu");
                               System.out.print("\t Indique a opção:");
                               int op = Input.lerInt();
                               if(op==1) n = 0;
                           }
                       }
                    }catch(NinguemPublicou e){
                        System.out.println(e);
                    }
                    break;
                }
            }
        } while (MenuAdII.getOpcao()!=0);
    }
    
    public static void MenuAdIII() {
        do {
            MenuAdIII.executa();
            switch (MenuAdIII.getOpcao()) {
                case 1: {
                    System.out.print('\u000C');
                    LinhasDup();
                    break;
                }
                case 2: {
                    System.out.print('\u000C');
                    System.out.print("Indique a letra que pretende consultar: ");
                    String letra = Input.lerString();
                    char l = letra.charAt(0);
                    Crono.start();
                    TreeSet<String> aux = rede.AllAutL(l);
                    Crono.stop();
                    System.out.println("\nTempo de exec: "+Crono.print()+" segundos\n");
         
                    System.out.print("Total de autore começados com a letra " + l + ": " + aux.size() + "\n");
                    Iterator<String> it = aux.iterator();
                    int n = 0;
                    while(it.hasNext() && n < 15){
                        String x = it.next();
                        System.out.print(" - " + x + ";\n");
                        n++;
                        if(n == 15){
                            System.out.println("\nDeseja ver mais?"); 
                            System.out.println("\t 1 - Sim");
                            System.out.println("\t Qualquer outro para voltar ao menu");
                            System.out.print("\t Indique a opção:");
                            int op = Input.lerInt();
                            if(op==1) n = 0;
                        }
                    }
                    break;
                }    
                case 3: {
                    System.out.print('\u000C');
                    System.out.print("Introduza o Autor que pretende consultar: ");
                    String nome = Input.lerString();
                    nome.trim();
                    System.out.print("Ano: ");
                    int ano = Input.lerInt();
                    try{ 
                        Crono.start();
                        String x = rede.AllCoAutAndPub(nome,ano);
                        Crono.stop();
                        System.out.println("\nTempo de exec: "+Crono.print()+" segundos\n");
         
                        System.out.print(x);
                    }catch(AutorNaoPublicouAno e){
                        System.out.println(e);
                    }
                    break;
                }
                case 4: { 
                    System.out.print('\u000C');
                    System.out.print("Introduza o nome do Autor que pretende consultar: ");
                    String nome = Input.lerString();
                    nome.trim();
                   try{ 
                       Crono.start();
                       TreeSet<String> aux = rede.AllCoAut(nome);
                       Crono.stop();
                       System.out.println("\nTempo de exec: "+Crono.print()+" segundos\n");
                       
                       Iterator<String> it = aux.iterator();
                       int n = 0;
                       while(it.hasNext() && n < 15){
                            String x = it.next();
                            System.out.print(" - " + x + ";\n");
                            n++;
                            if(n == 15){
                               System.out.println("\nTotal de Coautores: " + aux.size());
                               System.out.println("\nDeseja ver mais?"); 
                               System.out.println("\t 1 - Sim");
                               System.out.println("\t Qualquer outro para voltar ao menu");
                               System.out.print("\t Indique a opção:");
                               int op = Input.lerInt();
                               if(op==1) n = 0;
                            }
                       }
                       System.out.print("Total de Coautores: " + aux.size());
                    }catch(AutorNaoExiste e){
                        System.out.println(e);
                    }
                    break;
                }
            }
        } while (MenuAdIII.getOpcao()!=0);
    }
    
    private static void LinhasDup() {
        System.out.println("Linhas duplicadas no ficheiro");
        ArrayList<String> linhas = new ArrayList<>();
        Scanner fichScan = null;
        try{
            Crono.start();
            fichScan = new Scanner(new FileReader(nameFile));
            fichScan.useDelimiter(System.getProperty("line.separator"));
            while(fichScan.hasNext()) linhas.add(fichScan.next());
        }
        catch(IOException e) { System.out.println(e.getMessage()); }
        Crono.stop();
        System.out.println("\nTempo de exec: "+Crono.print()+" segundos\n");
        HashSet<String> noDupRecs = new HashSet<String>(linhas);
        System.out.println("Número de linhas lidas: " + linhas.size());
        System.out.println("Número de linhas em duplicado: " + (linhas.size() - noDupRecs.size()));;
    }
    
    private static void carregarMenus() {
        String[] ops = {
            "publicx.txt",
            "publicx_x4.txt",
            "publicx_x6.txt",
            "Inserir nome do ficheiro",
            "Carregar objecto publicx.obj"
        };
        String [] opsad = {
            "Consultas Estastícas",
            "Consultas indexadas por ano ou anos",
            "Consultas globais especiais",
            "Gravar estado"
        };
        
        String [] opsad1 = {
            "Relatorio de leitura",
            "Números gerais do ficheiro",
            "Total de autores que publicaram mais de X artigos no intervalo de anos",
            "Concultar tabela de publicações"
        };
        
        String [] opsad2 = {
            "Nomes dos X autores que mais publicaram no intervalo de anos",
            "Os X pares de autores com mais artigos publicados em co-autorias",
            "Listagem de todos os co-autores comuns aos autores de uma lista",
            "Listagem nomes dos autores que publicaram artigos em todos os anos de um dado intervalo"
        };
        
        String [] opsad3 = {
            "Total de linhas em duplicado",
            "Nomes de todos os autores começados por uma determinada letra",
            "Determinar todos os co-autores e somatório de artigos publicados num dado anos",
            "Todos os coautores de um dado autor"
        };

        MenuP = new Menu(ops);
        MenuAd = new Menu(opsad);
        MenuAdI = new Menu(opsad1);
        MenuAdII = new Menu(opsad2);
        MenuAdIII = new Menu(opsad3);
    }
    
    public static RedeGlobalAutores readFile() throws IOException{
        System.out.println("\nA ler o ficheiro " + nameFile + " ...");
        
        BufferedReader parser = null;
        
        RedeGlobalAutores aux = new RedeGlobalAutores();
        
        try{
            FileReader ficheiro = new FileReader(nameFile);
            parser = new BufferedReader(ficheiro); 
            String pub = "";            
        
            while( (pub = parser.readLine()) != null ){
                if( !pub.equals("") ){ 
                    ArrayList<String> aut = new ArrayList<>();
                    int ano = 0;
                    int count = 0;
                
                    String[] tokens = pub.split(",");
                    count = (tokens.length)-1;
                    
                    int data = 0;
                    for (String autor : tokens) {
                        if(data == count){
                            ano = Integer.parseInt(autor.trim());
                        }
                        else{
                            aut.add(autor.trim());
                            data++;
                        }
                    }   
                    aux.addPub(aut,ano);
                }   
            }
        }catch (IOException e){
            System.out.println("\nErro na leitura do ficheiro ...\n");
        }
        return aux;
    }
    
    public static RedeGlobalAutores open() throws IOException{
        try{
            System.out.println("\nA carregar a rede global de Autores guardada ...\n");
            String workingDir = System.getProperty("user.dir");
            FileInputStream fin = new FileInputStream(workingDir + "publicx.obj");
            ObjectInputStream oin = new ObjectInputStream(fin);
            return (RedeGlobalAutores)oin.readObject();
        }
        catch (Exception e){
            System.out.println("\nErro a abrir o ficheiro!\n");
            return null;
        }  
    }
    
    public static void save(RedeGlobalAutores rede) throws IOException{
        String workingDir = System.getProperty("user.dir");
        FileOutputStream fos = new FileOutputStream(workingDir + "publicx.obj");
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        try{
            System.out.println("\nA guardar a rede global de Autores existente ...\n");
            oos.writeObject(rede);
            oos.close();
            System.out.println("\nFicheiro guardado com sucesso ...\n");
        }
        catch (IOException e){
            System.out.println("\nErro a gravar o ficheiro!\n");
        }
    }
}
