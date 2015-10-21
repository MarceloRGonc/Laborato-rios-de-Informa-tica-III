import java.io.Serializable;
import java.util.*;

/**
 *
 * @author Grupo 30
 */
class Autor implements Serializable{
    String Nome; // nome do autor
    int with; // Total de publicações que publicaram  com co-autores;
    int alone; // Total de publicações que publicaram a solo;

    TreeSet<CoAutor> coautores; // Autores com que publicou e total de publicações

    public Autor() {
        this.Nome = "";
        this.with = 0;
        this.alone = 0;
        this.coautores = new TreeSet<>(new CoAutComparator());
    }
    
    public Autor(Autor m) {
        this.Nome = m.getNome();
        this.with = m.getWith();
        this.alone = m.getAlone();
        this.coautores = m.getCoAutores();
    }
    
    public Autor(String Nome, int with, int alone) {
        this.Nome = Nome;
        this.with = with;
        this.alone = alone;
        this.coautores = new TreeSet<>(new CoAutComparator());
    }

    public Autor(String Nome, int with, int alone, Set<CoAutor> coautores) {
        this.Nome = Nome;
        this.with = with;
        this.alone = alone;
        
        Iterator<CoAutor> it = coautores.iterator();
        while (it.hasNext()) {
            CoAutor entry = it.next();
            this.coautores.add(entry.clone());
        }
    }
    
    public String getNome() { return this.Nome; }

    public int getWith() { return this.with; }

    public int getAlone() { return this.alone; }

    public int getTPub() { return (this.alone + this.with); }
    
    public TreeSet<CoAutor> getCoAutores() {
        TreeSet<CoAutor> r = new TreeSet<>(new CoAutComparator());
        Iterator<CoAutor> it = this.coautores.iterator();
        while (it.hasNext()) {
            CoAutor entry = it.next();
            r.add(entry.clone());
        }   
        return r;
    }
    
     public TreeSet<String> getCoAut() {
        TreeSet<String> r = new TreeSet<>();
        Iterator<CoAutor> it = this.coautores.iterator();
        while (it.hasNext()) {
            CoAutor entry = it.next();
            r.add(entry.getNome());
        }   
        return r;
    }

    public void setNome(String Nome) { this.Nome = Nome; }

    public void setWith(int with) { this.with = with; }

    public void setAlone(int alone) { this.alone = alone; }

    public void setCoautores(Set<CoAutor> coautores) {
        this.coautores = new TreeSet<CoAutor>(new CoAutComparator());
        Iterator<CoAutor> it = coautores.iterator(); 
        while (it.hasNext()) {
            CoAutor entry = it.next();
            this.coautores.add(entry.clone());
        }      
    }
    
    public boolean incCoAutor(String nome) {
        Iterator<CoAutor> it = this.coautores.iterator();
        while (it.hasNext()) {
            CoAutor entry = it.next();
            if(entry.getNome().equals(nome)){
                entry.incPub();
                return true;
            }
        }
        return false;
    }
    
    public void addCoAutores(ArrayList<String> coAutores) {

        Iterator<String> it = coAutores.iterator();
        
        while (it.hasNext()) {
            String autor = it.next();
            if (incCoAutor(autor)){
                return;
            }
            else{
                CoAutor novo = new CoAutor(autor);
                this.coautores.add(novo); 
            }           
        }  
    }

    public void incWith() { this.with++; }
    
    public void incAlone() { this.alone++; }

    public boolean equals(Object obj) {
        if (obj == null) { return false; }
        if (getClass() != obj.getClass()) { return false; }
        
        Autor other = (Autor) obj;
 
        return this.Nome.equals(other.Nome);
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append("\nInformação do Autor: ").append(this.Nome).append("\n");
        s.append("Total de publicações registadas: ").append(this.getTPub()).append("\n");
        s.append("Total de publicações realizadas a solo: ").append(this.getAlone()).append("\n");
        s.append("Total de publicações realizadas a solo com outros autores: ").append(this.getWith()).append("\n");
        return s.toString();   
    }

    public Autor clone(){ return new Autor(this); }

    public String CoAutores(){
        StringBuilder s = new StringBuilder();
        s.append("\nLista de Co-Autor do Autor: ").append(this.Nome).append("\n");
        s.append("Co-Autor").append("\n");
        
        for(CoAutor entry : this.coautores){
            s.append(entry.getNome());
            s.append("\n");
        }        
        s.append("\nTotal de publicações registadas em co-Autorias: ").append(this.getWith()).append("\n");
        return s.toString(); 
    }
}
