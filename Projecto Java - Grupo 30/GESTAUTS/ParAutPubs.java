import java.io.Serializable;
import java.util.*;

/**
 * 
 * @author Grupo 30
 */
public class ParAutPubs implements Serializable {
    String Nome; // nome do autor
    int total; // Total de publicações
    int with; // Total de publicações que publicaram  com co-autores;
    int alone; // Total de publicações que publicaram a solo;

    public ParAutPubs() {
        this.Nome = "";
        this.total = 1;
        this.with = 0;
        this.alone = 0;
    }
    
    public ParAutPubs(ParAutPubs m) {
        this.Nome = m.getNome();
        this.total = m.getTotal();
        this.with = m.getWith();
        this.alone = m.getAlone();
    }
    
    public ParAutPubs(String Nome, int total) {
        this.Nome = Nome;
        this.total = total;
        this.with = 0;
        this.alone = 0;
    }

    public ParAutPubs(String Nome, int total, int with, int alone) {
        this.Nome = Nome;
        this.total = total;
        this.with = with;
        this.alone = alone;
    }
    
    public String getNome() { return this.Nome;    }

    public int getTotal() { return this.total; }
    
    public int getWith() { return this.with; }

    public int getAlone() { return this.alone; }

    public void setNome(String Nome) { this.Nome = Nome; }

    public void setTotal(int total) { this.total = total; }
    
    public void setWith(int with) { this.with = with; }

    public void setAlone(int alone) { this.alone = alone; }
    
    public void incTotal() { this.total++; }
    
    public void incWith() { this.with++; }
    
    public void incAlone() { this.alone++; }
    
    public boolean equals(Object obj) {
        if (obj == null) { return false; }
        if (this.getClass() != obj.getClass()) { return false; }
        
        ParAutPubs other = (ParAutPubs) obj;
 
        return this.Nome.equals(other.getNome());
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append("Nome do autor: ").append(this.getNome()).append("\n");
        s.append("Total de publicações realizadas: ").append(this.total).append("\n");
        return s.toString();   
    }

    public ParAutPubs clone(){ return new ParAutPubs(this); }
    
    public int hashCode() {
        return Arrays.hashCode(new Object[] {Nome, total});
    }

}
