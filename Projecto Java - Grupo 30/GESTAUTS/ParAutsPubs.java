import java.io.Serializable;
import java.util.*;

/**
 * 
 * @author Grupo 30
 */
public class ParAutsPubs implements Serializable{
    String Aut1; // nome do autor
    String Aut2; // nome do autor
    int total; // Total de publicações

    public ParAutsPubs() {
        this.Aut1 = "";
        this.Aut2 = "";
        this.total = 0;
    }
    
    public ParAutsPubs(ParAutsPubs m) {
        this.Aut1 = m.getAut1();
        this.total = m.getTotal();
        this.Aut2 = m.getAut2();
    }
    
    public ParAutsPubs(String aut1, String aut2, int total) {
        this.Aut1 = aut1;
        this.total = total;
        this.Aut2 = aut2;
    }
    
    public ParAutsPubs(String aut1, String aut2) {
        this.Aut1 = aut1;
        this.Aut2 = aut2;
        this.total = 0;
    }
    
    public String getAut1() { return this.Aut1; }
    
    public String getAut2() { return this.Aut2; }

    public int getTotal() { return this.total; }
    
    public void setAut1(String Nome) { this.Aut1 = Nome;}
    
    public void setAut2(String Nome) { this.Aut2 = Nome; }

    public void setTotal(int total) { this.total = total; }
    
    public void incTotal() { this.total++; }
    
    public void incTotal(int x){this.total += x;}
    
    public boolean equals(Object obj) {
        if (obj == null) { return false; }
        if (this.getClass() != obj.getClass()) { return false; }
        
        ParAutsPubs other = (ParAutsPubs) obj;
 
        return this.Aut1.equals(other.getAut1()) && this.Aut2.equals(other.getAut2()) || this.Aut1.equals(other.getAut2()) && this.Aut2.equals(other.getAut1()); 
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append("Nome do par de autores: ").append(this.getAut1()).append("; ").append(this.getAut2() + " - ");
        s.append("Total de publicações realizadas: ").append(this.total).append("\n");
        return s.toString();   
    }

    public ParAutsPubs clone(){ return new ParAutsPubs(this); }
    
    public int hashCode() {
        return Arrays.hashCode(new Object[] {Aut1, Aut2, total});
    }
}
