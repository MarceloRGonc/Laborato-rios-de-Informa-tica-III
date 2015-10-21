import java.io.Serializable;
import java.util.Comparator;

/**
 * 
 * @author Grupo 30
 */

public class AutComparator implements Comparator<Autor>, Serializable {
    
        public int compare(Autor n, Autor o){
            if(n.getTPub() < o.getTPub()) return 1;
            else if(o.equals(n)) return 0;
            else return -1;
        }
    
}