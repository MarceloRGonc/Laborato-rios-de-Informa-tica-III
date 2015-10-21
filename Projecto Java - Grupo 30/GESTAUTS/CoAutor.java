import java.io.Serializable;
import java.util.*;

/**
 *
 * @author NaoHaPai
 */
class CoAutor implements Serializable{
    String Nome;
    int pub;
    
    public CoAutor(){
        this.Nome = "";
        this.pub = 0;
    }
    
    public CoAutor(String nome){
        this.Nome = nome;
        this.pub = 1;
    }
    
    public CoAutor(String nome, int valor){
        this.Nome = nome;
        this.pub = valor;
    }
    
    public CoAutor(CoAutor n){
        this.Nome = n.getNome();
        this.pub = n.getCoAut();
    }
        
    public String getNome(){return this.Nome;}
    public int getCoAut(){return this.pub;}

    public void setCoAut(int x){ this.pub = x;}
    
    public int hashCode() {
        return Arrays.hashCode(new Object[] {Nome, pub});
    }

    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) { return false; }
        CoAutor other = (CoAutor) obj;
        if (!(this.Nome.equals(other.getNome()))) { return false; }
        
        return true;
    }
    
    public CoAutor clone(){ return new CoAutor(this); }

    public void incPub(){this.pub++;}
}