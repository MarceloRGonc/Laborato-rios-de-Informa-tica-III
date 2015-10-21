import java.io.Serializable;
import java.util.*;

/**
 *
 * @author Grupo 30
 */
class RedeAnualAutores implements Serializable {

    private int ano; // ano das publicações
    private int Tpub; // total de publicações neste ano 
    private TreeMap<String,Autor> autores; // Chave: nome do autor  Valor: Autor correspondente à chave
    
    public RedeAnualAutores(int ano){
        this.ano = ano;
        this.Tpub = 1;
        this.autores = new TreeMap<>();
    } 

    public RedeAnualAutores(int ano, int total, Map<String,Autor> autores) {
        this.ano = ano;
        this.Tpub = total;
        Iterator<Map.Entry<String, Autor>> it = autores.entrySet().iterator();
        while(it.hasNext()) {
            Map.Entry<String,Autor> entry = it.next();
            this.autores.put(entry.getKey(),entry.getValue().clone());
        }
    }
    
    public RedeAnualAutores(RedeAnualAutores r){
        this.ano = r.getAno();
        this.Tpub = r.getTPub();
        this.autores = new TreeMap<>();
        
        Iterator<Map.Entry<String, Autor>> it = r.getAutores().entrySet().iterator();
        while(it.hasNext()) {
            Map.Entry<String,Autor> entry = it.next();
            this.autores.put(entry.getKey(),entry.getValue().clone());
        }
    }
    
    public int getAno(){ return this.ano; }
    public int getTPub() { return this.Tpub; }
    
    public Map<String,Autor> getAutores() {
        TreeMap<String,Autor> r = new TreeMap<>();
        Iterator<Map.Entry<String, Autor>> it = autores.entrySet().iterator();
        while(it.hasNext()) {
           Map.Entry<String,Autor> entry = it.next();
           r.put(entry.getKey(),entry.getValue().clone());
        }
        return r;
    }

    TreeSet<String> getAAno() {
        TreeSet<String> r = new TreeSet<String>();
        Iterator<Map.Entry<String, Autor>> it = this.autores.entrySet().iterator();
        while(it.hasNext()) {
           Map.Entry<String,Autor> entry = it.next();
           r.add(entry.getValue().getNome());
        }
        return r;
    }

    public void setTpub(int Tpub) { this.Tpub = Tpub; }
    public void setAno(int ano) { this.ano = ano; }
    public void setAutores(TreeMap<String, Autor> r) {
        Iterator<Map.Entry<String, Autor>> it = r.entrySet().iterator();
        while(it.hasNext()) {
            Map.Entry<String,Autor> entry = it.next();
            this.autores.put(entry.getKey(),entry.getValue().clone());
        }
    }

    public boolean equals(Object obj) {
        if (obj == null) { return false; }
        if (getClass() != obj.getClass()) { return false; }
        
        RedeAnualAutores other = (RedeAnualAutores) obj;
        if (this.ano != other.ano) { return false; }
        if (this.Tpub != other.Tpub) { return false; }
       
        for(Map.Entry<String,Autor> entry : this.autores.entrySet())
          if(!other.autores.containsKey(entry.getKey()))
             return false; 
        return true;
    }

    public String toString() {
       StringBuilder s = new StringBuilder();
       s.append("Ano: ").append(ano).append("\n");
       s.append("Total de publicações neste ano: ").append(Tpub).append("\n");
       s.append("Total de autores que publicaram neste ano: ").append(autores.size()).append("\n");    
       return s.toString();     
    }

    public RedeAnualAutores clone(){ return new RedeAnualAutores(this); }
  
    void incTPub() { this.Tpub++; }
    
    public int numAut(){ return this.autores.size(); }
    
    public int TpubAut(String nome){
        if(containsAut(nome)) return this.autores.get(nome).getTPub();
        return 0;
    }
    
    public boolean containsAut(String autor){ return this.autores.containsKey(autor); }
    
    public void addAutorAno(ArrayList<String> nomes){

        if(autores.size()==1){
            if(this.autores.containsKey(nomes.get(0))){
                Autor novo = this.autores.get(nomes.get(0));
                this.autores.get(nomes.get(0)).incAlone();
            }
            else{
                Autor novo = new Autor(nomes.get(0),0,1);
                this.autores.put(novo.getNome(),novo);
            }
        }
        else{
            for(String nome : nomes){
                Autor novo = new Autor(nome,0,0);
    
                if(this.autores.containsKey(nome)){
                    ArrayList<String> coautores = new ArrayList<>();
                    for(String n : nomes)
                        if(!nome.equals(n))
                            coautores.add(n);
                    this.autores.get(nome).addCoAutores(coautores);
                    this.autores.get(nome).incWith();
                }
                else{
                    novo = new Autor(nome,1,0);
                    ArrayList<String> coautores = new ArrayList<>();
                    for(String n : nomes)
                        if(!nome.equals(n))
                            coautores.add(n);
                    novo.addCoAutores(coautores);
                    this.autores.put(nome,novo);
                }
            }
        }
    }
}