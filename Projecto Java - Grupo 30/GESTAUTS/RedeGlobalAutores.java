import java.io.Serializable;
import java.util.*;

/**
 *
 * @author Grupo 30
 */
public class RedeGlobalAutores implements Serializable {
    int minY; // ano mais antigo
    int maxY; // ano mais recente
    int Tpub; // total de publicações
    int Tnomes; // total de nomes inseridos
    int OnlyOne; // total de artigos publicados por um único autor
    
    TreeMap<Integer, RedeAnualAutores> rede;
    
    HashMap<String,ParAutPubs> autores; 
    
    public RedeGlobalAutores(){
        this.minY = 9999;
        this.maxY = 0;
        this.Tpub = 0;
        this.Tnomes = 0;
        this.OnlyOne = 0;
        this.rede = new TreeMap<Integer, RedeAnualAutores>();
        this.autores = new HashMap<String,ParAutPubs>();
    }

    public RedeGlobalAutores(int minY, int maxY, int Tpub, int Tnomes, int OnlyOne, Map<Integer, RedeAnualAutores> rede, Map<String,ParAutPubs> autores){
        this.minY = minY;
        this.maxY = maxY;
        this.Tpub = Tpub;
        this.Tnomes = Tnomes;
        this.OnlyOne = OnlyOne;
        
        this.rede = new TreeMap<Integer, RedeAnualAutores>();
        this.autores = new HashMap<String,ParAutPubs>();
                
        for(Map.Entry<Integer,RedeAnualAutores> entry : rede.entrySet())
            this.rede.put(entry.getKey(), entry.getValue().clone());
            
        Iterator<Map.Entry<String, ParAutPubs>> it = autores.entrySet().iterator();
        while(it.hasNext()) {
            Map.Entry<String,ParAutPubs> entry = it.next();
            this.autores.put(entry.getValue().getNome(),entry.getValue().clone());
        }
            
    }

    public RedeGlobalAutores(RedeGlobalAutores other) {
       this.minY = other.getMinY();
       this.maxY = other.getMaxY();
       this.Tpub =other.getTPub();
       this.Tnomes = other.getTNomes();
       this.OnlyOne = other.getOnlyOne();
       this.rede = other.getRede();
       this.autores = new HashMap<>();
       
       Iterator<Map.Entry<String,ParAutPubs>> it = this.autores.entrySet().iterator();
       while(it.hasNext()) {
          Map.Entry<String,ParAutPubs> entry = it.next();
          this.autores.put(entry.getValue().getNome(),entry.getValue().clone());
       }
    }

    public String toString() {
       StringBuilder s = new StringBuilder();
       s.append("\nRede Global de autores:\n");
       s.append("Total de artigos publicados: ").append(this.Tpub).append("\n");
       s.append("Total de nomes lidos: ").append(this.Tnomes).append("\n");
       s.append("Total de nomes distintos: ").append(this.getAutores().size()).append("\n");
       s.append("Intervalo de anos das publicações: [").append(this.minY).append(",").append(this.maxY).append("]\n");
       return s.toString(); 
    }
   
    public boolean equals(Object obj) {
        if (obj == null) { return false; }
        if (getClass() != obj.getClass()) { return false; }
         
        RedeGlobalAutores other = (RedeGlobalAutores) obj;
        
        if (this.minY != other.getMinY()) { return false; }
        if (this.maxY != other.getMaxY()) { return false; }
        if (this.Tpub != other.getTPub()) { return false; }
        if (this.Tnomes != other.getTNomes()) { return false; }
        if (this.OnlyOne != other.getOnlyOne()) { return false; }
        
        for(Map.Entry<Integer,RedeAnualAutores> entry : this.rede.entrySet())
          if(!other.getRede().containsKey(entry.getKey()))
             return false; 
        
        for(Map.Entry<String,ParAutPubs> entry : this.autores.entrySet())
          if(!other.getAutores().containsKey(entry.getValue().getNome()))
             return false;      
             
        return true;
    }
    
    public RedeGlobalAutores clone(){
        return new RedeGlobalAutores(this);
    }

    public TreeMap<Integer,RedeAnualAutores> getRede() {
        TreeMap<Integer,RedeAnualAutores> aux = new TreeMap<Integer,RedeAnualAutores>();
        
        Iterator<Map.Entry<Integer, RedeAnualAutores>> it = this.rede.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<Integer,RedeAnualAutores> entry = it.next();
            aux.put(entry.getKey(), entry.getValue().clone());
        }
        
