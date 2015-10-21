import java.io.Serializable;
import java.util.Comparator;

/**
 * 
 * @author Grupo 30
 */

public class CoAutComparator implements Comparator<CoAutor>, Serializable {
    
        public int compare(CoAutor n, CoAutor o){
            if(n.getCoAut() < o.getCoAut()) return 1;
            else if(n.equals(o)) return 0;
            else return -1;
        }
    
}