        return aux;    
    }
    
    public HashMap<String,ParAutPubs> getAutores() {
        HashMap<String, ParAutPubs> r = new HashMap<>();
        Iterator<Map.Entry<String,ParAutPubs>> it = this.autores.entrySet().iterator();
        while(it.hasNext()) {
          Map.Entry<String,ParAutPubs> entry = it.next();
          r.put(entry.getValue().getNome(),entry.getValue().clone());
        }
        return r;
    }

    public int getTNomes() { return this.Tnomes; }
    public int getTPub() { return this.Tpub; }
    public int getMinY() { return this.minY; }
    public int getMaxY() { return this.maxY; }
    public int getOnlyOne() { return this.OnlyOne; }
    
    public String Relatorio() {
       StringBuilder s = new StringBuilder();
       s.append("Total de artigos publicados: ").append(Tpub).append("\n");
       s.append("Total de nomes inseridos: ").append(Tnomes).append("\n");
       s.append("Total de nomes distintos inseridos: ").append(this.getAutores().size()).append("\n");
       s.append("Intervalo de anos das publicações: [").append(this.minY).append(",").append(this.maxY).append("]\n");
       return s.toString(); 
    }
    
    public int sempreSolo(){
       int count = 0;
       for(Map.Entry<String,ParAutPubs> entry : this.autores.entrySet()){
          if(entry.getValue().getWith()==0) count++;
       }
       return count;
    }
    
    public int nuncaSolo(){
       int count = 0;
       for(Map.Entry<String,ParAutPubs> entry : this.autores.entrySet()){
          if(entry.getValue().getAlone()==0) count++;
       }
       return count;
    }
    
    public String getTab(){
       StringBuilder s = new StringBuilder();
       s.append("\nTabela de publicações ano a ano\n");
       s.append("__________________________\n");
       s.append(" Ano").append("  |       Publicações|\n");
       s.append("--------------------------\n");
       
       Iterator<Map.Entry<Integer, RedeAnualAutores>> it = this.rede.entrySet().iterator();
       while (it.hasNext()) {
            Map.Entry<Integer,RedeAnualAutores> other = it.next();
            s.append(" " + other.getKey()).append(" |             ").append(other.getValue().getTPub()).append("\n"); 
            s.append("--------------------------\n");
        }

       s.append("Soma dos artigos publicados ano a ano: ").append(this.getTPub()).append(";\n");
      
       return s.toString(); 
    }
    
    public void addPub(ArrayList<String> nomes, int ano){
        RedeAnualAutores r;
        if(this.rede.containsKey(ano)){
            r = this.rede.get(ano);
            r.incTPub();
        }
        else{
            r = new RedeAnualAutores(ano);
            this.rede.put(ano, r);
        }
        
        if(nomes.size() == 1) this.OnlyOne++;
        r.addAutorAno(nomes);
        addParAutPubs(nomes);
        
        this.Tpub++;
        this.Tnomes += nomes.size();
        
        if(ano < this.minY) this.minY = ano;
        if(ano > this.maxY) this.maxY = ano;       
    }
    
    public void addParAutPubs(List<String> nomes){
        Iterator<String> it = nomes.iterator();
        int aux = nomes.size();
        while(it.hasNext()) {
            String entry = it.next();
            ParAutPubs n;
            if(this.autores.containsKey(entry)){
               if(aux == 1) this.autores.get(entry).incAlone();
               else this.autores.get(entry).incWith();
               this.autores.get(entry).incTotal();
            }
            else{
               if(aux == 1) n = new ParAutPubs(entry,1,0,1);
               else n = new ParAutPubs(entry,1,1,0);
               this.autores.put(entry,n);
            }
        }
    }
    
    public int MorethanX(int x){
        int count = 0;
        Iterator<Map.Entry<String,ParAutPubs>> it = this.autores.entrySet().iterator();
        while(it.hasNext()) {
           Map.Entry<String,ParAutPubs> entry = it.next();
           if(entry.getValue().getTotal() > x) count++;
        }
        return count;
    }
    
    public int TPub_Autor(String nome){
        int count = 0;
        Iterator<Map.Entry<Integer, RedeAnualAutores>> it = this.rede.entrySet().iterator();
        
        while(it.hasNext()){
            Map.Entry<Integer, RedeAnualAutores> entry = it.next();
            count += entry.getValue().TpubAut(nome);
        }
        
        return count;   
    }
    
    public TreeSet<ParAutPubs> MorePub(int min, int max){
        TreeMap<String,Integer> auts = new TreeMap<>();
                
        for(Map.Entry<Integer,RedeAnualAutores> entry : this.rede.entrySet()){
            if(entry.getKey() >= min && entry.getKey() <= max){
                for(Map.Entry<String,Autor> autor : entry.getValue().getAutores().entrySet()){
                    if(auts.containsKey(autor.getKey())){
                        auts.put(autor.getKey(),auts.get(autor.getKey()) + autor.getValue().getTPub());
                    }
                    else{
                        auts.put(autor.getKey(),autor.getValue().getTPub());
                    }
                }
            }
        }
        
        TreeSet<ParAutPubs> aux = new TreeSet<>(new ParAutPubsComparator());
        for(Map.Entry<String,Integer> entry : auts.entrySet()){
            ParAutPubs x = new ParAutPubs(entry.getKey(),entry.getValue());
            aux.add(x);
        }
        return aux;
    }

    public TreeSet<ParAutsPubs> BestPar(int min, int max){
        HashMap<ParAutsPubs,Integer> aux = new HashMap<>();
        
        for(RedeAnualAutores r : this.rede.values()){
            if(r.getAno() >= min && r.getAno() <= max){
                for(Autor autor : r.getAutores().values()){
                    for(CoAutor entry : autor.getCoAutores()){
                        ParAutsPubs par = new ParAutsPubs(autor.getNome(),entry.getNome(),0);
                        if(aux.containsKey(par)){
                            aux.put(par, aux.get(par) + entry.getCoAut()); 
                        }
                        else{
                            aux.put(par,entry.getCoAut());
                        }
                    }
                }   
           }
        }
        TreeSet<ParAutsPubs> result = new TreeSet<>(new ParAutsPubsComparator());
        
        for(Map.Entry<ParAutsPubs,Integer> entry : aux.entrySet()){
            ParAutsPubs par = new ParAutsPubs(entry.getKey());
            par.setTotal(entry.getValue());
            result.add(par);
        }
        
        return result;
    }

    public Set<String> ListaMPub(int min, int max) throws NinguemPublicou{
        StringBuilder s = new StringBuilder();
        Map<String,Autor>  aux = this.rede.get(min).getAutores();
        ArrayList<String> r = new ArrayList<>();
        min++;
        while(min<=max){
            Set<String> ano = this.rede.get(min).getAAno();
            Iterator<Map.Entry<String, Autor>> it = aux.entrySet().iterator();
            while(it.hasNext()){
                Map.Entry<String, Autor> autor = it.next();
                if(!ano.contains(autor.getKey())) r.add(autor.getKey());
            }
            Iterator<String> i = r.iterator();
            while(i.hasNext()){
                String m = i.next();
                if(!ano.contains(m)) aux.remove(m);
            }
            r = new ArrayList<>();
            min++;
        }
        if (aux.isEmpty()) throw new NinguemPublicou("Nenhum autor publicou em todos os anos desse intervalo");
        TreeSet<String> result = new TreeSet<>(aux.keySet());

        return result;
    }
    
    public TreeSet<String> AllCoAut(String nome) throws AutorNaoExiste{
        TreeSet<String> result = new TreeSet<>();
        int count = 0;
        for(Map.Entry<Integer,RedeAnualAutores> entry : this.rede.entrySet()){
            for(Map.Entry<String,Autor> autor : entry.getValue().getAutores().entrySet()){
                if(!autor.getValue().getNome().equals(nome)){
                    if(autor.getValue().getCoAut().contains(nome)){
                        count++;
                        result.add(autor.getValue().getNome());
                    }
                }
            }
        }
        return result;
    }
    
    public String AllCoAutAndPub(String nome, int ano) throws AutorNaoPublicouAno{
        StringBuilder s = new StringBuilder();
        
        RedeAnualAutores rede = this.rede.get(ano);
        if(!rede.getAutores().containsKey(nome)){
            throw new AutorNaoPublicouAno("O Autor introduzido não publicou neste ano.");
        }
        else{
            Autor autor = rede.getAutores().get(nome);
            s.append(autor.CoAutores());
        }
        return s.toString();
    }
    
    public TreeSet<String> ComunsCoAut(int min, int max, ArrayList<String> lista) throws AutorNaoExiste{
        TreeSet<String> result = new TreeSet<>();
        int n = 0;
        TreeSet<String> aut1;
        TreeSet<String> aut2;
        TreeSet<String> aut3;
           
        if(lista.size() == 3){
           aut1 = AllCoAut(lista.get(0));
           aut2 = AllCoAut(lista.get(1));
           aut3 = AllCoAut(lista.get(2));
        }else if(lista.size() == 2){
           aut1 = AllCoAut(lista.get(0));
           aut2 = AllCoAut(lista.get(1));
           aut3 = null;
        }else{
           aut1 = AllCoAut(lista.get(0));
           return aut1;
        }
 
        for(String l : aut1){
          if(aut2.contains(l)){
            if(aut3 != null && aut3.contains(l)){
                result.add(l);
            }
            else{
                result.add(l);
            }
          }
        } 
        return result; 
    }
    
    public TreeSet<String> AllAutL(char letra){
        TreeSet<String> nomes = new TreeSet<>();
        
        for(RedeAnualAutores r : this.rede.values()){
            for(String a : r.getAAno()){
                if(a.charAt(0) == letra)
                    nomes.add(a);
            }
        }
        return nomes;        
    }
}